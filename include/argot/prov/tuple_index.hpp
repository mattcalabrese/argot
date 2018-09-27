/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TO_TUPLE_INDEX_HPP_
#define ARGOT_PROV_TO_TUPLE_INDEX_HPP_

//[description
/*`
prov::tuple_index is a facility that takes a TupleLike type as an explicit
template parameter and an /index/ as a function parameter in the form of the
/index/ type of the TupleLike type or a `std::integral_constant` instantiation
of the /index/ type of the TupleLike type. It returns a
PersistentArgumentProvider that provides the /index/ as a
`std::integral_constant` instantiation.

TODO(mattcalabrese) Describe Default

[global_function_object_template_designator]
*/
//]

#include <argot/default_.hpp>
#include <argot/prov/value_in_range.hpp>
#include <argot/tuple_traits/index_type.hpp>
#include <argot/tuple_traits/num_elements.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

template< class Tup >
using tuple_index_fn
  = ARGOT_REQUIRES( TupleLike< Tup > )
    //=< ``[unspecified_type]`` >;
//<-
    < value_in_range_fn
      < tuple_traits::index_type_t< Tup >
      , 0, tuple_traits::num_elements_v< Tup >
      >
    >; //->

template< class Tup >
tuple_index_fn< Tup > constexpr tuple_index{};

template< class Tup, class V, class Def = argot::default_unreachable_t >
using result_of_tuple_index//= = ``[see_prologue_result_of]``;
//<-
  = result_of_value_in_range
    < tuple_traits::index_type_t< Tup >
    , 0, tuple_traits::num_elements_v< Tup >, V
    , Def
    >; //->

template< class Tup, class V, class Def = argot::default_unreachable_t >
using result_of_tuple_index_t//= = ``[see_prologue_result_of]``;
//<-
  = result_of_value_in_range_t
    < tuple_traits::index_type_t< Tup >
    , 0, tuple_traits::num_elements_v< Tup >, V
    , Def
    >; //->

} // namespace (argot::prov)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`class Tup`]
  [A TupleLike type]
  [The type for which `index` is a valid /index/]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`Index index`]
  [A value of the /index/ type of `Tup`, or `std::integral_constant` of the
   /index/ type of `Tup`, where the value is in the range
   \[0, `tuple_traits::num_elements_v< Tup >` )
  ]
  [The value that is to be provided in the form of a `std::integral_constant`
   instantiation
  ]
 ]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Tup` in ascending order.
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
  [[itemized_list [```( std::integral_constant< tuple_traits::index_type_t< Var >, i > )...```]]
   [itemized_list [[~The possible argument list kinds of `Def`]]]
  ]
  [[itemized_list [```( std::integral_constant< ValueType, index.value > )```]]]
  [[itemized_list [[~The possible argument list kinds of `Def`]]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_TO_TUPLE_INDEX_HPP_
