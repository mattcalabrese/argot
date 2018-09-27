/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_INDEX_TYPE_HPP_
#define ARGOT_VARIANT_TRAITS_INDEX_TYPE_HPP_

//[description
/*`
variant_traits::index_type_t is template alias that takes a VariantLike type and
resolves to the /index type/ to be used when accessing that VariantLike type.
*/
//]

#include <argot/concepts/variant_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/index_type.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::variant_traits {

template< class Var >
using index_type_t
  = ARGOT_REQUIRES( VariantLike< Var > )
    //=< ``[unspecified_type]`` >;
//<-
    < typename union_traits::index_type_t< Var > >; //->

// TODO(mattcalabrese) Remove
template< class Var >
using index_type//= = ``[unspecified_type]``;
//<-
 = call_detail::lazy_inherit< index_type_t, Var >; //->

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

#endif  // ARGOT_VARIANT_TRAITS_INDEX_TYPE_HPP_
