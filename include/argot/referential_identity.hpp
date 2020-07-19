/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REFERENTIAL_IDENTITY_HPP_
#define ARGOT_REFERENTIAL_IDENTITY_HPP_

//[description
/*`
argot::referential_identity is a function object that returns its input by
reference.
*/
//]

#include <argot/basic_result_of.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

struct referential_identity_fn
{
  template< class P >
  [[nodiscard]]
  constexpr P&& operator()( P&& arg ) const noexcept//=;
  //<-
  {
    return static_cast< P&& >( arg );
  } //->
} inline constexpr referential_identity{};

template< class T >
using result_of_referential_identity//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< referential_identity_fn const&, T >; //->

template< class T >
using result_of_referential_identity_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< referential_identity_fn const&, T >; //->

} // namespace argot

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`P&& arg`]
  [A ParameterType]
  [The reference to be returned]
 ]
]
*/

//]

#endif  // ARGOT_IDENTITY_HPP_
