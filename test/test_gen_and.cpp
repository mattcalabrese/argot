/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/and.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>

namespace {

template< class >
ARGOT_EXPLICIT_CONCEPT( Int )
(
);

template< class >
ARGOT_EXPLICIT_CONCEPT( Char )
(
);

template< class >
ARGOT_EXPLICIT_CONCEPT( Float )
(
);

}  // namespace

namespace argot {

template<>
struct make_concept_map< Int< int > > {};

template<>
struct make_concept_map< Char< char > > {};

template<>
struct make_concept_map< Float< float > > {};

}  // namespace argot

namespace {

using argot::And;
using argot::Not;

// Sanity checks for initial concept maps
ARGOT_CONCEPT_ENSURE( Int< int > );
ARGOT_CONCEPT_ENSURE( Not< Int< void > > );
ARGOT_CONCEPT_ENSURE( Char< char > );
ARGOT_CONCEPT_ENSURE( Not< Char< void > > );
ARGOT_CONCEPT_ENSURE( Float< float > );
ARGOT_CONCEPT_ENSURE( Not< Float< void > > );

// Nullary
ARGOT_CONCEPT_ENSURE( And<> );

// Unary
ARGOT_CONCEPT_ENSURE( And< Int< int > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< char > > > );

// Binary
ARGOT_CONCEPT_ENSURE( And< Int< int >, Char< char > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< int >, Char< void > > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< void >, Char< char > > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< void >, Char< void > > > );

// Ternary
ARGOT_CONCEPT_ENSURE( And< Int< int >, Char< char >, Float< float > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< int >, Char< char >, Float< void > > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< int >, Char< void >, Float< float > > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< int >, Char< void >, Float< void > > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< void >, Char< char >, Float< float > > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< void >, Char< char >, Float< void > > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< void >, Char< void >, Float< float > > > );
ARGOT_CONCEPT_ENSURE( Not< And< Int< void >, Char< void >, Float< void > > > );

}  // namespace
