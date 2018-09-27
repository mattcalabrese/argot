/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_UNION_INDICES_HPP_
#define ARGOT_PROV_UNION_INDICES_HPP_

//[description
/*`
prov::union_indices is used to expand out the valid /indices/ of a
UnionLike type as separate arguments, each in the form of the corresponding
`std::integral_constant` instantiation.

[global_object_template_designator]
*/
//]

#include <argot/concepts/union_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/integer_sequence.hpp>
#include <argot/union_traits/num_alternatives.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

template< class Un >
using union_indices_t
  = ARGOT_REQUIRES( UnionLike< Un > )
    //=< ``[unspecified_type]`` >;
//<-
    < integer_sequence_t< union_traits::num_alternatives_v< Un > > >;
//->

template< class Un >
ARGOT_REQUIRES( UnionLike< Un > )
< union_indices_t< Un > > constexpr union_indices{};

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Un`]
  [A UnionLike type]
  [The UnionLike type whose valid /indices/ are to be provided]
 ]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Un` in ascending order.
]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision]
  [A `std::integral_constant` corresponding to each valid /index/ of `Un`]
 ]
 [[Possible Argument Types of Provision]
  [[itemized_list [```( std::integral_constant< union_traits::index_type_t< Un >, i >... )```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_UNION_INDICES_HPP_
