/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ACCESS_VARIANT_HPP_
#define ARGOT_PROV_ACCESS_VARIANT_HPP_

//[description
/*`
prov::access_variant is a function object that returns an ArgumentProvider of a
single alternative of a VariantLike type using an index that may be either a
compile-time constant or a run-time value.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/default_.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/union_index.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/union_traits/natural_get.hpp>
#include <argot/variant_traits/index_type.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct access_variant_fn
{
  template< class Var, class Index, class Def = argot::default_unreachable_t
          , ARGOT_REQUIRES
            ( VariantLike< detail_argot::remove_cvref_t< Var > > )
            ( Not< VolatileObject< std::remove_reference_t< Var > > > )
            ( ConvertibleToTypeOrConstant
              < Index
              , variant_traits::index_type_t
                < detail_argot::remove_cvref_t< Var > >
              >
            )
            ( Default< Def > )
            ()
          >
  [[nodiscard]] constexpr auto operator ()
  ( Var&& var, Index&& index, Def def = Def() ) const//=;
  //<-
  {
    return prov::lift_call
    ( union_traits::natural_get
    , prov::reference_to( ARGOT_FORWARD( Var )( var ) )
    , prov::union_index< detail_argot::remove_cvref_t< Var > >
      ( ARGOT_FORWARD( Index )( index ), ARGOT_MOVE( def ) )
    );
  } //->
} inline constexpr access_variant{};

template< class Var, class Index, class Def = argot::default_unreachable_t >
using result_of_access_variant//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< access_variant_fn const&, Var, Index, Def >; //->

template< class Var, class Index, class Def = argot::default_unreachable_t >
using result_of_access_variant_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< access_variant_fn const&, Var, Index, Def >; //->

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Var&& var`]
  [Forwarding-reference to a possibly-const VariantLike]
  [The VariantLike of which an alternative is to be provided]
 ]
 [[`Index&& index`]
  [Either: [ordered_list [Forwarding-reference convertible to `var`'s index
  type /or/][Forwarding-reference to a `std::integral_constant` with var's
  index type as the value type.]]
  ]
  [The index of the alternative to be provided]
 ]
 [[`Def def`]
  [A model of Default]
  [The handler to be used if `index` is out of range for `var`]
 ]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Var` in ascending order.
]

[table Resultant Provider
 [[Property][Dynamic Index][Static Index]]
 [[Logical Provision][Reference to the corresponding alternative]
                     [Reference to the corresponding alternative]]
 [[Possible Argument Types]
  [[itemized_list [```( variant_traits::result_of_get_t< Var&&, i > )...```]]]
  [[itemized_list [```( variant_traits::result_of_get_t< Var&&, index.value > )```]]]
 ]
]
*/
//]

#endif  // ARGOT_PROV_ACCESS_VARIANT_HPP_
