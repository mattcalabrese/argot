/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/less_equal_comparable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::LessEqualComparable;

ARGOT_CONCEPT_ENSURE( LessEqualComparable< int > );
ARGOT_CONCEPT_ENSURE( LessEqualComparable< int const > );
ARGOT_CONCEPT_ENSURE( LessEqualComparable< int volatile > );
ARGOT_CONCEPT_ENSURE( LessEqualComparable< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< int[5] > > );

ARGOT_CONCEPT_ENSURE( LessEqualComparable< argot_test::nothrow_less_equal > );

ARGOT_CONCEPT_ENSURE
( LessEqualComparable< argot_test::exceptional_less_equal > );

ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< argot_test::no_less_equal > > );

ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< void > > );

ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< int[] > > );

} // namespace
