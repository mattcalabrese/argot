/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/equality_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::EqualityComparable;

ARGOT_CONCEPT_ENSURE( EqualityComparable< int > );
ARGOT_CONCEPT_ENSURE( EqualityComparable< int const > );
ARGOT_CONCEPT_ENSURE( EqualityComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( EqualityComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE( EqualityComparable< argot_test::nothrow_equality > );
ARGOT_CONCEPT_ENSURE( EqualityComparable< argot_test::exceptional_equality > );
ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< argot_test::no_equality > > );

ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< int[] > > );

} // namespace
