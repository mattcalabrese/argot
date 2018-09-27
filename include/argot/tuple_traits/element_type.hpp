/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_ELEMENT_TYPE_HPP_
#define ARGOT_TUPLE_TRAITS_ELEMENT_TYPE_HPP_

//[description
/*`
tuple_traits::element_type_t is a template alias that takes a TupleLike type
along with an /index/ and resolves to the corresponding /element/'s type.
*/
//]

#include <argot/concepts/tuple_index.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/tuple_traits/index_type.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::tuple_traits {

template< class Tup, auto Index >
using element_type_t
  = ARGOT_REQUIRES( TupleLike< Tup > )
                  ( TupleIndex< Tup, Index > )
    //=< ``[unspecified_type]`` >;
//<-
    < typename access_raw_concept_map< TupleLike< Tup > >
      ::template element_type_t< Index >
    >;
//->

// TODO(mattcalabrese) Remove
template< class Tup, auto Index >
using element_type//= = ``[unspecified_type]``;
//<-
  = call_detail::lazy_expand_access< element_type_t, Tup, Index >;
//->

} // namespace (argot::tuple_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Tup`]
  [A TupleLike type]
  [The type to introspect]
 ]
 [[`auto Index`]
  [An integral value in the range \[0, `tuple_traits::num_elements_v< Tup >`)]
  [The index of an /element/ of `Tup` whose type is to be retrieved]
 ]
]
*/

//]

#endif  // ARGOT_TUPLE_TRAITS_ELEMENT_TYPE_HPP_
