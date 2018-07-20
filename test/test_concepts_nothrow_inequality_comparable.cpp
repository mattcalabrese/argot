/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_inequality_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowInequalityComparable;

ARGOT_CONCEPT_ENSURE( NothrowInequalityComparable< int > );
ARGOT_CONCEPT_ENSURE( NothrowInequalityComparable< int const > );
ARGOT_CONCEPT_ENSURE( NothrowInequalityComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowInequalityComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowInequalityComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( NothrowInequalityComparable< argot_test::nothrow_inequality > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowInequalityComparable< argot_test::exceptional_inequality > > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowInequalityComparable< argot_test::no_inequality > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowInequalityComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowInequalityComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowInequalityComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowInequalityComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowInequalityComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowInequalityComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowInequalityComparable< int[] > > );

} // namespace
