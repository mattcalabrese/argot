/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_destructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowDestructible;

ARGOT_CONCEPT_ENSURE( NothrowDestructible< int > );
ARGOT_CONCEPT_ENSURE( NothrowDestructible< int const > );
ARGOT_CONCEPT_ENSURE( NothrowDestructible< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowDestructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( NothrowDestructible< int[5] > );

ARGOT_CONCEPT_ENSURE( NothrowDestructible< argot_test::trivial_destructor > );
ARGOT_CONCEPT_ENSURE( NothrowDestructible< argot_test::nothrow_destructor > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowDestructible< argot_test::exceptional_destructor > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDestructible< argot_test::no_destructor > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDestructible< int& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDestructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDestructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDestructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDestructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDestructible< int[] > > );

} // namespace
