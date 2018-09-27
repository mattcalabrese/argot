/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TO_VARIANT_INDEX_HPP_
#define ARGOT_PROV_TO_VARIANT_INDEX_HPP_

//[description
/*`
prov::variant_index is used to "convert" a possibly-non-constant /index/ of a
given VariantLike type to its corresponding `std::integral_constant`. If the
input value is not a valid /index/ for the VariantLike type, then a Default
is used.

[note If no explicit Default argument is provided, then
      argot::default_unreachable is used.
]

[global_function_object_template_designator]
*/
//]

#include <argot/default_.hpp>
#include <argot/prov/value_in_range.hpp>
#include <argot/variant_traits/index_type.hpp>
#include <argot/variant_traits/num_alternatives.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

template< class Var >
using variant_index_fn
  = prov::value_in_range_fn
    < variant_traits::index_type_t< Var >
    , 0, variant_traits::num_alternatives_v< Var >
    >;

template< class Var >
constexpr variant_index_fn< Var > variant_index{};

template< class Var, class V, class Def = argot::default_unreachable_t >
using result_of_variant_index//= = ``[see_prologue_result_of]``;
//<-
  = result_of_value_in_range
    < variant_traits::index_type_t< Var >
    , 0, variant_traits::num_alternatives_v< Var >, V
    , Def
    >; //->

template< class Var, class V, class Def = argot::default_unreachable_t >
using result_of_variant_index_t//= = ``[see_prologue_result_of]``;
//<-
  = result_of_value_in_range_t
    < variant_traits::index_type_t< Var >
    , 0, variant_traits::num_alternatives_v< Var >, V
    , Def
    >; //->

} // namespace (argot::prov)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`class Var`]
  [A VariantLike type]
  [The type for which `index` is a valid /index/]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`ValueType index`]
  [A value of the /index/ type of `Var`, or `std::integral_constant` of the
   /index/ type of `Var`, where the value is in the range
   \[0, `variant_traits::num_alternatives_v< Var >` )
  ]
  [The value that is to be provided in the form of a `std::integral_constant`
   instantiation
  ]
 ]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Var` in ascending order.
]

[table Resultant Provider
 [[Property][Dynamic Index][Static Index in Range][Static Index Not in Range]]
 [[Logical Provision]
  [The /value/ as a `std::integral_constant` instantiation or what `Def`
   provides when passed /value/
  ]
  [The /value/ as a `std::integral_constant` instantiation]
  [What `Def` provides when passed /value/]
 ]
 [[Possible Argument Types]
  [[itemized_list [```( std::integral_constant< variant_traits::index_type_t< Var >, i > )...```]]
   [itemized_list [[~The possible argument list kinds of `Def`]]]
  ]
  [[itemized_list [```( std::integral_constant< ValueType, index.value > )```]]]
  [[itemized_list [[~The possible argument list kinds of `Def`]]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_TO_CONSTANT_VARIANT_INDEX_HPP_
