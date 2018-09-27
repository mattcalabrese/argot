/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ALTERNATIVE_OF_HPP_
#define ARGOT_PROV_ALTERNATIVE_OF_HPP_

//[description
/*`
prov::alternative_of is a function object that returns a
PersistentArgumentProvider of the currently active alternative of a VariantLike
type.

[note The ArgumentProvider returned by prov::alternative_of captures the
VariantLike by reference. If the desire is for the VariantLike to be captured by
value, use prov::alternative_of_by_value instead.]

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/index_of.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/union_traits/natural_get.hpp>

#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct alternative_of_fn
{
  template< class Var
          , ARGOT_REQUIRES
            ( VariantLike< detail_argot::remove_cvref_t< Var > > )
            ( Not< VolatileObject< std::remove_reference_t< Var > > > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Var&& var ) const//=;
  //<-
  {
    return prov::lift_call
    ( union_traits::natural_get
    , prov::reference_to( ARGOT_FORWARD( Var )( var ) )
    , prov::index_of( var )
    );
  } //->
} inline constexpr alternative_of{};

template< class Var >
using result_of_alternative_of//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< alternative_of_fn const&, Var >; //->

template< class Var >
using result_of_alternative_of_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< alternative_of_fn const&, Var >; //->

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Var&& var`]
  [Forwarding-reference to a possibly-const VariantLike.
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
  [[itemized_list [```( union_traits::result_of_get_t< Var&&, variant_traits::index_of( var ) > )```]]]
 ]
 [[Possible Argument Types of Persistent Provision]
  [[itemized_list [```( union_traits::result_of_get_t< Var&, variant_traits::index_of( var ) > )```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_ALTERNATIVE_OF_HPP_
