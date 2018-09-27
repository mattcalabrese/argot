/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[description
/*`
union_traits::num_alternatives_v is variable template that takes a
UnionLike and resolves to a `constexpr` value corresponding to the number of
/alternatives/ of that type.
*/
//]

#ifndef ARGOT_UNION_TRAITS_NUM_ALTERNATIVES_HPP_
#define ARGOT_UNION_TRAITS_NUM_ALTERNATIVES_HPP_

#include <argot/concepts/union_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/index_type.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::union_traits {

// TODO(mattcalabrese) Remove
template< class Un >
using num_alternatives_t
  = ARGOT_REQUIRES( UnionLike< Un > )
    < std::integral_constant
      < index_type_t< Un >
      , access_raw_concept_map< UnionLike< Un > >::num_alternatives
      >
    >;

// TODO(mattcalabrese) Remove
template< class Un >
using num_alternatives
  = call_detail::lazy_inherit< num_alternatives_t, Un >;

template< class Un >
ARGOT_REQUIRES( UnionLike< Un > )
< index_type_t< Un > > constexpr num_alternatives_v
  = num_alternatives_t< Un >::value;

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

#endif  // ARGOT_UNION_TRAITS_NUM_ALTERNATIVES_HPP_
