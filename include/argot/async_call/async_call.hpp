/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_ASYNC_CALL_ASYNC_CALL_HPP_
#define ARGOT_ASYNC_CALL_ASYNC_CALL_HPP_

#include <argot/async_call/detail/continuation_with_reducer.hpp>
#include <argot/basic_result_of.hpp>
#include <argot/conc/default_to_value_of.hpp>
#include <argot/concepts/argot_invocable_with_reduction.hpp>
#include <argot/concepts/concurrent_can_default_to_value_of.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/detail/operator_bracket.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/then.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/reducer_reference.hpp>
#include <argot/reducer/same_type_or_fail.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot {

template< class FPackager >
struct async_call_fn
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );

 private:
  template< class Reducer >
  struct with_reducer
  {
    ARGOT_CONCEPT_ASSERT( ReturnValueReducer< Reducer > );

    // TODO(mattcalabrese) Check callability
    template< class Exec, class Fun, class... P
            , ARGOT_REQUIRES
              ( Executor< remove_cvref_t< Exec > > )
              ( ConcurrentCanDefaultToValueOf< remove_cvref_t< P > >... )
              ( Sinkable< Exec&& > )
              ( DecaySinkable< Fun&& > )
              ( Sinkable< P&& >... )
              ()
            >
    [[nodiscard]]
    constexpr decltype( auto )
    operator()( Exec&& exec, Fun&& fun, P&&... args ) &&
    {
      return fut_traits::then< FPackager >
      ( conc_traits::as_future
        ( conc::default_to_value_of( ARGOT_FORWARD( P )( args )... ) )
      , call_detail::forward_and_sink< Exec >( exec )
      , detail_async_call::continuation_with_reducer
        < FPackager, Reducer, std::decay_t< Fun > >
        { ARGOT_MOVE( reducer )
        , call_detail::forward_and_decay_sink< Fun >( fun )
        }
      );
    }

    // TODO(mattcalabrese) Check callability
    template
    < class Exec, class Fun, class... P
    , ARGOT_REQUIRES
      ( Executor< remove_cvref_t< Exec > > )
      ( ConcurrentCanDefaultToValueOf< remove_cvref_t< P > >... )
      ( Sinkable< Exec&& > )
      ( DecaySinkable< Fun&& > )
      ( Sinkable< P&& >... )
      ()
    >
    [[nodiscard]]
    constexpr decltype( auto )
    operator()( Exec&& exec, Fun&& fun, P&&... args ) const&
    {
      return fut_traits::then< FPackager >
      ( conc_traits::as_future
        ( conc::default_to_value_of( ARGOT_FORWARD( P )( args )... ) )
      , call_detail::forward_and_sink< Exec >( exec )
      , detail_async_call::continuation_with_reducer
        < FPackager, Reducer, std::decay_t< Fun > >
        { reducer
        , call_detail::forward_and_decay_sink< Fun >( fun )
        }
      );
    }

    ARGOT_NO_UNIQUE_ADDRESS Reducer reducer;
  };

  template< class Fun >
  struct continuation
  {
    // TODO(mattcalabrese) concept assert potentially invocable

    // TODO(mattcalabrese) conditional noexcept
    // TODO(mattcalabrese) take by forwarding reference
    template< class Provider >
    constexpr decltype( auto ) operator ()( Provider provider ) &&
    {
      return prov_traits::destructive_provide
      ( ARGOT_MOVE( provider )
      , receiver::reduced_invoke
        ( reducer::same_type_or_fail
        , argot_detail::invocable_to_basic_callable_by_reference
          ( ARGOT_FORWARD( Fun )( fun ) )
        )
      );
    }

    ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  };
 public:
  // TODO(mattcalabrese) Check callability
  template
  < class Exec, class Fun, class... P
  , ARGOT_REQUIRES( Executor< remove_cvref_t< Exec > > )
                  ( ConcurrentCanDefaultToValueOf< remove_cvref_t< P > >... )
                  ( Sinkable< Exec&& > )
                  ( DecaySinkable< Fun&& > )
                  ( Sinkable< P&& >... )
                  ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Exec&& exec, Fun&& fun, P&&... args ) const
  {
    return fut_traits::then< FPackager >
    ( conc_traits::as_future
      ( conc::default_to_value_of( ARGOT_FORWARD( P )( args )... ) )
    , call_detail::forward_and_sink< Exec >( exec )
    , continuation< std::decay_t< Fun > >
      { call_detail::forward_and_decay_sink< Fun >( fun ) }
    );
  }

  template< class Reducer
          , ARGOT_REQUIRES( ReturnValueReducer< remove_cvref_t< Reducer > > )
                          ( Sinkable< Reducer&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator []( Reducer&& reducer ) const
  {
    return with_reducer< remove_cvref_t< Reducer > >
    { call_detail::forward_and_sink< Reducer >( reducer ) };
  }
};

template< class FPackager >
ARGOT_REQUIRES( FuturePackager< FPackager > )
< async_call_fn< FPackager > > constexpr async_call{};

template< class FPackager, class Exec, class Fun, class... P >
using result_of_async_call_t
  = basic_result_of_t< async_call_fn< FPackager > const&, Exec, Fun, P... >;

template< class FPackager, class Exec, class Fun, class... P >
using result_of_async_call
  = basic_result_of< async_call_fn< FPackager > const&, Exec, Fun, P... >;
/*
template< class Reducer, class Fun, class... P >
using result_of_reduced_async_call_t
  = call_detail::result_of_bracketed_async_call_t
    < async_call_t const&, Reducer, Fun, P... >;

template< class Reducer, class Fun, class... P >
using result_of_reduced_async_call
  = call_detail::result_of_bracketed_call
    < async_call_t const&, Reducer, Fun, P... >;*/

} // namespace argot

#endif  // ARGOT_ASYNC_CALL_ASYNC_CALL_HPP_
