/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNREACHABLE_FUNCTION_HPP_
#define ARGOT_UNREACHABLE_FUNCTION_HPP_

#include <argot/concepts/return_type.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>

#include <boost/config.hpp>

//[description
/*`
argot::unreachable_function is a function object of a user-specified return type
that produces undefined behavior when executed. It ignores any input that it is
given.

[note_for_ub]
*/
//]

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

template< class Ret >
struct unreachable_function_fn
{
  //<-
  ARGOT_CONCEPT_ASSERT( ReturnType< Ret > );
  //->
  template< class... P >
  [[noreturn]]
  //<-
  BOOST_FORCEINLINE //->
  constexpr Ret operator()( P&&... ) const//=;
  //<-
  {
    ARGOT_DETAIL_UNREACHABLE();
  } //->
};

template< class Ret >
ARGOT_REQUIRES( ReturnType< Ret > )
< unreachable_function_fn< Ret > >
constexpr unreachable_function{};

} // namespace argot

//]

#endif  // ARGOT_UNREACHABLE_FUNCTION_HPP_
