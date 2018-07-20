/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/hashable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::Hashable;

ARGOT_CONCEPT_ENSURE( Hashable< int > );
ARGOT_CONCEPT_ENSURE( Not< Hashable< int const > > );
ARGOT_CONCEPT_ENSURE( Not< Hashable< int volatile > > );
ARGOT_CONCEPT_ENSURE( Not< Hashable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< Hashable< int[5] > > );
ARGOT_CONCEPT_ENSURE( Not< Hashable< int const[5] > > );

ARGOT_CONCEPT_ENSURE( Hashable< argot_test::nothrow_hash > );
ARGOT_CONCEPT_ENSURE( Hashable< argot_test::exceptional_hash > );
ARGOT_CONCEPT_ENSURE( Not< Hashable< argot_test::no_hash > > );

ARGOT_CONCEPT_ENSURE( Not< Hashable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< Hashable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< Hashable< void > > );

ARGOT_CONCEPT_ENSURE( Not< Hashable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< Hashable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< Hashable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< Hashable< int[] > > );

} // namespace
