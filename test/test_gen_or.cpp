/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>

namespace {

template< class >
ARGOT_EXPLICIT_CONCEPT( Int )
(
);

}  // namespace

namespace argot {

template<>
struct make_concept_map< Int< int > > {};

}  // namespace argot

namespace {

using argot::Or;
using argot::Not;

// Sanity checks for initial concept maps
ARGOT_CONCEPT_ENSURE( Int< int > );
ARGOT_CONCEPT_ENSURE( Not< Int< char > > );

// Nullary
ARGOT_CONCEPT_ENSURE( Not< Or<> > );

// Unary
ARGOT_CONCEPT_ENSURE( Or< Int< int > > );
ARGOT_CONCEPT_ENSURE( Not< Or< Int< char > > > );

// Binary
ARGOT_CONCEPT_ENSURE( Or< Int< int >, Int< int > > );
ARGOT_CONCEPT_ENSURE( Or< Int< int >, Int< char > > );
ARGOT_CONCEPT_ENSURE( Or< Int< char >, Int< int > > );
ARGOT_CONCEPT_ENSURE( Not< Or< Int< char >, Int< char > > > );

// Ternary
ARGOT_CONCEPT_ENSURE( Or< Int< int >, Int< int >, Int< int > > );
ARGOT_CONCEPT_ENSURE( Or< Int< int >, Int< int >, Int< char > > );
ARGOT_CONCEPT_ENSURE( Or< Int< int >, Int< char >, Int< int > > );
ARGOT_CONCEPT_ENSURE( Or< Int< int >, Int< char >, Int< char > > );
ARGOT_CONCEPT_ENSURE( Or< Int< char >, Int< int >, Int< int > > );
ARGOT_CONCEPT_ENSURE( Or< Int< char >, Int< int >, Int< char > > );
ARGOT_CONCEPT_ENSURE( Or< Int< char >, Int< char >, Int< int > > );
ARGOT_CONCEPT_ENSURE( Not< Or< Int< char >, Int< char >, Int< char > > > );

}  // namespace
