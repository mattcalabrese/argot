/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_INDEX_TYPE_HPP_
#define ARGOT_TUPLE_TRAITS_INDEX_TYPE_HPP_

//[description
/*`
tuple_traits::index_type_t is template alias that takes a TupleLike type and
resolves to the /index type/ to be used when accessing that TupleLike type.
*/
//]

#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::tuple_traits {

template< class Tup >
using index_type_t
  = ARGOT_REQUIRES( TupleLike< Tup > )
    //=< ``[unspecified_type]`` >;
//<-
    < typename access_raw_concept_map< TupleLike< Tup > >::index_type >; //->

// TODO(mattcalabrese) Remove
template< class Tup >
using index_type//= = ``[unspecified_type]``;
//<-
  = call_detail::lazy_expand< index_type_t, Tup >; //->

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

#endif  // ARGOT_TUPLE_TRAITS_INDEX_TYPE_HPP_
