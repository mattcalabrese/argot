/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_INDEX_CONSTANT_HPP_
#define ARGOT_TUPLE_TRAITS_INDEX_CONSTANT_HPP_

//[description
/*`
tuple_traits::index_constant_v is a variable template that takes a TupleLike
and an /index/ for that TupleLike as template parameters and resolves to an
instance of a `std::integral_constant` with the corresponding /index/ type and
value.
*/
//]

#include <argot/concepts/tuple_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/tuple_traits/index_type.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::tuple_traits {

template< class Tup, tuple_traits::index_type_t< Tup > Index >
using index_constant_t
  = ARGOT_REQUIRES( TupleLike< Tup > )
    < std::integral_constant< tuple_traits::index_type_t< Tup >, Index > >;

template< class Tup, tuple_traits::index_type_t< Tup > Index >
ARGOT_REQUIRES( TupleLike< Tup > )
< index_constant_t< Tup, Index > > constexpr index_constant_v{};

} // namespace (argot::tuple_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Tup`]
  [A TupleLike type]
  [The type whose /index/ type is to be used]
 ]
 [[`tuple_traits::index_type_t< Tup > Index`]
  [An instance of `tuple_traits::index_type_t< Tup >` ]
  [A value of the TupleLike's /index/ type to be used in the
   `std::integral_constant` instantiation that the variable template resolves to
  ]
 ]
]
*/

//]

#endif  // ARGOT_TUPLE_TRAITS_INDEX_CONSTANT_HPP_
