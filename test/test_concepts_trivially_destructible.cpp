/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_destructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::TriviallyDestructible;

ARGOT_CONCEPT_ENSURE( TriviallyDestructible< int > );
ARGOT_CONCEPT_ENSURE( TriviallyDestructible< int const > );
ARGOT_CONCEPT_ENSURE( TriviallyDestructible< int volatile > );
ARGOT_CONCEPT_ENSURE( TriviallyDestructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( TriviallyDestructible< int[5] > );

ARGOT_CONCEPT_ENSURE( TriviallyDestructible< argot_test::trivial_destructor > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyDestructible< argot_test::nothrow_destructor > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyDestructible< argot_test::exceptional_destructor > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyDestructible< argot_test::no_destructor > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDestructible< int& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDestructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDestructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDestructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDestructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDestructible< int[] > > );

} // namespace
