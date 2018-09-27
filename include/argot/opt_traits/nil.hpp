/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPT_TRAITS_NIL_HPP_
#define ARGOT_OPT_TRAITS_NIL_HPP_

//[description
/*`
opt_traits::nil is a unary type template taking a `class T`. Instantiations of
opt_traits::nil are intended to represent the lack of a `T`. 

[note An instance of `opt_traits::nil< T >` is logically contained in an
      OptionalLike of /element type/ `T` whenever it is in a /disengaged/ state.
]
*/
//]

#include <argot/detail/regular_monostate_base.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::opt_traits {

// TODO(mattcalabrese) Describe the type as having all comparisons, etc.
template< class T >
struct nil //={};
//<-
  : private argot_detail::regular_monostate_base< nil< T > > {}; //->

} // namespace (argot::opt_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class T`]
  [A type]
  [The type that the instantiation of `opt_traits::nil< T >` represents a lack
   of
  ]
 ]
]
*/

//]

namespace std {

template< class T >
struct hash;

template< class T >
ARGOT_DETAIL_MONOSTATE_HASH_DEFINITION( ::argot::opt_traits::nil< T > );

} // namespace std

#endif  // ARGOT_OPT_TRAITS_NIL_HPP_
