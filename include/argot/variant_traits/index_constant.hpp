/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_INDEX_CONSTANT_HPP_
#define ARGOT_VARIANT_TRAITS_INDEX_CONSTANT_HPP_

//[description
/*`
variant_traits::index_constant_v is a variable template that takes a VariantLike
and an /index/ for that VariantLike as template parameters and resolves to an
instance of a `std::integral_constant` with the corresponding /index/ type and
value.
*/
//]

#include <argot/union_traits/index_constant.hpp>
#include <argot/variant_traits/index_type.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::variant_traits {

template< class Var, variant_traits::index_type_t< Var > Index >
using index_constant_t = union_traits::index_constant_t< Var, Index >;

template< class Var, variant_traits::index_type_t< Var > Index >
constexpr index_constant_t< Var, Index > index_constant_v{};

} // namespace (argot::variant_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Var`]
  [A VariantLike type]
  [The type whose /index/ type is to be used]
 ]
 [[`variant_traits::index_type_t< Var > Index`]
  [An instance of `variant_traits::index_type_t< Var >` ]
  [A value of the VariantLike's /index/ type to be used in the
   `std::integral_constant` instantiation that the variable template resolves to
  ]
 ]
]
*/

//]

#endif  // ARGOT_VARIANT_TRAITS_INDEX_CONSTANT_HPP_
