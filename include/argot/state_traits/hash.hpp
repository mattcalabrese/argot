/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STATE_TRAITS_HASH_HPP_
#define ARGOT_STATE_TRAITS_HASH_HPP_

//[description
/*`
state_traits::hash is a facility for calculating a hashed value for a
user-specified type `T`.

[note The default /concept map/ for object types uses `std::hash< T >`. For
      reference types, `std::hash< std::remove_reference_t< T >* >` is used.
]
*/
//]

#include <argot/concepts/hashable.hpp>
#include <argot/concepts/nothrow_hashable.hpp>
#include <argot/detail/declval.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>

#include <cstddef>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::state_traits {

template< class T >
struct hash_fn
{
  //<-
  ARGOT_CONCEPT_ENSURE( Hashable< T > );
  //->
  [[nodiscard]]
  constexpr std::size_t operator ()( T const& arg ) const
  noexcept( ARGOT_IS_MODELED( NothrowHashable< T > ) )//=;
  //<-
  {
    return access_raw_concept_map< Hashable< T > >::hash( arg );
  } //->
};

template< class T >
ARGOT_REQUIRES( Hashable< T > )
< hash_fn< T > > constexpr hash{};

} // namespace (argot::state_traits)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`class T`]
  [A Hashble type]
  [The type of the entity to be hashed]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`T const& arg`]
  [A reference-to-const `T`]
  [The argument to obtain a hashed value from]
 ]
]
*/

//]

#endif  // ARGOT_STATE_TRAITS_HASH_HPP_
