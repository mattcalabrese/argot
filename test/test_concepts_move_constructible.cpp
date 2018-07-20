/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/move_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::MoveConstructible;

ARGOT_CONCEPT_ENSURE( MoveConstructible< int > );
ARGOT_CONCEPT_ENSURE( MoveConstructible< int const > );
ARGOT_CONCEPT_ENSURE( MoveConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( MoveConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE
( MoveConstructible< argot_test::trivial_move_constructor > );

ARGOT_CONCEPT_ENSURE
( MoveConstructible< argot_test::nothrow_move_constructor > );

ARGOT_CONCEPT_ENSURE
( MoveConstructible< argot_test::exceptional_move_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< MoveConstructible< argot_test::no_move_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int[] > > );

} // namespace
