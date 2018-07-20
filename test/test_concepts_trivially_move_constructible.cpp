/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_move_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::TriviallyMoveConstructible;

ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< int > );
ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< int const > );
ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE
( TriviallyMoveConstructible< argot_test::trivial_move_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyMoveConstructible< argot_test::nothrow_move_constructor > > );

ARGOT_CONCEPT_ENSURE
( Not
  < TriviallyMoveConstructible< argot_test::exceptional_move_constructor > >
);

ARGOT_CONCEPT_ENSURE
( Not< TriviallyMoveConstructible< argot_test::no_move_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int[] > > );

} // namespace
