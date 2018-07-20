/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/less_than_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::LessThanComparable;

ARGOT_CONCEPT_ENSURE( LessThanComparable< int > );
ARGOT_CONCEPT_ENSURE( LessThanComparable< int const > );
ARGOT_CONCEPT_ENSURE( LessThanComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( LessThanComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE( LessThanComparable< argot_test::nothrow_less_than > );
ARGOT_CONCEPT_ENSURE( LessThanComparable< argot_test::exceptional_less_than > );
ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< argot_test::no_less_than > > );

ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< int[] > > );

} // namespace
