/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/copy_assignable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::CopyAssignable;

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

ARGOT_CONCEPT_ENSURE( CopyAssignable< int > );
ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int const > > );
ARGOT_CONCEPT_ENSURE( CopyAssignable< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int[5] > > );

ARGOT_CONCEPT_ENSURE( CopyAssignable< trivial_copy_assign > );
ARGOT_CONCEPT_ENSURE( CopyAssignable< nothrow_copy_assign > );
ARGOT_CONCEPT_ENSURE( CopyAssignable< throwing_copy_assign > );

ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< no_copy_assign > > );

ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< void > > );

ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< CopyAssignable< int[] > > );

} // namespace
