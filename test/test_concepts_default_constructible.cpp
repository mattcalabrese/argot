/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/default_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::DefaultConstructible;

ARGOT_CONCEPT_ENSURE( DefaultConstructible< int > );
ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int const > > );
ARGOT_CONCEPT_ENSURE( DefaultConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int volatile const > > );

ARGOT_CONCEPT_ENSURE( DefaultConstructible< argot_test::int_member > );

ARGOT_CONCEPT_ENSURE
( Not< DefaultConstructible< argot_test::int_member const > > );

ARGOT_CONCEPT_ENSURE( DefaultConstructible< argot_test::default_initializer > );

ARGOT_CONCEPT_ENSURE
( DefaultConstructible< argot_test::default_initializer const > );

ARGOT_CONCEPT_ENSURE( DefaultConstructible< int[5] > );

ARGOT_CONCEPT_ENSURE
( DefaultConstructible< argot_test::trivial_default_constructor > );

ARGOT_CONCEPT_ENSURE
( DefaultConstructible< argot_test::nothrow_default_constructor > );

ARGOT_CONCEPT_ENSURE
( DefaultConstructible< argot_test::exceptional_default_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< DefaultConstructible< argot_test::no_default_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int& > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int[] > > );

} // namespace
