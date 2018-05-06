/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/gen/associated_requirements.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>

#include <type_traits>

namespace {

template< class >
ARGOT_EXPLICIT_CONCEPT( Char )
(
);

template< class >
ARGOT_EXPLICIT_CONCEPT( Integral )
(
);

template< class >
ARGOT_AUTO_CONCEPT( AutoAll )
(
);

template< class T >
ARGOT_AUTO_CONCEPT( AutoChar )
(
  Char< T >
);

template< class T >
ARGOT_AUTO_CONCEPT( AutoCharIntegral )
(
  Char< T >
, Integral< T >
);

}  // namespace

namespace argot {

template<>
struct make_concept_map< Char< char > > {};

template< class T >
struct make_concept_map
< Integral< T >
, std::enable_if_t< std::is_integral_v< T > >
> {};

}  // namespace argot

namespace {

using argot::is_modeled;
using argot::is_modeled_v;

// Char
static_assert( is_modeled_v< Char< char > > );
static_assert( is_modeled< Char< char > >::value );
static_assert( !is_modeled_v< Char< void > > );
static_assert( !is_modeled< Char< void > >::value );

// Integral
static_assert( is_modeled_v< Char< char > > );
static_assert( is_modeled< Char< char > >::value );
static_assert( !is_modeled_v< Char< int > > );
static_assert( !is_modeled< Char< int > >::value );
static_assert( !is_modeled_v< Char< void > > );
static_assert( !is_modeled< Char< void > >::value );

// AutoAll
static_assert( is_modeled_v< AutoAll< int > > );
static_assert( is_modeled< AutoAll< int > >::value );
static_assert( is_modeled_v< AutoAll< void > > );
static_assert( is_modeled< AutoAll< void > >::value );

// AutoCharIntegral
static_assert( !is_modeled_v< AutoCharIntegral< int > > );
static_assert( !is_modeled< AutoCharIntegral< int > >::value );
static_assert( !is_modeled_v< AutoCharIntegral< void > > );
static_assert( !is_modeled< AutoCharIntegral< void > >::value );
static_assert( is_modeled_v< AutoCharIntegral< char > > );
static_assert( is_modeled< AutoCharIntegral< char > >::value );

}  // namespace
