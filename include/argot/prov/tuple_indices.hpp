/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TUPLE_INDICES_HPP_
#define ARGOT_PROV_TUPLE_INDICES_HPP_

//[description
/*`
prov::tuple_indices is used to expand out the valid /indices/ of a
TupleLike type as separate arguments, each in the form of the corresponding
`std::integral_constant` instantiation.

[global_object_template_designator]
*/
//]

#include <argot/concepts/tuple_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/integer_sequence.hpp>
#include <argot/tuple_traits/num_elements.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

template< class Tup >
using tuple_indices_t
  = ARGOT_REQUIRES( TupleLike< Tup > )
    //=< ``[unspecified_type]`` >;
//<-
    < integer_sequence_t< tuple_traits::num_elements_v< Tup > > >;
//->

template< class Tup >
ARGOT_REQUIRES( TupleLike< Tup > )
< tuple_indices_t< Tup > > constexpr tuple_indices{};

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Tup`]
  [A TupleLike type]
  [The TupleLike type whose valid /indices/ are to be provided]
 ]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Tup` in ascending order.
]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision]
  [A `std::integral_constant` corresponding to each valid /index/ of `Tup`]
 ]
 [[Possible Argument Types of Provision]
  [[itemized_list [```( std::integral_constant< tuple_traits::index_type_t< Tup >, i >... )```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_TUPLE_INDICES_HPP_
