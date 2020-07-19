/*==============================================================================
  Copyright (c) 2017, 2018, 2019, 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_IDENTITY_HPP_
#define ARGOT_IDENTITY_HPP_

//[description
/*`
argot::identity is a function object that returns its input by value.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/remove_cvref.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

struct identity_fn
{
  template< class P, ARGOT_REQUIRES( Sinkable< P&& > )() >
  [[nodiscard]]
  constexpr detail_argot::remove_cvref_t< P >
  operator()( P&& arg ) const//=;
  //<-
  {
    return call_detail::forward_and_sink< P&& >( arg );
  } //->
} inline constexpr identity{};

template< class P >
using result_of_identity//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< identity_fn const&, P >; //->

template< class P >
using result_of_identity_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< identity_fn const&, P >; //->

} // namespace argot

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`P&& arg`]
  [A Sinkable type]
  [An object with the value that `arg` had at the start of the function call.]
 ]
]
*/

//]

#endif  // ARGOT_IDENTITY_HPP_
