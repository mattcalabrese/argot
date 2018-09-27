/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_NUM_ELEMENTS_HPP_
#define ARGOT_TUPLE_TRAITS_NUM_ELEMENTS_HPP_

//[description
/*`
tuple_traits::num_elements_v is variable template that takes a TupleLike and
resolves to a `constexpr` value corresponding to the number of /elements/ of
that type.
*/
//]

#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/tuple_traits/index_type.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::tuple_traits {

// TODO(mattcalabrese) Remove
template< class Tup >
using num_elements_t
  = ARGOT_REQUIRES( TupleLike< Tup > )
    < std::integral_constant
      < tuple_traits::index_type_t< Tup >
      , access_raw_concept_map< TupleLike< Tup > >::num_elements
      >
    >;

// TODO(mattcalabrese) Remove
template< class Tup >
using num_elements = call_detail::lazy_inherit< num_elements_t, Tup >;

template< class Tup >
ARGOT_REQUIRES( TupleLike< Tup > )
< tuple_traits::index_type_t< Tup > > constexpr num_elements_v
  = num_elements< Tup >::value;

} // namespace (argot::tuple_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Tup`]
  [A TupleLike type]
  [The type to introspect]
 ]
]
*/

//]

#endif  // ARGOT_TUPLE_TRAITS_NUM_ELEMENTS_HPP_
