/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_FORGETFUL_THENABLE_DETAIL_STLAB_FUTURE_HPP_
#define ARGOT_CONCEPTS_FORGETFUL_THENABLE_DETAIL_STLAB_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_STLAB_FUTURE
#error Included stlab::future concept map header without continuations enabled.
#else

#include <argot/concepts/forgetful_thenable.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/void_.hpp>

#include <stlab/concurrency/future.hpp>
#include <stlab/concurrency/immediate_executor.hpp>

namespace argot {
namespace detail_future_stlab_future {

template< class Fun, class ValueType >
struct continuation
{
  // Mutable because stlab doesn't execute the function as a non-const rvalue.
  ARGOT_NO_UNIQUE_ADDRESS mutable Fun fun;

  // NOTE: This should only ever be called once.
  //       This overload exists for void types.
  constexpr void operator()() const
  {
    ARGOT_MOVE( fun )( ValueType() );
  }

  constexpr void operator()( ValueType&& arg ) const
  {
    ARGOT_MOVE( fun )( ARGOT_MOVE( arg ) );
  }

  constexpr void operator()( ValueType const& arg ) const
  {
    ARGOT_MOVE( fun )( arg );
  }
};

template< class Fun, class ValueType >
struct continuation< Fun, ValueType& >
{
  // Mutable because stlab doesn't execute the function as a non-const rvalue.
  ARGOT_NO_UNIQUE_ADDRESS mutable Fun fun;

  constexpr void operator()( ValueType arg ) const
  {
    ARGOT_MOVE( fun )( arg );
  }
};

} // namespace argot(::detail_future_stlab_future)

template< class T >
struct make_concept_map
< ForgetfulThenable< stlab::future< T >, executor::immediate_t > >
{
  template< class Fun >
  static constexpr void
  forgetful_then( stlab::future< T >&& self, executor::immediate_t, Fun&& fun )
  {
    (void)ARGOT_MOVE( self ).then
    ( stlab::immediate_executor
    , detail_future_stlab_future::continuation
      < Fun, void_to_regular_void_t< T > >
      { ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

} // namespace argot

#endif  // ARGOT_HAS_STLAB_FUTURE

#endif  // ARGOT_CONCEPTS_FORGETFUL_THENABLE_DETAIL_STLAB_FUTURE_HPP_
