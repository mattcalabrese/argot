/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_ALTERNATIVE_TYPE_HPP_
#define ARGOT_UNION_TRAITS_ALTERNATIVE_TYPE_HPP_

//[description
/*`
union_traits::alternative_type_t is a template alias that takes a UnionLike type
along with an /index/ and resolves to the corresponding /alternative/'s type.
*/
//]

#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/index_type.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::union_traits {

template< class Un, auto Index >
using alternative_type_t
  = ARGOT_REQUIRES( UnionLike< Un > )
                  ( UnionIndex< Un, Index > )
    //=< ``[unspecified_type]`` >;
//<-
    < typename access_raw_concept_map< UnionLike< Un > >
      ::template alternative_type_t< Index >
    >;
//->

// TODO(mattcalabrese) Remove
template< class Un, auto Index >
using alternative_type//= = ``[unspecified_type]``;
//<-
  = call_detail::lazy_expand_access< alternative_type_t, Un, Index >;
//->

} // namespace (argot::union_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Un`]
  [A UnionLike type]
  [The type to introspect]
 ]
 [[`auto Index`]
  [An integral value in the range \[0, `union_traits::num_alternatives_v< Un >`)]
  [The index of an /alternative/ of `Un` whose type is to be retrieved]
 ]
]
*/

//]

#endif  // ARGOT_UNION_TRAITS_ALTERNATIVE_TYPE_HPP_
