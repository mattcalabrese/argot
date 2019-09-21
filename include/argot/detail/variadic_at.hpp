/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_VARIADIC_AT_HPP_
#define ARGOT_DETAIL_VARIADIC_AT_HPP_

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/expand.hpp>
#include <argot/detail/forward.hpp>

#include <cstddef>

namespace argot::detail_argot {

#define ARGOT_DETAIL_MAX_PREPROCESSED_AT 10

template< std::size_t I >
struct variadic_at_impl;

template<>
struct variadic_at_impl< 0 >
{
  template< class F, class E, class... Tail >
  static constexpr decltype( auto ) run( F&& fun, E&& elem, Tail&&... )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template< template< class... > class Result, class E, class... P >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 1 >
{
  template
  < class F
  , class D0
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result
  , class D0, class E, class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 2 >
{
  template
  < class F
  , class D0, class D1
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result, class D0, class D1
  , class E, class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 3 >
{
  template
  < class F
  , class D0, class D1, class D2
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2
  , class E
  , class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 4 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3
  , class E
  , class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 5 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4
  , class E
  , class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 6 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4, class D5
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4
  , class D5
  , class E
  , class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 7 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6
  , class E
  , class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 8 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7
  , class E
  , class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 9 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&, D8&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8
  , class E
  , class... Tail
  >
  using apply = Result< E >;
};

template<>
struct variadic_at_impl< 10 >
{
  static_assert( 10 == ARGOT_DETAIL_MAX_PREPROCESSED_AT );

  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8, class D9
  , class E
  , class... Tail
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&, D8&&, D9&&
  , E&& elem
  , Tail&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( E )( elem ) );
  }

  template
  < std::size_t I
  , class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8, class D9
  , class... Tail
  >
  static constexpr decltype( auto ) run_recursive
  ( F&& fun
  , D0&&, D1&&, D2&&, D3&&, D4&&, D5&&, D6&&, D7&&, D8&&, D9&&
  , Tail&&... tail
  )
  {
    constexpr std::size_t next_i = I - ARGOT_DETAIL_MAX_PREPROCESSED_AT;

    if constexpr( next_i <= ARGOT_DETAIL_MAX_PREPROCESSED_AT )
      return variadic_at_impl< next_i >::run
      ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( Tail )( tail )... );
    else
      return run_recursive< next_i >
      ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( Tail )( tail )... );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8, class D9
  , class E
  , class... Tail
  >
  using apply = Result< E >;

  template
  < std::size_t AmountToDrop
  , template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8, class D9
  , class... Tail
  >
  using apply_recursive
    = typename variadic_at_impl
      < AmountToDrop - ARGOT_DETAIL_MAX_PREPROCESSED_AT >
      ::template apply< Result, Tail... >;
};

template< std::size_t I >
struct variadic_at_impl
{
  template< class F, class... P >
  static constexpr decltype( auto ) run( F&& fun, P&&... args )
  {
    return variadic_at_impl< ARGOT_DETAIL_MAX_PREPROCESSED_AT >
    ::template run_recursive< I >
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class... P
  >
  using apply
    = expand_into_with_index
      < variadic_at_impl< ARGOT_DETAIL_MAX_PREPROCESSED_AT >
        ::template apply_recursive
      , I, Result, P...
      >;
};

#undef ARGOT_DETAIL_MAX_PREPROCESSED_AT

template< std::size_t I, class F, class... P >
constexpr decltype( auto ) variadic_at_run( F&& fun, P&&... args )
{
  return variadic_at_impl< I >::run
  ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
}

template< std::size_t I
        , template< class... > class Result, class... P
        >
using variadic_at
  = expand_into< variadic_at_impl< I >::template apply, Result, P... >;

// TODO(mattcalabrese) Remove
template< std::size_t I
        , template< class... > class Result, class... P
        >
using variadic_at_t
  = typename variadic_at_impl< I >::template apply< Result, P... >;

} // namespace (argot::detail_argot)

#endif  // ARGOT_DETAIL_VARIADIC_AT_HPP_
