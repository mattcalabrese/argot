/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/nothrow_default_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::NothrowDefaultConstructible;

struct trivial_default_constructor {};
struct nothrow_default_constructor{ nothrow_default_constructor() noexcept {} };
struct throwing_default_constructor { throwing_default_constructor() {} };
struct no_default_constructor { no_default_constructor() = delete; };

ARGOT_CONCEPT_ENSURE( NothrowDefaultConstructible< int > );
ARGOT_CONCEPT_ENSURE( NothrowDefaultConstructible< int const > );
ARGOT_CONCEPT_ENSURE( NothrowDefaultConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( NothrowDefaultConstructible< int volatile const > );

ARGOT_CONCEPT_ENSURE( NothrowDefaultConstructible< int[5] > );

ARGOT_CONCEPT_ENSURE
( NothrowDefaultConstructible< trivial_default_constructor > );

ARGOT_CONCEPT_ENSURE
( NothrowDefaultConstructible< nothrow_default_constructor > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowDefaultConstructible< throwing_default_constructor > > );

ARGOT_CONCEPT_ENSURE
( Not< NothrowDefaultConstructible< no_default_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDefaultConstructible< int& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDefaultConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDefaultConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDefaultConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDefaultConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< NothrowDefaultConstructible< int[] > > );

} // namespace
