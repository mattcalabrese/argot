/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_INTEGER_SEQUENCE_HPP_
#define ARGOT_PROV_INTEGER_SEQUENCE_HPP_

//[description
/*`
prov::integer_sequence is used to expand out all of the values in the range
\[`0`, `Size`) in ascending order in a single argument list in the form of their
corresponding `std::integral_constant` instantiation.

[global_object_template_designator]
*/
//]

#include <argot/prov/unpack_integer_sequence.hpp>

#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

// TODO(mattcalabrese) Test the remove_const
// TODO(mattcalabrese) Require integral type (std requires it)
template< auto Size >
using integer_sequence_t
  = result_of_unpack_integer_sequence_t
    < std::make_integer_sequence
      < std::remove_const_t< decltype( Size ) >, Size >
    >;

template< auto Size >
integer_sequence_t< Size > constexpr integer_sequence{};

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`auto Size`]
  [A non-negative Integral value]
  [The upper-bound (exclusive) of the range of values to provide]
 ]
]

[provider_properties_heading]

[note In the following tables, assume `i` is a parameter pack of all valid
      /indices/ of `tup` in ascending order.
]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision]
  [A `std::integral_constant` for each value in the range \[`0`, `Size`)]
 ]
 [[Possible Argument Types of Provision]
  [[itemized_list [```( std::integral_constant< decltype( i ), i >... )```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_INTEGER_SEQUENCE_HPP_
