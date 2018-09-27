/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ALTERNATIVE_OF_BY_VALUE_HPP_
#define ARGOT_PROV_ALTERNATIVE_OF_BY_VALUE_HPP_

//[description
/*`
prov::alternative_of_by_value is a function object that returns a
PersistentArgumentProvider of the currently active alternative of a VariantLike
type.

[note The ArgumentProvider returned by prov::alternative_of_by_value captures
the VariantLike by value. If the desire is for the VariantLike to be captured by
reference, use prov::alternative_of instead.]

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/index_of.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/union_traits/natural_get.hpp>
#include <argot/detail/remove_cvref.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct alternative_of_by_value_fn
{
  template< class Var
          , ARGOT_REQUIRES
            ( VariantLike< detail_argot::remove_cvref_t< Var > > )
            ( Sinkable< Var&& > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Var&& var ) const//=;
  //<-
  {
    return prov::lift_call
    ( union_traits::natural_get
    , prov::value_of( call_detail::forward_and_sink< Var >( var ) )
    , prov::index_of( var )
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

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Var&& var`]
  [Forwarding-reference to a possibly-cv-qualified VariantLike that is Sinkable.
   The VariantLike must have an active alternative
   (it must not be in a partially-formed or `valueless_by_exception` state).
  ]
  [The VariantLike for which the currently active alternative is to be provided]
 ]
]

[provider_properties_heading]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision][Reference to the currently active alternative]]
 [[Possible Argument Types of Destructive Provision]
  [[itemized_list [```( union_traits::result_of_get_t< std::remove_cvref_t< Var >&&, variant_traits::index_of( var ) > )```]]]
 ]
 [[Possible Argument Types of Persistent Provision]
  [[itemized_list [```( union_traits::result_of_get_t< std::remove_cvref_t< Var > const&, variant_traits::index_of( var ) > )```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_ALTERNATIVE_OF_BY_VALUE_HPP_
