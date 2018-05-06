/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/concept_ensure.hpp>

using argot::SameType;
using argot::Not;

struct a {};
struct b {};

// 1-arg
ARGOT_CONCEPT_ENSURE( SameType< int > );
ARGOT_CONCEPT_ENSURE( SameType< int volatile > );
ARGOT_CONCEPT_ENSURE( SameType< char > );
ARGOT_CONCEPT_ENSURE( SameType< void > );
ARGOT_CONCEPT_ENSURE( SameType< int& > );

// 2-arg
ARGOT_CONCEPT_ENSURE( SameType< int, int > );
ARGOT_CONCEPT_ENSURE( SameType< int volatile, int volatile > );
ARGOT_CONCEPT_ENSURE( SameType< char, char > );
ARGOT_CONCEPT_ENSURE( SameType< void*, void* > );
ARGOT_CONCEPT_ENSURE( SameType< int&, int& > );
ARGOT_CONCEPT_ENSURE( SameType< void, void > );

ARGOT_CONCEPT_ENSURE( Not< SameType< int, char > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< int, int const > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< int const, int > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< int volatile, int > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< void volatile, void > > );

// 3-arg
ARGOT_CONCEPT_ENSURE( SameType< a, a, a > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, a > > );
ARGOT_CONCEPT_ENSURE( SameType< b, b, b > );

// 4-arg
ARGOT_CONCEPT_ENSURE( SameType< a, a, a, a > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, b, a > > );
ARGOT_CONCEPT_ENSURE( SameType< b, b, b, b > );

// 5-arg
ARGOT_CONCEPT_ENSURE( SameType< a, a, a, a, a > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, a, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, a, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, a, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, b, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, b, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, b, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, a, b, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, a, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, a, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, a, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, a, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, b, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, b, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, b, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< a, b, b, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, a, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, a, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, a, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, a, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, b, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, b, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, b, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, a, b, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, a, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, a, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, a, b, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, a, b, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, b, a, a > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, b, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< SameType< b, b, b, b, a > > );
ARGOT_CONCEPT_ENSURE( SameType< b, b, b, b, b > );

// TODO(mattcalabrese)
//   Test one and two beyone the arity of the pre-processed specializations.
