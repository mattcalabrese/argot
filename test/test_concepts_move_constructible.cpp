/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/move_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::MoveConstructible;

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

ARGOT_CONCEPT_ENSURE( MoveConstructible< int > );
ARGOT_CONCEPT_ENSURE( MoveConstructible< int const > );
ARGOT_CONCEPT_ENSURE( MoveConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( MoveConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int[5] > > );

ARGOT_CONCEPT_ENSURE( MoveConstructible< trivial_move_constructor > );
ARGOT_CONCEPT_ENSURE( MoveConstructible< nothrow_move_constructor > );
ARGOT_CONCEPT_ENSURE( MoveConstructible< throwing_move_constructor > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< no_move_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int& > > );
ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int&& > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< MoveConstructible< int[] > > );

} // namespace
