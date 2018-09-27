/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_INDEX_CONSTANT_HPP_
#define ARGOT_UNION_TRAITS_INDEX_CONSTANT_HPP_

//[description
/*`
union_traits::index_constant_v is a variable template that takes a UnionLike
and an /index/ for that UnionLike as template parameters and resolves to an
instance of a `std::integral_constant` with the corresponding /index/ type and
value.
*/
//]

#include <argot/union_traits/index_type.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::union_traits {

template< class Un, union_traits::index_type_t< Un > Index >
using index_constant_t
  = std::integral_constant< union_traits::index_type_t< Un >, Index >;

template< class Un, union_traits::index_type_t< Un > Index >
constexpr index_constant_t< Un, Index > index_constant_v{};

} // namespace (argot::union_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Un`]
  [A UnionLike type]
  [The type whose /index/ type is to be used]
 ]
 [[`union_traits::index_type_t< Un > Index`]
  [An instance of `union_traits::index_type_t< Un >` ]
  [A value of the UnionLike's /index/ type to be used in the
   `std::integral_constant` instantiation that the variable template resolves to
  ]
 ]
]
*/

//]

#endif  // ARGOT_UNION_TRAITS_INDEX_CONSTANT_HPP_
