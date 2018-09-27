/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_ALTERNATIVE_TYPE_HPP_
#define ARGOT_VARIANT_TRAITS_ALTERNATIVE_TYPE_HPP_

//[description
/*`
variant_traits::alternative_type_t is a template alias that takes a VariantLike
type along with an /index/ and resolves to the corresponding /alternative/'s
type.
*/
//]

#include <argot/concepts/variant_index.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/alternative_type.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::variant_traits {

template< class Var, auto Index >
using alternative_type_t
  = ARGOT_REQUIRES( VariantLike< Var > )
                  ( VariantIndex< Var, Index > )
    //=< ``[unspecified_type]`` >;
//<-
    < typename union_traits::alternative_type_t< Var, Index > >;
//->

// TODO(mattcalabrese) Remove
template< class Var, auto Index >
using alternative_type//= = ``[unspecified_type]``;
//<-
  = call_detail::lazy_expand_access< alternative_type_t, Var, Index >;
//->

} // namespace (argot::variant_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Var`]
  [A VariantLike type]
  [The type to introspect]
 ]
 [[`auto Index`]
  [An integral value in the range \[0, `variant_traits::num_alternatives_v< Var >`)]
  [The index of an /alternative/ of `Var` whose type is to be retrieved]
 ]
]
*/

//]

#endif  // ARGOT_VARIANT_TRAITS_ALTERNATIVE_TYPE_HPP_
