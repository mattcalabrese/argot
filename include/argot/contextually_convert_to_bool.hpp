/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONTEXTUALLY_CONVERT_TO_BOOL_HPP_
#define ARGOT_CONTEXTUALLY_CONVERT_TO_BOOL_HPP_

#include <argot/concepts/contextually_convertible_to_bool.hpp>
#include <argot/forward.hpp>
#include <argot/gen/requires.hpp>

namespace argot {

struct contextually_convert_to_bool_fn
{
  template< class T >
  ARGOT_REQUIRES( ContextuallyConvertibleToBool< T&& > )
  < bool > constexpr operator()( T&& arg ) const
  {
    return ARGOT_FORWARD( T )( arg ) ? true : false;
  }
} inline constexpr contextually_convert_to_bool{};

}  // namespace argot

#endif  // ARGOT_CONTEXTUALLY_CONVERT_TO_BOOL_HPP_
