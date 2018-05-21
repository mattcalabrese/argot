/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_default_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::TriviallyDefaultConstructible;

ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< int > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int const > > );
ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE
( Not< TriviallyDefaultConstructible< int volatile const > > );

ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< argot_test::int_member > );
ARGOT_CONCEPT_ENSURE
( Not< TriviallyDefaultConstructible< argot_test::int_member const > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyDefaultConstructible< argot_test::default_initializer > > );

ARGOT_CONCEPT_ENSURE
( Not
  < TriviallyDefaultConstructible< argot_test::default_initializer const > >
);

ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< int[5] > );

// NOTE: Needs trivial destructor because of std trait defect.
ARGOT_CONCEPT_ENSURE
( TriviallyDefaultConstructible
  < argot_test::combined_regularity_archetype_t
    < argot_test::trivial_default_constructor_profile
    , argot_test::trivial_destructor_profile
    >
  >
);

ARGOT_CONCEPT_ENSURE
( Not
  < TriviallyDefaultConstructible< argot_test::nothrow_default_constructor > >
);

ARGOT_CONCEPT_ENSURE
( Not
  < TriviallyDefaultConstructible
    < argot_test::exceptional_default_constructor >
  >
);

ARGOT_CONCEPT_ENSURE
( Not< TriviallyDefaultConstructible< argot_test::no_default_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int[] > > );

} // namespace
