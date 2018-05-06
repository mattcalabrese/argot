/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/reference.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/concept_ensure.hpp>

using argot::Reference;
using argot::Not;

struct a {};

ARGOT_CONCEPT_ENSURE( Reference< a& > );
ARGOT_CONCEPT_ENSURE( Reference< a const& > );
ARGOT_CONCEPT_ENSURE( Reference< a volatile& > );
ARGOT_CONCEPT_ENSURE( Reference< a volatile const& > );

ARGOT_CONCEPT_ENSURE( Reference< a&& > );
ARGOT_CONCEPT_ENSURE( Reference< a const&& > );
ARGOT_CONCEPT_ENSURE( Reference< a volatile&& > );
ARGOT_CONCEPT_ENSURE( Reference< a volatile const&& > );

ARGOT_CONCEPT_ENSURE( Not< Reference< a > > );
ARGOT_CONCEPT_ENSURE( Not< Reference< a const > > );
ARGOT_CONCEPT_ENSURE( Not< Reference< a volatile > > );
ARGOT_CONCEPT_ENSURE( Not< Reference< a volatile const > > );
