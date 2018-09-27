/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_INDEX_TYPE_HPP_
#define ARGOT_UNION_TRAITS_INDEX_TYPE_HPP_

//[description
/*`
union_traits::index_type_t is template alias that takes a UnionLike type and
resolves to the /index type/ to be used when accessing that UnionLike type.
*/
//]

#include <argot/concepts/union_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::union_traits {

template< class Un >
using index_type_t
  = ARGOT_REQUIRES( UnionLike< Un > )
    //=< ``[unspecified_type]`` >;
//<-
    < typename access_raw_concept_map< UnionLike< Un > >::index_type >; //->

// TODO(mattcalabrese) Remove
template< class Un >
using index_type//= = ``[unspecified_type]``;
//<-
  = call_detail::lazy_expand< index_type_t, Un >; //->

} // namespace (argot::union_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Un`]
  [A UnionLike type]
  [The type to introspect]
 ]
]
*/

//]

#endif  // ARGOT_UNION_TRAITS_INDEX_TYPE_HPP_
