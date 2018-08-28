/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STATE_TRAITS_EQUAL_TO_HPP_
#define ARGOT_STATE_TRAITS_EQUAL_TO_HPP_

#include <argot/concepts/equatable.hpp>
#include <argot/declval.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/requires.hpp>

namespace argot::state_traits {

template< class T >
struct equal_to_fn
{
  ARGOT_CONCEPT_ENSURE( Equatable< T > );

  constexpr bool operator ()( T const& lhs, T const& rhs ) const
  noexcept
  ( noexcept( access_raw_concept_map< Equatable< T > >::equal_to( lhs, rhs) ) )
  {
    return access_raw_concept_map< Equatable< T > >::equal_to( lhs, rhs );
  }
};

template< class T >
ARGOT_REQUIRES( Equatable< T > )
< equal_to_fn< T > > constexpr equal_to{};

}  // namespace (argot::state_traits)

#endif  // ARGOT_STATE_TRAITS_EQUAL_TO_HPP_
