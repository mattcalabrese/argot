/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_copy_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::TriviallyCopyConstructible;

ARGOT_CONCEPT_ENSURE( TriviallyCopyConstructible< int > );
ARGOT_CONCEPT_ENSURE( TriviallyCopyConstructible< int const > );
ARGOT_CONCEPT_ENSURE( TriviallyCopyConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( TriviallyCopyConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE
( TriviallyCopyConstructible< argot_test::trivial_copy_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyCopyConstructible< argot_test::nothrow_copy_constructor > > );

ARGOT_CONCEPT_ENSURE
( Not
  < TriviallyCopyConstructible< argot_test::exceptional_copy_constructor > >
);

ARGOT_CONCEPT_ENSURE
( Not< TriviallyCopyConstructible< argot_test::no_copy_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyCopyConstructible< int[] > > );

} // namespace
