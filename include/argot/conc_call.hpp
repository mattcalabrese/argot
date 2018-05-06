/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_CALL_HPP_
#define ARGOT_CONC_CALL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argot_invocable_with_reduction.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/always.hpp>
#include <argot/detail/call_impl.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/detail/operator_bracket.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {

////////////////////////////////////////////////////////////////////////////////
// Approach A:                                                                //
//                                                                            //
// If a ConcurrentArgumentProvider, pass along as-is.                         //
// Otherwise, if an argument provider, expand and capture each produced       //
//   argument in a ready_concurrent_argument_provider, by value.              //
// Otherwise, wrap in a ready_concurrent_argument_provider by value.          //
//                                                                            //
// Drawbacks:                                                                 //
//                                                                            //
// If a user does conc_call( fun, prov::reference_to(a) ), it will pass "a"   //
// by value rather than by reference.                                         //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Approach B:                                                                //
//                                                                            //
// If a ConcurrentArgumentProvider, pass along as-is.                         //
// Otherwise, if an argument provider, expand and capture the provider in a   //
//   ready_concurrent_argument_provider.                                      //
// Otherwise, wrap in a ready_concurrent_argument_provider by value.          //
//                                                                            //
// Drawbacks:                                                                 //
//                                                                            //
// If a user does conc_call( fun, prov::unpack(tup) ), it will capture tup by //
// reference.                                                                 //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Approach C:                                                                //
//                                                                            //
// If a ConcurrentArgumentProvider, pass along as-is.                         //
// Otherwise, if an argument provider, produce an error.                      //
// Otherwise, wrap in a ready_concurrent_argument_provider by value.          //
//                                                                            //
// Drawbacks:                                                                 //
//                                                                            //
// If a user does conc_call( fun, prov::unpack(tup) ), it will fail to        //
// compile.                                                                   //
////////////////////////////////////////////////////////////////////////////////

// This code...
foo( fun, when_ready(a_), when_ready(b_))

// Translates roughly to...
a_.then( [fun, b_]( a const& arg ) { b_.then( [fun, arg]( b const& arg2 ) { return fun( arg, arg2 ); } ) } )


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
//// General Idea:                                                          ////
////                                                                        ////
//// A ConcurrentArgumentProvider represents a "future" argument list       ////
//// portion to be expanded. It has an associated function "then_provide"   ////
//// which takes an ArgumentReceiver and provides ArgumentProviders. It is  ////
//// necessary to provide ArgumentProviders rather than the arguments       ////
//// directly because and ArgumentProvider (effectively) represents not     ////
//// just the arguments, but how the arguments are properly copied/moved.   ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct conc_call_t
{
  // TODO(mattcalabrese) Constrain
  template
  < class Spawner, class Fun, class... P
  , ARGOT_REQUIRES( FutureSpawner< remove_cvref_t< Spawner > > )
                  ( ConcurrentArgumentProvider< remove_cvref_t< P >... > )
                  ( Sinkable< Spawner&& >... )
                  ( Sinkable< P&& >... )
                  ()
  >
  auto operator ()( Spawner&& spawner, Fun&& fun, P&&... args ) const
  {
    // TODO(mattcalabrese) Force the grouping to not defer execution.

    return fut_traits::then
    ( conc::group( ARGOT_FORWARD( P )( args )... )
    , receiver::reduced_concurrent_invoke
      ( ARGOT_FORWARD( Spawner )( spawner ), /*default reducer*/,  )
    );
  }
} inline constexpr conc_call{};

template< class Fun, class... P >
using result_of_conc_call_t
  = basic_result_of_t< conc_call_t const&, Fun, P... >;

template< class Fun, class... P >
using result_of_conc_call
  = basic_result_of< conc_call_t const&, Fun, P... >;
/*
template< class Reducer, class Fun, class... P >
using result_of_reduced_conc_call_t
  = call_detail::result_of_bracketed_conc_call_t
    < conc_call_t const&, Reducer, Fun, P... >;

template< class Reducer, class Fun, class... P >
using result_of_reduced_conc_call
  = call_detail::result_of_bracketed_call
    < conc_call_t const&, Reducer, Fun, P... >;*/

} // namespace argot

#endif  // ARGOT_CONC_CALL_HPP_
