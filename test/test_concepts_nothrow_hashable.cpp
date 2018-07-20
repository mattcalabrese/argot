/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_hashable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowHashable;

ARGOT_CONCEPT_ENSURE( NothrowHashable< int > );
ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int const > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int volatile > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int[5] > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int const[5] > > );

ARGOT_CONCEPT_ENSURE( NothrowHashable< argot_test::nothrow_hash > );
ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< argot_test::exceptional_hash > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< argot_test::no_hash > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowHashable< int[] > > );

} // namespace
