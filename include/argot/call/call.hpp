/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CALL_CALL_HPP_
#define ARGOT_CALL_CALL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argot_invocable_with_persistent_reduction.hpp>
#include <argot/concepts/argot_invocable_with_reduction.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/detail/operator_bracket.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/reducer_reference.hpp>
#include <argot/reducer/same_type_or_fail.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {

struct call_t
{
  template< class Reducer >
  struct with_reducer
  {
    ARGOT_CONCEPT_ASSERT( ReturnValueReducer< Reducer > );

    template< class Fun, class... P
            , ARGOT_REQUIRES
              ( ArgotInvocableWithReduction< Reducer, Fun&&, P&&... > )
              ()
            >
    constexpr decltype( auto ) operator()( Fun&& fun, P&&... args ) &&
    {
      return prov_traits::destructive_provide
      ( prov::default_to_reference_to( ARGOT_FORWARD( P )( args )... )
      , receiver::reduced_invoke
        ( reducer::reducer_reference( ARGOT_MOVE( reducer ) )
        , argot_detail::invocable_to_basic_callable_by_reference
          ( ARGOT_FORWARD( Fun )( fun ) )
        )
      );
    }

    template
    < class Fun, class... P
    , ARGOT_REQUIRES
      ( ArgotInvocableWithPersistentReduction< Reducer, Fun&&, P&&... > )
      ()
    >
    constexpr decltype( auto ) operator()( Fun&& fun, P&&... args ) const&
    {
      return prov_traits::destructive_provide
      ( prov::default_to_reference_to( ARGOT_FORWARD( P )( args )... )
      , receiver::reduced_invoke
        ( reducer::reducer_reference( reducer )
        , argot_detail::invocable_to_basic_callable_by_reference
          ( ARGOT_FORWARD( Fun )( fun ) )
        )
      );
    }

    ARGOT_NO_UNIQUE_ADDRESS Reducer reducer;
  };

  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( ArgotInvocableWithPersistentReduction
      < reducer::same_type_or_fail_t, Fun&&, P&&... >
    )()
  >
  constexpr decltype( auto ) operator ()( Fun&& fun, P&&... args ) const
  {
    return prov_traits::destructive_provide
    ( prov::default_to_reference_to( ARGOT_FORWARD( P )( args )... )
    , receiver::reduced_invoke
      ( reducer::same_type_or_fail
      , argot_detail::invocable_to_basic_callable_by_reference
        ( ARGOT_FORWARD( Fun )( fun ) )
      )
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
} inline constexpr call{};

template< class Fun, class... P >
using result_of_call_t = basic_result_of_t< call_t const&, Fun, P... >;

template< class Fun, class... P >
using result_of_call = basic_result_of< call_t const&, Fun, P... >;

template< class Reducer, class Fun, class... P >
using result_of_reduced_call_t
  = call_detail::result_of_bracketed_call_t
    < call_t const&, Reducer, Fun, P... >;

template< class Reducer, class Fun, class... P >
using result_of_reduced_call
  = call_detail::result_of_bracketed_call< call_t const&, Reducer, Fun, P... >;

}  // namespace argot

#endif  // ARGOT_CALL_CALL_HPP_
