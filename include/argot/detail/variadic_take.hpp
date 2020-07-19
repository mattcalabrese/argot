/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_VARIADIC_TAKE_HPP_
#define ARGOT_DETAIL_VARIADIC_TAKE_HPP_

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/expand.hpp>
#include <argot/detail/forward.hpp>

#include <cstddef>

namespace argot::detail_argot {

#define ARGOT_DETAIL_MAX_PREPROCESSED_TAKE 10

template< std::size_t I >
struct variadic_take_impl;

template<>
struct variadic_take_impl< 0 >
{
  template< class F, class... P >
  static constexpr decltype( auto ) run( F&& fun, P&&... )
  {
    return argot_detail::constexpr_invoke( ARGOT_FORWARD( F )( fun ) );
  }

  template< template< class... > class Result, class... P >
  using apply = Result<>;
};

template<>
struct variadic_take_impl< 1 >
{
  template
  < class F
  , class D0
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    );
  }

  template< template< class... > class Result, class D0, class... P >
  using apply = Result< D0 >;
};

template<>
struct variadic_take_impl< 2 >
{
  template
  < class F
  , class D0, class D1
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    );
  }

  template< template< class... > class Result, class D0, class D1, class... P >
  using apply = Result< D0, D1 >;
};

template<>
struct variadic_take_impl< 3 >
{
  template
  < class F
  , class D0, class D1, class D2
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    , ARGOT_FORWARD( D2 )( d2 )
    );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2
  , class... P
  >
  using apply = Result< D0, D1, D2 >;
};

template<>
struct variadic_take_impl< 4 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2, D3&& d3
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    , ARGOT_FORWARD( D2 )( d2 )
    , ARGOT_FORWARD( D3 )( d3 )
    );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3
  , class... P
  >
  using apply = Result< D0, D1, D2, D3 >;
};

template<>
struct variadic_take_impl< 5 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2, D3&& d3, D4&& d4
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    , ARGOT_FORWARD( D2 )( d2 )
    , ARGOT_FORWARD( D3 )( d3 )
    , ARGOT_FORWARD( D4 )( d4 )
    );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4
  , class... P
  >
  using apply = Result< D0, D1, D2, D3, D4 >;
};

template<>
struct variadic_take_impl< 6 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2, D3&& d3, D4&& d4
  , D5&& d5
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    , ARGOT_FORWARD( D2 )( d2 )
    , ARGOT_FORWARD( D3 )( d3 )
    , ARGOT_FORWARD( D4 )( d4 )
    , ARGOT_FORWARD( D5 )( d5 )
    );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5
  , class... P
  >
  using apply = Result< D0, D1, D2, D3, D4, D5 >;
};

template<>
struct variadic_take_impl< 7 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2, D3&& d3, D4&& d4
  , D5&& d5, D6&& d6
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    , ARGOT_FORWARD( D2 )( d2 )
    , ARGOT_FORWARD( D3 )( d3 )
    , ARGOT_FORWARD( D4 )( d4 )
    , ARGOT_FORWARD( D5 )( d5 )
    , ARGOT_FORWARD( D6 )( d6 )
    );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class... P
  >
  using apply = Result< D0, D1, D2, D3, D4, D5, D6 >;
};

template<>
struct variadic_take_impl< 8 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2, D3&& d3, D4&& d4
  , D5&& d5, D6&& d6, D7&& d7
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    , ARGOT_FORWARD( D2 )( d2 )
    , ARGOT_FORWARD( D3 )( d3 )
    , ARGOT_FORWARD( D4 )( d4 )
    , ARGOT_FORWARD( D5 )( d5 )
    , ARGOT_FORWARD( D6 )( d6 )
    , ARGOT_FORWARD( D7 )( d7 )
    );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7
  , class... P
  >
  using apply = Result< D0, D1, D2, D3, D4, D5, D6, D7 >;
};

template<>
struct variadic_take_impl< 9 >
{
  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2, D3&& d3, D4&& d4
  , D5&& d5, D6&& d6, D7&& d7, D8&& d8
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    , ARGOT_FORWARD( D2 )( d2 )
    , ARGOT_FORWARD( D3 )( d3 )
    , ARGOT_FORWARD( D4 )( d4 )
    , ARGOT_FORWARD( D5 )( d5 )
    , ARGOT_FORWARD( D6 )( d6 )
    , ARGOT_FORWARD( D7 )( d7 )
    , ARGOT_FORWARD( D8 )( d8 )
    );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8
  , class... P
  >
  using apply = Result< D0, D1, D2, D3, D4, D5, D6, D7, D8 >;
};

template<>
struct variadic_take_impl< 10 >
{
  static_assert( 10 == ARGOT_DETAIL_MAX_PREPROCESSED_TAKE );

