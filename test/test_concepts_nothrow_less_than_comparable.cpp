/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_less_than_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowLessThanComparable;

ARGOT_CONCEPT_ENSURE( NothrowLessThanComparable< int > );
ARGOT_CONCEPT_ENSURE( NothrowLessThanComparable< int const > );
ARGOT_CONCEPT_ENSURE( NothrowLessThanComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowLessThanComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessThanComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( NothrowLessThanComparable< argot_test::nothrow_less_than > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowLessThanComparable< argot_test::exceptional_less_than > > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowLessThanComparable< argot_test::no_less_than > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessThanComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowLessThanComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessThanComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessThanComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessThanComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessThanComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowLessThanComparable< int[] > > );

} // namespace
