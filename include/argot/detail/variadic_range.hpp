/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_VARIADIC_RANGE_HPP_
#define ARGOT_DETAIL_VARIADIC_RANGE_HPP_

#include <argot/detail/forward.hpp>
#include <argot/detail/variadic_drop.hpp>
#include <argot/detail/variadic_take.hpp>

#include <cstddef>

namespace argot::detail_argot {

template< std::size_t Size, class Fun >
constexpr auto bind_variadic_take_run( Fun&& fun )
{
  return [ &fun ]( auto&&... args ) -> decltype( auto )
  {
    return variadic_take_impl< Size >::run
    ( ARGOT_FORWARD( Fun )( fun )
    , ARGOT_FORWARD( decltype( args ) )( args )...
    );
  };
}

template< std::size_t Size, template< class... > class Result >
struct bind_variadic_take
{
  template< class... P >
  using apply = variadic_take< Size, Result, P... >;
};

template< std::size_t Start, std::size_t Size, class F, class... P >
constexpr decltype( auto ) variadic_sized_range_run( F&& fun, P&&... args )
{
  return variadic_drop_impl< Start >::run
  ( ( bind_variadic_take_run< Size > )( ARGOT_FORWARD( F )( fun ) )
  , ARGOT_FORWARD( P )( args )...
  );
}

template< std::size_t Start, std::size_t Size
        , template< class... > class Result, class... P
        >
using variadic_sized_range
  = typename variadic_drop_impl< Start >
    ::template apply
    < bind_variadic_take< Size, Result >::template apply, P... >;

template< std::size_t Start, std::size_t End, class F, class... P >
constexpr decltype( auto ) variadic_range_run( F&& fun, P&&... args )
{
  return variadic_drop_impl< Start >::run
  ( ( bind_variadic_take_run< End - Start > )( ARGOT_FORWARD( F )( fun ) )
  , ARGOT_FORWARD( P )( args )...
  );
}

template< std::size_t Start, std::size_t End
        , template< class... > class Result, class... P
        >
using variadic_range
  = typename variadic_drop_impl< Start >
    ::template apply
    < bind_variadic_take< End - Start, Result >::template apply, P... >;

} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_VARIADIC_RANGE_HPP_
