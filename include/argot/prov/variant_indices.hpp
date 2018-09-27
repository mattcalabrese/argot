/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_VARIANT_INDICES_HPP_
#define ARGOT_PROV_VARIANT_INDICES_HPP_

//[description
/*`
prov::variant_indices is used to expand out the valid /indices/ of a
VariantLike type as separate arguments, each in the form of the corresponding
`std::integral_constant` instantiation.

[global_object_template_designator]
*/
//]

#include <argot/concepts/variant_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/integer_sequence.hpp>
#include <argot/variant_traits/num_alternatives.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

template< class Var >
using variant_indices_t
  = ARGOT_REQUIRES( VariantLike< Var > )
    //=< ``[unspecified_type]`` >;
//<-
    < integer_sequence_t< variant_traits::num_alternatives_v< Var > > >;
//->

template< class Var >
ARGOT_REQUIRES( VariantLike< Var > )
< variant_indices_t< Var > > constexpr variant_indices{};

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Var`]
  [A VariantLike type]
  [The VariantLike type whose valid /indices/ are to be provided]
 ]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Var` in ascending order.
]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision]
  [A `std::integral_constant` corresponding to each valid /index/ of `Var`]
 ]
 [[Possible Argument Types of Provision]
  [[itemized_list [```( std::integral_constant< variant_traits::index_type_t< Var >, i >... )```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_VARIANT_INDICES_HPP_
