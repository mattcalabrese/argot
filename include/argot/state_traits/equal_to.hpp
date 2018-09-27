/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STATE_TRAITS_EQUAL_TO_HPP_
#define ARGOT_STATE_TRAITS_EQUAL_TO_HPP_

//[description
/*`
state_traits::equal_to is a facility for comparing two entities for equality
with respect to the Equatable concept.

[note The default /concept map/ for object types uses `==` to check for
      equality. Two references are only considered equal if they refer to the
      same entity.
]
*/
//]

#include <argot/concepts/equatable.hpp>
#include <argot/detail/declval.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::state_traits {

template< class T >
struct equal_to_fn
{
  //<-
  ARGOT_CONCEPT_ENSURE( Equatable< T > );
  //->
  [[nodiscard]]
  constexpr bool operator ()( T const& lhs, T const& rhs ) const//=;
  //<-
  noexcept
  ( noexcept( access_raw_concept_map< Equatable< T > >::equal_to( lhs, rhs) ) )
  {
    return access_raw_concept_map< Equatable< T > >::equal_to( lhs, rhs );
  } //->
};

template< class T >
ARGOT_REQUIRES( Equatable< T > )
< equal_to_fn< T > > constexpr equal_to{};

} // namespace (argot::state_traits)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`class T`]
  [An Equatable type]
  [The type of the entities to be compared]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`T const& lhs`]
  [A reference-to-const `T`]
  [The first argument of the comparison]
 ]
 [[`T const& rhs`]
  [A reference-to-const `T`]
  [The second argument of the comparison]
 ]
]
*/

//]

#endif  // ARGOT_STATE_TRAITS_EQUAL_TO_HPP_
