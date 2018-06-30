/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_move_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::NothrowMoveConstructible;

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

ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< int > );
ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< int const > );
ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< trivial_move_constructor > );
ARGOT_CONCEPT_ENSURE( NothrowMoveConstructible< nothrow_move_constructor > );
ARGOT_CONCEPT_ENSURE
( Not< NothrowMoveConstructible< throwing_move_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< no_move_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowMoveConstructible< int[] > > );

} // namespace
