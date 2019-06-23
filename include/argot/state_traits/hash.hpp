/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STATE_TRAITS_HASH_HPP_
#define ARGOT_STATE_TRAITS_HASH_HPP_

#include <argot/concepts/hashable.hpp>
#include <argot/concepts/nothrow_hashable.hpp>
#include <argot/detail/declval.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>

#include <cstddef>

namespace argot::state_traits {

template< class T >
struct hash_fn
{
  ARGOT_CONCEPT_ENSURE( Hashable< T > );

  constexpr std::size_t operator ()( T const& arg ) const
  noexcept( ARGOT_IS_MODELED( NothrowHashable< T > ) )
  {
    return access_raw_concept_map< Hashable< T > >::hash( arg );
  }
};

template< class T >
ARGOT_REQUIRES( Hashable< T > )
< hash_fn< T > > constexpr hash{};

}  // namespace (argot::state_traits)

#endif  // ARGOT_STATE_TRAITS_HASH_HPP_
