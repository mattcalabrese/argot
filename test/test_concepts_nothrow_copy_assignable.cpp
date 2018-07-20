/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_copy_assignable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include "regularity_archetypes.hpp"

namespace {

using argot::Not;
using argot::NothrowCopyAssignable;

ARGOT_CONCEPT_ENSURE( NothrowCopyAssignable< int > );
ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int const > > );
ARGOT_CONCEPT_ENSURE( NothrowCopyAssignable< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int[5] > > );

ARGOT_CONCEPT_ENSURE
( NothrowCopyAssignable< argot_test::trivial_copy_assign > );

ARGOT_CONCEPT_ENSURE
( NothrowCopyAssignable< argot_test::nothrow_copy_assign > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowCopyAssignable< argot_test::exceptional_copy_assign > > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowCopyAssignable< argot_test::no_copy_assign > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int[] > > );

} // namespace
