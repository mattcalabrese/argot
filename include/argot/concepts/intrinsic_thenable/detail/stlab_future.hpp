/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_INTRINSIC_THENABLE_DETAIL_STLAB_FUTURE_HPP_
#define ARGOT_CONCEPTS_INTRINSIC_THENABLE_DETAIL_STLAB_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_STLAB_FUTURE
#error Included stlab::future concept map header without continuations enabled.
#else

#include <argot/concepts/future.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor/stlab.hpp>
#include <argot/executor_traits/execute.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/packager/stlab.hpp>
#include <argot/void_.hpp>

#include <stlab/concurrency/future.hpp>
#include <stlab/concurrency/immediate_executor.hpp>

#include <type_traits>

namespace argot {
namespace detail_thenable_stlab_future {

template< class Fun, class ValueType >
struct continuation
{
  // Mutable because stlab doesn't execute the function as a non-const rvalue.
  ARGOT_NO_UNIQUE_ADDRESS mutable Fun fun;

  // NOTE: This should only ever be called once.
  //       This overload exists for void types.
  constexpr decltype( auto ) operator()() const
  {
    return ARGOT_MOVE( fun )( ValueType() );
  }

  constexpr decltype( auto ) operator()( ValueType&& arg ) const
  {
    return ARGOT_MOVE( fun )( ARGOT_MOVE( arg ) );
  }

  constexpr decltype( auto ) operator()( ValueType const& arg ) const
  {
    return ARGOT_MOVE( fun )( arg );
  }
};

template< class Fun, class ValueType >
struct continuation< Fun, ValueType& >
{
  // Mutable because stlab doesn't execute the function as a non-const rvalue.
  ARGOT_NO_UNIQUE_ADDRESS mutable Fun fun;

  // NOTE: This should only ever be called once.
  //       This overload exists for void types.
  constexpr decltype( auto ) operator()() const
  {
    return ARGOT_MOVE( fun )( ValueType() );
  }

  constexpr decltype( auto ) operator()( ValueType& arg ) const
  {
    return ARGOT_MOVE( fun )( ARGOT_FORWARD( ValueType& )( arg ) );
  }
};

template< class Exec >
struct stlab_executor
{
  ARGOT_CONCEPT_ASSERT( Executor< Exec > );

  ARGOT_NO_UNIQUE_ADDRESS Exec exec;

  template< class Fun >
  void operator ()( Fun&& fun ) const
  {
    executor_traits::execute( exec, ARGOT_FORWARD( Fun )( fun ) );
  }
};

template< class T >
constexpr bool const& is_wrapped_stlab_executor_v = std::false_type::value;

template< class T >
constexpr bool const& is_wrapped_stlab_executor_v
                      < executor::stlab_fn::impl< T > >
  = std::true_type::value;

template< class Exec >
auto to_stlab_executor( Exec&& exec )
{
  if constexpr( is_wrapped_stlab_executor_v< detail_argot::remove_cvref_t< Exec > > )
    return ARGOT_FORWARD( Exec )( exec ).stlab_exec;
  else
    return stlab_executor< detail_argot::remove_cvref_t< Exec > >
    { call_detail::forward_and_sink< Exec >( exec ) };
}

} // namespace argot(::detail_thenable_stlab_future)

template< class T, class Exec >
struct make_concept_map
< IntrinsicThenable< stlab::future< T >, packager::stlab, Exec >
, ARGOT_REQUIRES( Executor< Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class ExecP, class Fun >
  static constexpr auto
  then( stlab::future< T >&& self, ExecP&& exec, Fun&& fun )
  {
    return ARGOT_MOVE( self ).then
    ( detail_thenable_stlab_future::to_stlab_executor
      ( call_detail::forward_and_sink< ExecP >( exec ) )
    , detail_thenable_stlab_future::continuation
      < Fun, fut_traits::value_type_t< stlab::future< T > > >
      { ARGOT_MOVE( fun ) }
    );
  }
};

} // namespace argot

#endif  // ARGOT_HAS_STLAB_FUTURE

#endif  // ARGOT_CONCEPTS_INTRINSIC_THENABLE_DETAIL_STLAB_FUTURE_HPP_
