/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/greater_equal_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::GreaterEqualComparable;

ARGOT_CONCEPT_ENSURE( GreaterEqualComparable< int > );
ARGOT_CONCEPT_ENSURE( GreaterEqualComparable< int const > );
ARGOT_CONCEPT_ENSURE( GreaterEqualComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( GreaterEqualComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< GreaterEqualComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( GreaterEqualComparable< argot_test::nothrow_greater_equal > );

ARGOT_CONCEPT_ENSURE
( GreaterEqualComparable< argot_test::exceptional_greater_equal > );

ARGOT_CONCEPT_ENSURE
( Not< GreaterEqualComparable< argot_test::no_greater_equal > > );

ARGOT_CONCEPT_ENSURE( Not< GreaterEqualComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< GreaterEqualComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< GreaterEqualComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< GreaterEqualComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< GreaterEqualComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< GreaterEqualComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< GreaterEqualComparable< int[] > > );

} // namespace
