/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STATE_TRAITS_LESS_EQUAL_HPP_
#define ARGOT_STATE_TRAITS_LESS_EQUAL_HPP_

//[description
/*`
state_traits::less_equal is a facility for determining if an entity is less than
or equal to another entity with respect to the Comparable concept.

[note The default /concept map/ for object types uses `<=` if present, otherwise
      it calculates `a <= b` by way of `!( b < a )`. If `T` is a reference type,
      the comparison is performed as if the address of each target were used.
]
*/
//]

#include <argot/concepts/comparable.hpp>
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
struct less_equal_fn
{
  //<-
  ARGOT_CONCEPT_ENSURE( Comparable< T > );
  //->
  [[nodiscard]]
  constexpr bool operator ()( T const& lhs, T const& rhs ) const//=;
  //<-
  noexcept
  ( noexcept
    ( access_raw_concept_map< Comparable< T > >::less_equal
      ( ARGOT_DECLVAL( T const& ), ARGOT_DECLVAL( T const& ) )
    )
  )
  {
    return access_raw_concept_map< Comparable< T > >::less_equal( lhs, rhs );
  } //->
};

template< class T >
ARGOT_REQUIRES( Comparable< T > )
< less_equal_fn< T > > constexpr less_equal{};

} // namespace (argot::state_traits)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`class T`]
  [A Comparable type]
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

#endif  // ARGOT_STATE_TRAITS_LESS_EQUAL_HPP_
