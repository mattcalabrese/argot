/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/volatile_object.hpp>

#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

namespace {

using argot::Not;
using argot::VolatileObject;

struct user_define_object {};

ARGOT_CONCEPT_ENSURE( VolatileObject< int volatile > );
ARGOT_CONCEPT_ENSURE( VolatileObject< int volatile const > );
ARGOT_CONCEPT_ENSURE( VolatileObject< user_define_object volatile > );
ARGOT_CONCEPT_ENSURE( VolatileObject< user_define_object volatile const > );
ARGOT_CONCEPT_ENSURE( VolatileObject< int volatile[5] > );
ARGOT_CONCEPT_ENSURE( VolatileObject< int volatile[] > );

ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int const > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< user_define_object > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< user_define_object const > > );

ARGOT_CONCEPT_ENSURE( Not< VolatileObject< void > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< void const > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< void volatile > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< void volatile const > > );

ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int& > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int const& > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int volatile& > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int volatile const& > > );

ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int&& > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int const&& > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int volatile&& > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int volatile const&& > > );

ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int() > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int() volatile > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int() volatile const > > );
ARGOT_CONCEPT_ENSURE( Not< VolatileObject< int() && > > );

} // namespace
