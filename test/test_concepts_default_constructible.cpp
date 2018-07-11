/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/default_constructible.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::DefaultConstructible;

struct trivial_default_constructor {};
struct nothrow_default_constructor{ nothrow_default_constructor() noexcept {} };
struct throwing_default_constructor { throwing_default_constructor() {} };
struct no_default_constructor { no_default_constructor() = delete; };
struct int_member { int member; };
struct default_initializer { int member = 5; };

ARGOT_CONCEPT_ENSURE( DefaultConstructible< int > );
ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int const > > );
ARGOT_CONCEPT_ENSURE( DefaultConstructible< int volatile > );
ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int volatile const > > );

ARGOT_CONCEPT_ENSURE( DefaultConstructible< int_member > );
ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int_member const > > );

ARGOT_CONCEPT_ENSURE( DefaultConstructible< default_initializer > );
ARGOT_CONCEPT_ENSURE( DefaultConstructible< default_initializer const > );

ARGOT_CONCEPT_ENSURE( DefaultConstructible< int[5] > );

ARGOT_CONCEPT_ENSURE( DefaultConstructible< trivial_default_constructor > );
ARGOT_CONCEPT_ENSURE( DefaultConstructible< nothrow_default_constructor > );
ARGOT_CONCEPT_ENSURE( DefaultConstructible< throwing_default_constructor > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< no_default_constructor > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int& > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< void > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int() > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int()& > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int()& noexcept > > );

ARGOT_CONCEPT_ENSURE( Not< DefaultConstructible< int[] > > );

} // namespace
