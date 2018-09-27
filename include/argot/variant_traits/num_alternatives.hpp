/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_NUM_ALTERNATIVES_HPP_
#define ARGOT_VARIANT_TRAITS_NUM_ALTERNATIVES_HPP_

//[description
/*`
variant_traits::num_alternatives_v is variable template that takes a
VariantLike and resolves to a `constexpr` value corresponding to the number of
/alternatives/ of that type.
*/
//]

#include <argot/concepts/variant_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/num_alternatives.hpp>
#include <argot/variant_traits/index_type.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::variant_traits {

template< class Var >
using num_alternatives_t
  = ARGOT_REQUIRES( VariantLike< Var > )
    < union_traits::num_alternatives_t< Var > >;

template< class Var >
using num_alternatives
  = call_detail::lazy_inherit< num_alternatives_t, Var >;

// TODO(mattcalabrese) Remove
template< class Var >
ARGOT_REQUIRES( VariantLike< Var > )
< index_type_t< Var > > constexpr num_alternatives_v
  = num_alternatives_t< Var >::value;

} // namespace (argot::variant_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Var`]
  [A VariantLike type]
  [The type to introspect]
 ]
]
*/

//]

#endif  // ARGOT_VARIANT_TRAITS_NUM_ALTERNATIVES_HPP_
