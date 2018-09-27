/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_INVOKER_HPP_
#define ARGOT_DETAIL_INVOKER_HPP_

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/sink.hpp>
#include <argot/no_unique_address.hpp>

#include <functional>
#include <type_traits>
#include <utility>

namespace argot::argot_detail {

// This is just a simple reference wrapper that turns a Callable into a function
// object with a function call operator overloaded to std::invoke the function.
// This is done rather that using std::invoke internally in the implementation
// of call because the implementation of call is recursive and we only need to
// use std::invoke on the Callable that the user passes in (during recursion,
// lambdas are used, which don't require the functionality of std::invoke).
template< class Fun >
struct invoker_by_reference
{
  // TODO(mattcalabrese) Require Fun is a reference type
  // TODO(mattcalabrese) Use contained here
  Fun&& fun;

  // TODO(mattcalabrese) Constrain
  template< class... P >
  constexpr argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... >
  operator()( P&&... args ) &&
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... );
  }
};

// This is just a simple wrapper that turns a Callable into a function object
// with a function call operator overloaded to std::invoke the function.
// This is done rather that using std::invoke internally in the implementation
// of call because the implementation of call is recursive and we only need to
// use std::invoke on the Callable that the user passes in (during recursion,
// lambdas are used, which don't require the functionality of std::invoke).
template< class Fun >
struct invoker_by_value
{
  // TODO(mattcalabrese) Require Fun is a reference type
  // TODO(mattcalabrese) Use contained here
  ARGOT_NO_UNIQUE_ADDRESS Fun fun;

  // TODO(mattcalabrese) Constrain
  template< class... P >
  constexpr argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... >
  operator()( P&&... args ) &&
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_MOVE( fun ), ARGOT_FORWARD( P )( args )... );
  }
};

template< class Inv  /*TODO(mattcalabrese) Constrain*/ >
constexpr
decltype( auto ) invocable_to_basic_callable_by_reference( Inv&& invocable )
{
  using raw_type = detail_argot::remove_cvref_t< Inv >;

  if constexpr( std::is_member_pointer_v< raw_type > )
    return invoker_by_reference< Inv&& >{ ARGOT_FORWARD( Inv )( invocable ) };
  else
    if constexpr( std::is_function_v< raw_type > )
      return invoker_by_value< raw_type* >{ invocable };
    else
      return ARGOT_FORWARD( Inv )( invocable );
}

template< class Inv  /*TODO(mattcalabrese) Constrain*/ >
constexpr auto invocable_to_basic_callable_by_value( Inv&& invocable )
{
  if constexpr( std::is_member_pointer_v< detail_argot::remove_cvref_t< Inv > > )
    return invoker_by_value< std::decay_t< Inv > >
    { ARGOT_FORWARD( Inv )( invocable ) };
  else
    return call_detail::forward_and_decay_sink< Inv >( invocable );
}

} // namespace (argot::argot_detail)

#endif  // ARGOT_DETAIL_INVOKER_HPP_
