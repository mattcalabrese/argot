/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_copy_assignable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::TriviallyCopyAssignable;

ARGOT_CONCEPT_ENSURE( TriviallyCopyAssignable< int > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int const > > );
ARGOT_CONCEPT_ENSURE( TriviallyCopyAssignable< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( TriviallyCopyAssignable< argot_test::trivial_copy_assign > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyCopyAssignable< argot_test::nothrow_copy_assign > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyCopyAssignable< argot_test::exceptional_copy_assign > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyCopyAssignable< argot_test::no_copy_assign > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyAssignable< int[] > > );

} // namespace
