/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/inequality_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::InequalityComparable;

ARGOT_CONCEPT_ENSURE( InequalityComparable< int > );
ARGOT_CONCEPT_ENSURE( InequalityComparable< int const > );
ARGOT_CONCEPT_ENSURE( InequalityComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( InequalityComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< InequalityComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE( InequalityComparable< argot_test::nothrow_inequality > );

ARGOT_CONCEPT_ENSURE
( InequalityComparable< argot_test::exceptional_inequality > );

ARGOT_CONCEPT_ENSURE
( Not< InequalityComparable< argot_test::no_inequality > > );

ARGOT_CONCEPT_ENSURE( Not< InequalityComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< InequalityComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< InequalityComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< InequalityComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< InequalityComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< InequalityComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< InequalityComparable< int[] > > );

} // namespace
