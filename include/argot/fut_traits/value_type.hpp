/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUTURE_TRAITS_VALUE_TYPE_HPP_
#define ARGOT_FUTURE_TRAITS_VALUE_TYPE_HPP_

//[description
/*`
fut_traits::value_type_t is a template alias that takes a Future type and
resolves to the /value type/ of that Future.
*/
//]

#include <argot/concepts/future.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/lazy_expand.hpp>

#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::fut_traits {

template< class Fut >
using value_type_t
  = ARGOT_REQUIRES( Future< Fut > )
    //=< ``[unspecified_type]`` >;
//<-
    < typename access_raw_concept_map< Future< Fut > >::value_type_t >;
//->

// TODO(mattcalabrese) Remove
template< class Fut >
using value_type//= = ``[unspecified_type]``;
//<-
  = lazy_expand< value_type_t, Fut >;
//->

} // namespace (argot::fut_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Fut`]
  [A Future type]
  [The type to introspect]
 ]
]
*/

//]

#endif  // ARGOT_FUTURE_TRAITS_VALUE_TYPE_HPP_
