/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include "regularity_testing.hpp"

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>

#include <limits>
#include <tuple>

// TODO(mattcalabrese) Test that everything fails when expected

namespace {

ARGOT_CONCEPT_ENSURE
( argot::SameType
  < argot_test::syntactic_regularity_profile_of_t< int >
  , argot_test::trivially_complete_profile
  >
);

using argot_test::trivially_complete_profile;

// TODO(mattcalabrese) constexpr (can't because of hash and default construct)
ARGOT_REGISTER_TEST( int_regularity )
{
  return argot_test::test_regularity< int, trivially_complete_profile >
  ( []{ return -5; }
  , []{ return -3; }
  , []{ return -2; }
  , []{ return -1; }
  , []{ return 0; }
  , []{ return 1; }
  , []{ return 2; }
  , []{ return 3; }
  , []{ return 5; }
  );
}

// TODO(mattcalabrese) constexpr (can't because of hash and default construct)
ARGOT_REGISTER_TEST( int_regularity_with_equivalences )
{
  return argot_test::test_regularity< int, trivially_complete_profile >
  ( []{ return -5; }
  , []{ return -3; }
  , []{ return -2; }
  , std::make_tuple( []{ return -1; }, []{ return -1; } )
  , []{ return 0; }
  , std::make_tuple( []{ return 1; }, []{ return 1; } )
  , []{ return 2; }
  , []{ return 3; }
  , []{ return 5; }
  );
}

// TODO(mattcalabrese) constexpr (can't because of hash and default construct)
ARGOT_REGISTER_TEST( double_regularity )
{
  using lim = std::numeric_limits< double >;

  // NOTE: Assumes various floating point properties (has_infinity, etc.)
  return argot_test::test_regularity< double, trivially_complete_profile >
  ( []{ return -lim::infinity(); }
  , []{ return -5.; }
  , []{ return -3.; }
  , []{ return -2.; }
  , []{ return -1.; }
  , std::make_tuple( []{ return -0.; }, []{ return 0.; } )
  , []{ return 1.; }
  , []{ return 2.; }
  , []{ return 3.; }
  , []{ return 5.; }
  , []{ return lim::infinity(); }
  );
}

ARGOT_EXECUTE_TESTS();

} // namespace
