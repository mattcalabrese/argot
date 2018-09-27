/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_UNPACK_BY_VALUE_HPP_
#define ARGOT_CONC_UNPACK_BY_VALUE_HPP_

//[description
/*`
conc::unpack_by_value is used to expand out all of the elements of a TupleLike
type in-place in an argument list.

[note A call to conc::unpack_by_value captures `tup` by value.]
*/
//]

#include <argot/conc/lift_result.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/prov/unpack_by_value.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

struct unpack_by_value_fn
{
  template< class Tup
          , ARGOT_REQUIRES
            ( TupleLike< detail_argot::remove_cvref_t< Tup > > )
            ( Sinkable< Tup&& > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Tup&& tup ) const//=;
  //<-
  {
    return conc::lift_result
    ( prov::unpack_by_value, call_detail::forward_and_sink< Tup >( tup ) );
  } //->
} inline constexpr unpack_by_value{};

template< class Tup >
using result_of_unpack_by_value//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< unpack_by_value_fn const&, Tup >; //->

template< class Tup >
using result_of_unpack_by_value_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< unpack_by_value_fn const&, Tup >; //->

} // namespace (argot::conc)

//]

#endif  // ARGOT_CONC_UNPACK_BY_VALUE_HPP_
