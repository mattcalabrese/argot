/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPT_TRAITS_ELEMENT_TYPE_HPP_
#define ARGOT_OPT_TRAITS_ELEMENT_TYPE_HPP_

//[description
/*`
opt_traits::element_type_t is a template alias that takes an OptionalLike
type and resolves to the /element/ type of that OptionalLike.
*/
//]

#include <argot/concepts/optional_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::opt_traits {

template< class Opt >
using element_type_t
  = ARGOT_REQUIRES( OptionalLike< Opt > )
    //=< ``[unspecified_type]`` >;
//<-
    < typename access_raw_concept_map< OptionalLike< Opt > >::element_type_t >;
//->

// TODO(mattcalabrese) Remove
template< class Opt >
using element_type//= = ``[unspecified_type]``;
//<-
  = call_detail::lazy_expand< element_type_t, Opt >;
//->

} // namespace (argot::opt_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Opt`]
  [An OptionalLike type]
  [The type to introspect]
 ]
]
*/

//]

#endif  // ARGOT_OPT_TRAITS_ELEMENT_TYPE_HPP_
