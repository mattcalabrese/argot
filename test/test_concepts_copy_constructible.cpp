/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/copy_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::CopyConstructible;

ARGOT_CONCEPT_ENSURE( CopyConstructible< int > );
ARGOT_CONCEPT_ENSURE( CopyConstructible< int const > );
ARGOT_CONCEPT_ENSURE( CopyConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( CopyConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< CopyConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE
( CopyConstructible< argot_test::trivial_copy_constructor > );

ARGOT_CONCEPT_ENSURE
( CopyConstructible< argot_test::nothrow_copy_constructor > );

ARGOT_CONCEPT_ENSURE
( CopyConstructible< argot_test::exceptional_copy_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< CopyConstructible< argot_test::no_copy_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< CopyConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< CopyConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< CopyConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< CopyConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< CopyConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< CopyConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< CopyConstructible< int[] > > );

} // namespace
