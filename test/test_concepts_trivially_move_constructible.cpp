/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_move_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::TriviallyMoveConstructible;

struct trivial_move_constructor {};

struct nothrow_move_constructor
{
  nothrow_move_constructor( nothrow_move_constructor&& ) noexcept {}
};

struct throwing_move_constructor
{
  throwing_move_constructor( throwing_move_constructor&& ) {}
};

struct no_move_constructor
{
  no_move_constructor( no_move_constructor&& ) = delete;
};

ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< int > );
ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< int const > );
ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE( TriviallyMoveConstructible< trivial_move_constructor > );
ARGOT_CONCEPT_ENSURE
( Not< TriviallyMoveConstructible< nothrow_move_constructor > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyMoveConstructible< throwing_move_constructor > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyMoveConstructible< no_move_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyMoveConstructible< int[] > > );

} // namespace
