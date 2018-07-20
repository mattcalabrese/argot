/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or move at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/move_assignable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::MoveAssignable;

ARGOT_CONCEPT_ENSURE( MoveAssignable< int > );
ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int const > > );
ARGOT_CONCEPT_ENSURE( MoveAssignable< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int[5] > > );

ARGOT_CONCEPT_ENSURE( MoveAssignable< argot_test::trivial_move_assign > );
ARGOT_CONCEPT_ENSURE( MoveAssignable< argot_test::nothrow_move_assign > );
ARGOT_CONCEPT_ENSURE( MoveAssignable< argot_test::exceptional_move_assign > );
ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< argot_test::no_move_assign > > );

ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< void > > );

ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< MoveAssignable< int[] > > );

} // namespace
