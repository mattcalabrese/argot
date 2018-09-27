/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_AS_CALL_OBJECT_HPP_
#define ARGOT_AS_CALL_OBJECT_HPP_

//[description
/*`
argot::as_call_object is a facility that takes a Callable and returns an object
that may pass ArgumentProvider objects as arguments directly, with them
implicitly undergoing provision, without having to pass the function object to
argot::call.
*/
//]

#include <argot/call.hpp>
#include <argot/concepts/argot_invocable.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>

#include <functional>
#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

template< class Fun >
struct as_call_object_t
{
  //<-
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
              )
              ()
            >
    constexpr decltype( auto ) operator()( P&&... args ) const&
    {
      return bound_call( fun, ARGOT_FORWARD( P )( args )... );
    }

    template< class... P
            , ARGOT_REQUIRES
              ( ArgotInvocableWithReduction< Reducer, Fun&&, P&&... > )
              ()
            >
    constexpr decltype( auto ) operator()( P&&... args ) &&
    {
      return ARGOT_MOVE( bound_call )
      ( ARGOT_MOVE( fun ), ARGOT_FORWARD( P )( args )... );
    }

    bound_call_t bound_call;
    Fun fun;
  };
//->
  template< class... P
          , ARGOT_REQUIRES
            ( ArgotInvocable< Fun&&, P&&... > )
            ()
          >
  constexpr decltype( auto ) operator()( P&&... args ) &&//=;
  //<-
  {
    return ( call )( ARGOT_MOVE( fun ), ARGOT_FORWARD( P )( args )... );
  } //->

  template< class... P
          , ARGOT_REQUIRES
            ( ArgotInvocable< Fun const&, P&&... > )
            ()
          >
  constexpr decltype( auto ) operator()( P&&... args ) const&//=;
  //<-
  {
    return ( call )( fun, ARGOT_FORWARD( P )( args )... );
  } //->

  template< class Reducer
          , ARGOT_REQUIRES
            ( ReturnValueReducer< std::decay_t< Reducer > > )
            ( Sinkable< Reducer&& > )
            ( Sinkable< Fun const& > )
            ()
          >
  constexpr auto operator []( Reducer&& reducer ) const&//=;
  //<-
  {
    return with_reducer_t< std::decay_t< Reducer > >
    { ( call )[ ARGOT_FORWARD( Reducer )( reducer ) ], fun };
  } //->

  template< class Reducer
          , ARGOT_REQUIRES
            ( ReturnValueReducer< std::decay_t< Reducer > > )
            ( Sinkable< Reducer&& > )
            ( Sinkable< Fun&& > )
            ()
          >
  constexpr auto operator []( Reducer&& reducer ) &&//=;
  //<-
  {
    return with_reducer_t< std::decay_t< Reducer > >
    { ( call )[ ARGOT_FORWARD( Reducer )( reducer ) ]
    , ARGOT_MOVE( fun )
    };
  }
 
  Fun fun;
  //->
};

struct as_call_object_fn
{
  template< class Fun
          , ARGOT_REQUIRES
            ( PotentiallyInvocable< std::decay_t< Fun > > )
            ( DecaySinkable< Fun&& > )
            ()
          >
  constexpr auto operator ()( Fun&& fun ) const//=;
  //<-
  {
    return as_call_object_t< std::decay_t< Fun > >
    { ARGOT_FORWARD( Fun )( fun ) };
  } //->
} inline constexpr as_call_object{};

} // namespace argot

//]

#endif  // ARGOT_AS_CALL_OBJECT_HPP_
