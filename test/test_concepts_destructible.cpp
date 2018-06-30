/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/destructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::Destructible;

struct trivial_destructor {};
struct nothrow_destructor{ ~nothrow_destructor() noexcept; };
struct throwing_destructor { ~throwing_destructor() noexcept( false ); };
struct no_destructor { ~no_destructor() = delete; };

ARGOT_CONCEPT_ENSURE( Destructible< int > );
ARGOT_CONCEPT_ENSURE( Destructible< int const > );
ARGOT_CONCEPT_ENSURE( Destructible< int volatile > );
ARGOT_CONCEPT_ENSURE( Destructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( Destructible< int[5] > );

ARGOT_CONCEPT_ENSURE( Destructible< trivial_destructor > );
ARGOT_CONCEPT_ENSURE( Destructible< nothrow_destructor > );
ARGOT_CONCEPT_ENSURE( Destructible< throwing_destructor > );

ARGOT_CONCEPT_ENSURE( Not< Destructible< no_destructor > > );

ARGOT_CONCEPT_ENSURE( Not< Destructible< int& > > );

ARGOT_CONCEPT_ENSURE( Not< Destructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< Destructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< Destructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< Destructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< Destructible< int[] > > );

} // namespace
