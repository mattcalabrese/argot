/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_copy_assignable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::NothrowCopyAssignable;

struct trivial_copy_assign {
  trivial_copy_assign( trivial_copy_assign const& ) = delete;
  trivial_copy_assign& operator=( trivial_copy_assign&& ) = delete;
  trivial_copy_assign& operator=( trivial_copy_assign const& )
    = default;
};

struct nothrow_copy_assign
{
  nothrow_copy_assign( nothrow_copy_assign const& ) = delete;
  nothrow_copy_assign& operator=( nothrow_copy_assign&& ) = delete;
  nothrow_copy_assign& operator=( nothrow_copy_assign const& ) noexcept;
};

struct throwing_copy_assign
{
  throwing_copy_assign( throwing_copy_assign const& ) = delete;
  throwing_copy_assign& operator=( throwing_copy_assign&& ) = delete;
  throwing_copy_assign& operator=( throwing_copy_assign const& );
};

struct no_copy_assign
{
  no_copy_assign( no_copy_assign const& ) = delete;
  no_copy_assign& operator=( no_copy_assign&& ) = default;
  no_copy_assign& operator=( no_copy_assign const& ) = delete;
};

ARGOT_CONCEPT_ENSURE( NothrowCopyAssignable< int > );
ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int const > > );
ARGOT_CONCEPT_ENSURE( NothrowCopyAssignable< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int[5] > > );

ARGOT_CONCEPT_ENSURE( NothrowCopyAssignable< trivial_copy_assign > );
ARGOT_CONCEPT_ENSURE( NothrowCopyAssignable< nothrow_copy_assign > );
ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< throwing_copy_assign > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< no_copy_assign > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyAssignable< int[] > > );

} // namespace
