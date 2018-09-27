/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_swappable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowSwappable;

ARGOT_CONCEPT_ENSURE( NothrowSwappable< int > );
ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< int const > > );

ARGOT_CONCEPT_ENSURE( NothrowSwappable< int[5] > );
ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< int const[5] > > );

ARGOT_CONCEPT_ENSURE( NothrowSwappable< argot_test::nothrow_swap > );
ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< argot_test::exceptional_swap > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< argot_test::no_swap > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowSwappable< int[] > > );

} // namespace