  template
  < class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8, class D9
  , class... P
  >
  static constexpr decltype( auto ) run
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2, D3&& d3, D4&& d4
  , D5&& d5, D6&& d6, D7&& d7, D8&& d8, D9&& d9
  , P&&...
  )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( F )( fun )
    , ARGOT_FORWARD( D0 )( d0 )
    , ARGOT_FORWARD( D1 )( d1 )
    , ARGOT_FORWARD( D2 )( d2 )
    , ARGOT_FORWARD( D3 )( d3 )
    , ARGOT_FORWARD( D4 )( d4 )
    , ARGOT_FORWARD( D5 )( d5 )
    , ARGOT_FORWARD( D6 )( d6 )
    , ARGOT_FORWARD( D7 )( d7 )
    , ARGOT_FORWARD( D8 )( d8 )
    , ARGOT_FORWARD( D9 )( d9 )
    );
  }

  template
  < std::size_t AmountToTake
  , class F
  , class D0, class D1, class D2, class D3, class D4
  , class D5, class D6, class D7, class D8, class D9
  , class... P
  >
  static constexpr decltype( auto ) run_recursive
  ( F&& fun
  , D0&& d0, D1&& d1, D2&& d2, D3&& d3, D4&& d4
  , D5&& d5, D6&& d6, D7&& d7, D8&& d8, D9&& d9
  , P&&... args
  )
  {    
    constexpr std::size_t next_i
      = AmountToTake - ARGOT_DETAIL_MAX_PREPROCESSED_TAKE;

    // TODO(mattcalabrese) Possibly don't use a lambda here.
    auto const call_with_leading_arguments
      = [ & ]( auto&&... next_args ) -> decltype( auto )
        {
          return argot_detail::constexpr_invoke
          ( ARGOT_FORWARD( F )( fun )
          , ARGOT_FORWARD( D0 )( d0 )
          , ARGOT_FORWARD( D1 )( d1 )
          , ARGOT_FORWARD( D2 )( d2 )
          , ARGOT_FORWARD( D3 )( d3 )
          , ARGOT_FORWARD( D4 )( d4 )
          , ARGOT_FORWARD( D5 )( d5 )
          , ARGOT_FORWARD( D6 )( d6 )
          , ARGOT_FORWARD( D7 )( d7 )
          , ARGOT_FORWARD( D8 )( d8 )
          , ARGOT_FORWARD( D9 )( d9 )
          , ARGOT_FORWARD( decltype( next_args ) )( next_args )...
          );
        };

    if constexpr( next_i <= ARGOT_DETAIL_MAX_PREPROCESSED_TAKE )
      return variadic_take_impl< next_i >::run
      ( call_with_leading_arguments
      , ARGOT_FORWARD( decltype( args ) )( args )...
      );
    else
      run_recursive< next_i >
      ( call_with_leading_arguments
      , ARGOT_FORWARD( decltype( args ) )( args )...
      );
  }

  template
  < template< class... > class Result
  , class D0, class D1, class D2, class D3, class D4, class D5, class D6
  , class D7, class D8, class D9
  , class... P
  >
  using apply = Result< D0, D1, D2, D3, D4, D5, D6, D7, D8, D9 >;

  // TODO(mattcalabrese) Optimize so that further recursion concatenates these
  template< template< class... > class Result, class... AlreadyTaken >
  struct result_with_leading_parameters
  {
    template< class... P >
    using apply = Result< AlreadyTaken..., P... >;
  };

  template< std::size_t AmountToTake
          , template< class... > class Result
          , class D0, class D1, class D2, class D3, class D4, class D5, class D6
          , class D7, class D8, class D9
          , class... P
          >
  using apply_recursive
    = expand_into
      < variadic_take_impl
        < AmountToTake - ARGOT_DETAIL_MAX_PREPROCESSED_TAKE >
        ::template apply
      , result_with_leading_parameters
        < Result, D0, D1, D2, D3, D4, D5, D6, D7, D8, D9 >::template apply
      , P...
      >;
};

template< std::size_t I >
struct variadic_take_impl
{
  template< class F, class... P >
  static constexpr decltype( auto ) run( F&& fun, P&&...args )
  {
    return variadic_take_impl< ARGOT_DETAIL_MAX_PREPROCESSED_TAKE >
    ::template run_recursive< I >
    ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
  }

  template
  < template< class... > class Result
  , class... P
  >
  using apply
    = expand_into_with_index
      < variadic_take_impl< ARGOT_DETAIL_MAX_PREPROCESSED_TAKE >
        ::template apply_recursive
      , I, Result, P...
      >;
};

#undef ARGOT_DETAIL_MAX_PREPROCESSED_TAKE

template< std::size_t AmountToTake, class F, class... P >
constexpr decltype( auto ) variadic_take_run( F&& fun, P&&... args )
{
  return variadic_take_impl< AmountToTake >::run
  ( ARGOT_FORWARD( F )( fun ), ARGOT_FORWARD( P )( args )... );
}

template< std::size_t AmountToTake
        , template< class... > class Result, class... P
        >
using variadic_take
  = expand_into
    < variadic_take_impl< AmountToTake >::template apply
    , Result, P...
    >;

} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_VARIADIC_TAKE_HPP_
