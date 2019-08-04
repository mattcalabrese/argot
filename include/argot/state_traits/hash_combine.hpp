/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STATE_TRAITS_HASH_COMBINE_HPP_
#define ARGOT_STATE_TRAITS_HASH_COMBINE_HPP_

#include <argot/concepts/hashable.hpp>
#include <argot/concepts/nothrow_hashable.hpp>
#include <argot/detail/declval.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>

#include <cstddef>
#include <memory>

namespace argot::state_traits {

template< class T >
struct hash_combine_fn
{
  //<-
  ARGOT_CONCEPT_ENSURE( Hashable< T > );
  //->
  constexpr void operator ()( std::size_t& curr, T const& state ) const
  noexcept( ARGOT_IS_MODELED( NothrowHashable< T > ) )//=;
  //<-
  {
    std::size_t old_hash = curr;

    curr ^=   access_raw_concept_map< Hashable< T > >::hash( state )
            + 0x9e3779b9
            + ( old_hash << 6 )
            + ( old_hash >> 2 );
  } //->
};

template< class T >
ARGOT_REQUIRES( Hashable< T > )
< hash_combine_fn< T > > constexpr hash_combine{};

} // namespace (argot::state_traits)

#endif  // ARGOT_STATE_TRAITS_HASH_COMBINE_HPP_
