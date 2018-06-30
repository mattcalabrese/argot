/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or move at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_move_assignable.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::TriviallyMoveAssignable;

struct trivial_move_assign {
  trivial_move_assign( trivial_move_assign const& ) = delete;
  trivial_move_assign& operator=( trivial_move_assign&& ) = default;
  trivial_move_assign& operator=( trivial_move_assign const& )
    = delete;
};

struct nothrow_move_assign
{
  nothrow_move_assign( nothrow_move_assign const& ) = delete;
  nothrow_move_assign& operator=( nothrow_move_assign&& ) noexcept;
  nothrow_move_assign& operator=( nothrow_move_assign const& ) = delete;
};

struct throwing_move_assign
{
  throwing_move_assign( throwing_move_assign const& ) = delete;
  throwing_move_assign& operator=( throwing_move_assign&& );
  throwing_move_assign& operator=( throwing_move_assign const& ) = delete;
};

struct no_move_assign
{
  no_move_assign( no_move_assign const& ) = delete;
  no_move_assign& operator=( no_move_assign&& ) = delete;
  no_move_assign& operator=( no_move_assign const& ) = default;
};

ARGOT_CONCEPT_ENSURE( TriviallyMoveAssignable< int > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int const > > );
ARGOT_CONCEPT_ENSURE( TriviallyMoveAssignable< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int[5] > > );

ARGOT_CONCEPT_ENSURE( TriviallyMoveAssignable< trivial_move_assign > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< nothrow_move_assign > > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< throwing_move_assign > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< no_move_assign > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int& > > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveAssignable< int[] > > );

} // namespace
