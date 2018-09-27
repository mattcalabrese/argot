/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONTEXTUALLY_CONVERT_TO_BOOL_HPP_
#define ARGOT_CONTEXTUALLY_CONVERT_TO_BOOL_HPP_

//[description
/*`
argot::contextually_convert_to_bool is a facility for performing a standard
/contextually-convertible-to-bool/ operation.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/contextually_convertible_to_bool.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

struct contextually_convert_to_bool_fn
{
  template< class T
          , ARGOT_REQUIRES
            ( ContextuallyConvertibleToBool< T&& > )
            ()
          >
  bool constexpr operator()( T&& arg ) const//=;
  //<-
  {
    return ARGOT_FORWARD( T )( arg ) ? true : false;
  } //->
} inline constexpr contextually_convert_to_bool{};

template< class T >
using result_of_contextually_convert_to_bool_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< contextually_convert_to_bool_fn const&, T >; //->

} // namespace argot

//]

#endif  // ARGOT_CONTEXTUALLY_CONVERT_TO_BOOL_HPP_
