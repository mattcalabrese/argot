/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_move_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowMoveConstructible;

ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< int > );
ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< int const > );
ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE
( NothrowMoveConstructible< argot_test::trivial_move_constructor > );

ARGOT_CONCEPT_ENSURE
( NothrowMoveConstructible< argot_test::nothrow_move_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowMoveConstructible< argot_test::exceptional_move_constructor > > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowMoveConstructible< argot_test::no_move_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int[] > > );

} // namespace
