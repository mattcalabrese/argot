/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_OPERATOR_BRACKET_HPP_
#define ARGOT_DETAIL_OPERATOR_BRACKET_HPP_

#include <argot/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/forward.hpp>

// TODO(mattcalabrese) Properly constrain and deduce return types.

namespace argot {
namespace call_detail {

template< class Self, class Operand >
using result_of_operator_bracket_t
  = decltype( ARGOT_DECLVAL( Self )[ ARGOT_DECLVAL( Operand ) ] );

template< class Self, class Operand >
using result_of_operator_bracket
  = lazy_expand< result_of_operator_bracket_t, Self, Operand >;

struct operator_bracket_t
{
  template< class Self, class Operand >
  result_of_operator_bracket_t< Self, Operand >
  operator ()( Self&& self, Operand&& operand ) const
  {
    return ARGOT_FORWARD( Self )( self )[ ARGOT_FORWARD( Operand )( operand ) ];
  }
} inline constexpr operator_bracket{};

template< class Enabler, class Self, class Operand, class... P >
struct result_of_bracketed_call_impl{};

template< class Self, class Operand, class... P >
using result_of_bracketed_call_t
  = decltype
    ( ARGOT_DECLVAL( Self )[ ARGOT_DECLVAL( Operand ) ]
      ( ARGOT_DECLVAL( P )... )
    );

template< class Self, class Operand, class... P >
using result_of_bracketed_call
  = lazy_expand< result_of_bracketed_call_t, Self, Operand, P... >;

struct bracketed_call_t
{
  template< class Self, class Operand, class... P >
  result_of_bracketed_call_t< Self, Operand, P... >
  operator ()( Self&& self, Operand&& operand, P&&... args ) const
  {
    return ARGOT_FORWARD( Self )( self )[ ARGOT_FORWARD( Operand )( operand ) ]
    ( ARGOT_FORWARD( P )( args )... );
  }
} /*inline*/ constexpr bracketed_call{};

}  // namespace argot::call_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_OPERATOR_BRACKET_HPP_
