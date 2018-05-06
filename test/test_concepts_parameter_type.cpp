/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/parameter_type.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/concept_ensure.hpp>

#include <type_traits>

using argot::ParameterType;
using argot::Not;

ARGOT_CONCEPT_ENSURE( ParameterType< int > );
ARGOT_CONCEPT_ENSURE( ParameterType< int* > );
ARGOT_CONCEPT_ENSURE( ParameterType< int&& > );

ARGOT_CONCEPT_ENSURE( Not< ParameterType< void > > );
ARGOT_CONCEPT_ENSURE( Not< ParameterType< void const > > );
ARGOT_CONCEPT_ENSURE( Not< ParameterType< void volatile > > );
ARGOT_CONCEPT_ENSURE( Not< ParameterType< void volatile const > >);

// TODO(mattcalabrese) Possibly don't accept these.
ARGOT_CONCEPT_ENSURE( ParameterType< int[5] > );
ARGOT_CONCEPT_ENSURE( ParameterType< int[] > );
ARGOT_CONCEPT_ENSURE( ParameterType< int() > );
