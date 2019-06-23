/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STATE_TRAITS_LESS_THAN_HPP_
#define ARGOT_STATE_TRAITS_LESS_THAN_HPP_

#include <argot/concepts/comparable.hpp>
#include <argot/detail/declval.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/requires.hpp>

namespace argot::state_traits {

template< class T >
struct less_than_fn
{
  ARGOT_CONCEPT_ENSURE( Comparable< T > );

  constexpr bool operator ()( T const& lhs, T const& rhs ) const
  noexcept
  ( noexcept
    ( access_raw_concept_map< Comparable< T > >::less_than
      ( ARGOT_DECLVAL( T const& ), ARGOT_DECLVAL( T const& ) )
    )
  )
  {
    return access_raw_concept_map< Comparable< T > >::less_than( lhs, rhs );
  }
};

template< class T >
ARGOT_REQUIRES( Comparable< T > )
< less_than_fn< T > > constexpr less_than{};

}  // namespace (argot::state_traits)

#endif  // ARGOT_STATE_TRAITS_LESS_THAN_HPP_
