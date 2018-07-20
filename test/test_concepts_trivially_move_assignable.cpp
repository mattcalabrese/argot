/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or move at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_move_assignable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::TriviallyMoveAssignable;

ARGOT_CONCEPT_ENSURE( TriviallyMoveAssignable< int > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int const > > );
ARGOT_CONCEPT_ENSURE( TriviallyMoveAssignable< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( TriviallyMoveAssignable< argot_test::trivial_move_assign > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyMoveAssignable< argot_test::nothrow_move_assign > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyMoveAssignable< argot_test::exceptional_move_assign > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyMoveAssignable< argot_test::no_move_assign > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int[] > > );

} // namespace
