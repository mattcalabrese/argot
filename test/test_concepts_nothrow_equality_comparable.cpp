/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_equality_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowEqualityComparable;

ARGOT_CONCEPT_ENSURE( NothrowEqualityComparable< int > );
ARGOT_CONCEPT_ENSURE( NothrowEqualityComparable< int const > );
ARGOT_CONCEPT_ENSURE( NothrowEqualityComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowEqualityComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowEqualityComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( NothrowEqualityComparable< argot_test::nothrow_equality > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowEqualityComparable< argot_test::exceptional_equality > > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowEqualityComparable< argot_test::no_equality > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowEqualityComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowEqualityComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowEqualityComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowEqualityComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowEqualityComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowEqualityComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowEqualityComparable< int[] > > );

} // namespace
