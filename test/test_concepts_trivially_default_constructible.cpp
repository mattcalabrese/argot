/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/trivially_default_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::TriviallyDefaultConstructible;

struct trivial_default_constructor {};
struct nothrow_default_constructor{ nothrow_default_constructor() noexcept {} };
struct throwing_default_constructor { throwing_default_constructor() {} };
struct no_default_constructor { no_default_constructor() = delete; };

ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< int > );
ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< int const > );
ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( TriviallyDefaultConstructible< int[5] > );

ARGOT_CONCEPT_ENSURE
( TriviallyDefaultConstructible< trivial_default_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyDefaultConstructible< nothrow_default_constructor > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyDefaultConstructible< throwing_default_constructor > > );

ARGOT_CONCEPT_ENSURE
( Not< TriviallyDefaultConstructible< no_default_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< TriviallyDefaultConstructible< int[] > > );

} // namespace
