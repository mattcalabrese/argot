/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_copy_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::NothrowCopyConstructible;

struct trivial_copy_constructor {
  trivial_copy_constructor( trivial_copy_constructor&& ) = delete;
  trivial_copy_constructor( trivial_copy_constructor const& ) = default;
  trivial_copy_constructor& operator=( trivial_copy_constructor const& )
    = delete;
};

struct nothrow_copy_constructor
{
  nothrow_copy_constructor( nothrow_copy_constructor&& ) = delete;
  nothrow_copy_constructor( nothrow_copy_constructor const& ) noexcept {}
  nothrow_copy_constructor& operator=( nothrow_copy_constructor const& )
    = delete;
};

struct throwing_copy_constructor
{
  throwing_copy_constructor( throwing_copy_constructor&& ) = delete;
  throwing_copy_constructor( throwing_copy_constructor const& ) {}
  throwing_copy_constructor& operator=( throwing_copy_constructor const& )
    = delete;
};

struct no_copy_constructor
{
  no_copy_constructor( no_copy_constructor&& ) = default;
  no_copy_constructor( no_copy_constructor const& ) = delete;
  no_copy_constructor& operator=( no_copy_constructor const& ) = default;
};

ARGOT_CONCEPT_ENSURE( NothrowCopyConstructible< int > );
ARGOT_CONCEPT_ENSURE( NothrowCopyConstructible< int const > );
ARGOT_CONCEPT_ENSURE( NothrowCopyConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowCopyConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE( NothrowCopyConstructible< trivial_copy_constructor > );
ARGOT_CONCEPT_ENSURE( NothrowCopyConstructible< nothrow_copy_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowCopyConstructible< throwing_copy_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< no_copy_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowCopyConstructible< int[] > > );

} // namespace
