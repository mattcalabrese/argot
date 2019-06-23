/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CALL_OBJECT_BASE_HPP_
#define ARGOT_CALL_OBJECT_BASE_HPP_

#include <argot/call.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <memory>
#include <type_traits>
#include <utility>

namespace argot {
namespace detail_call_object_base {

template< class Fun, class... P >
using result_of_run_t
  = decltype
    ( detail_argot::remove_cvref_t< Fun >::run
      ( ARGOT_DECLVAL( Fun ), ARGOT_DECLVAL( P )... )
    );

template< class Fun >
struct call_fun_t
{
  ARGOT_CONCEPT_ASSERT( Reference< Fun > );

  using cv_fun = std::remove_reference_t< Fun >;

  template< class... P >
  constexpr result_of_run_t< Fun, P&&... > operator ()( P&&... args ) &&
  {
    return cv_fun::run
    ( ARGOT_FORWARD( Fun )( *fun ), ARGOT_FORWARD( P )( args )... );
  }

  cv_fun* fun;
};

template< class Fun >
constexpr call_fun_t< Fun&& > make_call_fun( Fun&& fun ) noexcept
{
  return { std::addressof( fun ) };
}

}  // namespace argot::detail_call_object_base

template< class Fun >
struct call_object_base
{

  ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Fun > );

  template< class Reducer >
  struct with_reducer_t
  {
    ARGOT_CONCEPT_ASSERT( ReturnValueReducer< Reducer > );

    using bound_call_t = call_t::with_reducer< Reducer >;

    // TODO(mattcalabrese) Make this only exist if the Reducer is persistent.
    template< class... P
            , ARGOT_REQUIRES
              ( ArgotInvocableWithPersistentReduction
                < Reducer, Fun const&, P&&... >
              )()
            >
    constexpr decltype( auto )
    operator()( P&&... args ) const&
    {
      return ARGOT_MOVE( bound_call )
      ( detail_call_object_base::make_call_fun( fun )
      , ARGOT_FORWARD( P )( args )...
      );
    }

    template< class... P
            , ARGOT_REQUIRES
              ( ArgotInvocableWithReduction< Reducer, Fun&&, P&&... > )()
            >
    constexpr decltype( auto )
    operator()( P&&... args ) &&
    {
      return ARGOT_MOVE( bound_call )
      ( detail_call_object_base::make_call_fun( ARGOT_MOVE( fun ) )
      , ARGOT_FORWARD( P )( args )...
      );
    }

    bound_call_t bound_call;
    Fun fun;
  };

   // TODO(mattcalabrese) Constrain
  template< class... P >
  constexpr result_of_call_t
  < detail_call_object_base::call_fun_t< Fun const& >, P&&... >
  operator()( P&&... args ) const&
  {
    return argot::call
    ( detail_call_object_base::make_call_fun
      ( static_cast< Fun const& >( *this ) )
    , ARGOT_FORWARD( P )( args )...
    );
  }

   // TODO(mattcalabrese) Constrain
  template< class... P >
  constexpr result_of_call_t
  < detail_call_object_base::call_fun_t< Fun&& >, P&&... >
  operator()( P&&... args ) &&
  {
    return argot::call
    ( detail_call_object_base::make_call_fun
      ( detail_call_object_base::make_call_fun
        ( static_cast< Fun&& >( ARGOT_MOVE( *this ) ) )
      )
    , ARGOT_FORWARD( P )( args )...
    );
  }

  template< class Reducer
          , ARGOT_REQUIRES( ReturnValueReducer< std::decay_t< Reducer > > )
                          ( Sinkable< Reducer&& > )
                          ( Sinkable< Fun const& > )
                          ()
          >
  constexpr auto operator []( Reducer&& reducer ) const&
  {
    return with_reducer_t< std::decay_t< Reducer > >
    { argot::call[ ARGOT_FORWARD( Reducer )( reducer ) ]
    , detail_call_object_base::make_call_fun
      ( detail_call_object_base::make_call_fun
        ( static_cast< Fun const& >( *this ) )
      )
    };
  }

  template< class Reducer
          , ARGOT_REQUIRES( ReturnValueReducer< std::decay_t< Reducer > > )
                          ( Sinkable< Reducer&& > )
                          ( Sinkable< Fun&& > )
                          ()
          >
  constexpr auto operator []( Reducer&& reducer ) &&
  {
    return with_reducer_t< std::decay_t< Reducer > >
    { argot::call[ ARGOT_FORWARD( Reducer )( reducer ) ]
    , detail_call_object_base::make_call_fun
      ( detail_call_object_base::make_call_fun
        ( static_cast< Fun&& >( ARGOT_MOVE( *this ) ) )
      )
    };
  }
};

}  // namespace argot

#endif  // ARGOT_CALL_OBJECT_BASE_HPP_
