/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_ALTERNATIVE_OF_BY_VALUE_HPP_
#define ARGOT_CONC_ALTERNATIVE_OF_BY_VALUE_HPP_

//[description
/*`
conc::alternative_of_by_value is a function object that returns a
PersistentConcurrentArgumentProvider of the currently active alternative of a
VariantLike type.

[note The ConcurrentArgumentProvider returned by conc::alternative_of_by_value
      captures the VariantLike by value.
]
*/
//]

#include <argot/conc/lift_result.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/prov/alternative_of_by_value.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

struct alternative_of_by_value_fn
{
  template< class Var
          , ARGOT_REQUIRES
            ( VariantLike< detail_argot::remove_cvref_t< Var > > )
            ( Sinkable< Var&& > )
            ()
          >
  [[nodiscard]] constexpr auto operator ()( Var&& var ) const//=;
  //<-
  {
    return conc::lift_result
    ( prov::alternative_of_by_value
    , call_detail::forward_and_sink< Var >( var )
    );
  } //->
} inline constexpr alternative_of_by_value{};

template< class Var >
using result_of_alternative_of_by_value//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< alternative_of_by_value_fn const&, Var >; //->

template< class Var >
using result_of_alternative_of_by_value_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< alternative_of_by_value_fn const&, Var >; //->

} // namespace (argot::conc)

//]

#endif  // ARGOT_CONC_ALTERNATIVE_OF_BY_VALUE_HPP_
