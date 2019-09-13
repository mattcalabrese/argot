/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_VARIADIC_DROP_HPP_
#define ARGOT_DETAIL_VARIADIC_DROP_HPP_

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>

#include <cstddef>

namespace argot::detail_argot {

#define ARGOT_DETAIL_MAX_PREPROCESSED_DROP 10

template< std::size_t I >
struct variadic_drop_impl;

template<>
struct variadic_drop_impl< 0 >
{
  template< class F, class... P >
  static constexpr decltype( auto ) run( F&& fun, P&&... args )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template< template< class... > class Result, class... P >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 1 >
{
  template
  < class F
  , class D0
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template< template< class... > class Result, class D0, class... P >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 2 >
{
  template
  < class F
  , class D0, class D1
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template< template< class... > class Result, class D0, class D1, class... P >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 3 >
{
  template
  < class F
  , class D0, class D1, class D2
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2
  , class... P
  >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 4 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3
  , class... P
  >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 5 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4
  , class... P
  >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 6 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4, class D5
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4
  , class D5
  , class... P
  >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 7 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6
  , class... P
  >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 8 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7
  , class... P
  >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 9 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&, D8&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8
  , class... P
  >
  using apply = Result< P... >;
};

template<>
struct variadic_drop_impl< 10 >
{
  static_assert( 10 == ARGOT_DETAIL_MAX_PREPROCESSED_DROP );

  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8, class D9
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&, D8&&, D9&&
  , P&&... args
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < std::size_t AmountToDrop
  , class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8, class D9
  , class... P
  >
  static constexpr decltype( auto ) run_recursive
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&, D8&&, D9&&
  , P&&... args
  )
  {
    return variadic_drop_impl
    < AmountToDrop - ARGOT_DETAIL_MAX_PREPROCESSED_DROP >::run
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8, class D9
  , class... P
  >
  using apply = Result< P... >;

  template
  < std::size_t AmountToDrop
  , template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8, class D9, class... P
  >
  using apply_recursive
    = typename variadic_drop_impl
      < AmountToDrop - ARGOT_DETAIL_MAX_PREPROCESSED_DROP >
      ::template apply< Result, P... >;
};

template< std::size_t I >
struct variadic_drop_impl
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8, class D9
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&, D8&&, D9&&
  , P&&... args
  )
  {
    return variadic_drop_impl< ARGOT_DETAIL_MAX_PREPROCESSED_DROP >
    ::template run< I - ARGOT_DETAIL_MAX_PREPROCESSED_DROP >
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8, class D9
  , class... P
  >
  using apply
    = variadic_drop_impl< ARGOT_DETAIL_MAX_PREPROCESSED_DROP >
      ::template apply_recursive
      < I - ARGOT_DETAIL_MAX_PREPROCESSED_DROP, Result
      , D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, P...
      >;
};

#undef ARGOT_DETAIL_MAX_PREPROCESSED_DROP

template< std::size_t AmountToDrop, class F, class... P >
constexpr decltype( auto ) variadic_drop_run( F&& fun, P&&... args )
{
  return variadic_drop_impl< AmountToDrop >::run
  ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
}

template< std::size_t AmountToDrop
        , template< class... > class Result, class... P
        >
using variadic_drop
  = typename variadic_drop_impl< AmountToDrop >::template apply< Result, P... >;


} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_VARIADIC_DROP_HPP_
