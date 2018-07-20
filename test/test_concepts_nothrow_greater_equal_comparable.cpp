/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_greater_equal_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowGreaterEqualComparable;

ARGOT_CONCEPT_ENSURE( NothrowGreaterEqualComparable< int > );
ARGOT_CONCEPT_ENSURE( NothrowGreaterEqualComparable< int const > );
ARGOT_CONCEPT_ENSURE( NothrowGreaterEqualComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowGreaterEqualComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterEqualComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( NothrowGreaterEqualComparable< argot_test::nothrow_greater_equal > );

ARGOT_CONCEPT_ENSURE
( Not
  < NothrowGreaterEqualComparable< argot_test::exceptional_greater_equal > >
);

ARGOT_CONCEPT_ENSURE
( Not< NothrowGreaterEqualComparable< argot_test::no_greater_equal > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterEqualComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterEqualComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterEqualComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterEqualComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterEqualComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterEqualComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowGreaterEqualComparable< int[] > > );

} // namespace
