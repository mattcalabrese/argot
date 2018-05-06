/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_FUTURE_LIKE_FUTURE_LIKE_STLAB_FUTURE_HPP_
#define ARGOT_CONCEPTS_FUTURE_LIKE_FUTURE_LIKE_STLAB_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_STLAB_FUTURE
#error Included stlab::future concept map header without continuations enabled.
#else

#include <argot/concepts/future.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/move.hpp>
#include <argot/void_.hpp>

#include <stlab/concurrency/future.hpp>
#include <stlab/concurrency/immediate_executor.hpp>

#include <type_traits>

namespace argot {

template< class T >
struct make_concept_map< Future< stlab::future< T > > >
{
 public:
  using value_type_t
    = typename argot_detail::conditional< std::is_void_v< T > >
      ::template half_meta_apply< void_to_regular_void_t, T, T >;

 private:
  template< class Fun >
  struct continuation
  {
    ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, value_type_t&& > );

    // Mutable because stlab doesn't execute the function as a non-const rvalue.
    mutable Fun fun;

    // NOTE: This should only ever be called once.
    //       This overload exists for void types.
    constexpr decltype( auto ) operator()() const
    {
      return argot_detail::constexpr_invoke
      ( ARGOT_MOVE( fun ), value_type_t() );
    }

    // NOTE:
    //   This should only ever be called once.
    //   stlab is not r-value aware here. Because of this, we take by const& and
    //   cast away the unnecessary constness.
    constexpr decltype( auto ) operator()( value_type_t const& arg ) const
    {
      return argot_detail::constexpr_invoke
      ( ARGOT_MOVE( fun ), const_cast< value_type_t&& >( arg ) );
    }
  };
 public:
  // TODO(mattcalabrese) Constrain
  template< class Exec, class Fun >
  static constexpr decltype( auto )
  then( stlab::future< T >&& self, Exec&& exec, Fun&& fun )
  {
    // TODO(mattcalabrese) Perform the decay_sink as a cast to avoid moves
    return ARGOT_MOVE( self ).then
    ( stlab::immediate_executor /*convert to executor*/
    , continuation< std::decay_t< Fun&& > >
      { call_detail::decay_sink( ARGOT_FORWARD( Fun )( fun ) ) }
    );
  }
/*
  // TODO(mattcalabrese) Constrain
  template< class Exec, class Fun >
  static constexpr decltype( auto )
  then_on_executor( stlab::future< T >&& self, Exec&& exec, Fun&& fun )
  {
    // TODO(mattcalabrese) Perform the decay_sink as a cast to avoid moves
    return ARGOT_MOVE( self ).then
    ( ARGOT_FORWARD( Exec )( exec )  // TODO(mattcalabrese) Use native executor if encapsulated.
    , continuation< std::decay_t< Fun&& > >
      { call_detail::decay_sink( ARGOT_FORWARD( Fun )( fun ) ) }
    );
  }*/
};

} // namespace argot

#endif  // ARGOT_HAS_STLAB_FUTURE

#endif  // ARGOT_CONCEPTS_FUTURE_LIKE_FUTURE_LIKE_STLAB_FUTURE_HPP_
