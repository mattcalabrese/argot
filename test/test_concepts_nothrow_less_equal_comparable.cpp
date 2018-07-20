/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_less_equal_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowLessEqualComparable;

ARGOT_CONCEPT_ENSURE( NothrowLessEqualComparable< int > );
ARGOT_CONCEPT_ENSURE( NothrowLessEqualComparable< int const > );
ARGOT_CONCEPT_ENSURE( NothrowLessEqualComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowLessEqualComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessEqualComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( NothrowLessEqualComparable< argot_test::nothrow_less_equal > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowLessEqualComparable< argot_test::exceptional_less_equal > > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowLessEqualComparable< argot_test::no_less_equal > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessEqualComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowLessEqualComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessEqualComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessEqualComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessEqualComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessEqualComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessEqualComparable< int[] > > );

} // namespace
