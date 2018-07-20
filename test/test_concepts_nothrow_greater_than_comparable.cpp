/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_greater_than_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowGreaterThanComparable;

ARGOT_CONCEPT_ENSURE( NothrowGreaterThanComparable< int > );
ARGOT_CONCEPT_ENSURE( NothrowGreaterThanComparable< int const > );
ARGOT_CONCEPT_ENSURE( NothrowGreaterThanComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowGreaterThanComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterThanComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( NothrowGreaterThanComparable< argot_test::nothrow_greater_than > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowGreaterThanComparable< argot_test::exceptional_greater_than > > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowGreaterThanComparable< argot_test::no_greater_than > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterThanComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterThanComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterThanComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterThanComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterThanComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterThanComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterThanComparable< int[] > > );

} // namespace
