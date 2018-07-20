/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/swappable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::Swappable;

ARGOT_CONCEPT_ENSURE( Swappable< int > );
ARGOT_CONCEPT_ENSURE( Not< Swappable< int const > > );
ARGOT_CONCEPT_ENSURE( Swappable< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< Swappable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Swappable< int[5] > );
ARGOT_CONCEPT_ENSURE( Not< Swappable< int const[5] > > );

ARGOT_CONCEPT_ENSURE( Swappable< argot_test::nothrow_swap > );
ARGOT_CONCEPT_ENSURE( Swappable< argot_test::exceptional_swap > );
ARGOT_CONCEPT_ENSURE( Not< Swappable< argot_test::no_swap > > );

ARGOT_CONCEPT_ENSURE( Not< Swappable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< Swappable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< Swappable< void > > );

ARGOT_CONCEPT_ENSURE( Not< Swappable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< Swappable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< Swappable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< Swappable< int[] > > );

} // namespace
