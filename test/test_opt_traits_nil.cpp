/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/opt_traits/nil.hpp>

#include <argot/detail/constexpr_test.hpp>

#include "regularity_facilities.hpp"
#include "regularity_testing.hpp"

namespace {

ARGOT_REGISTER_CONSTEXPR_TEST( test_nil )
{
  using nil = argot::opt_traits::nil< struct type_for_nil_test >;

  ARGOT_TEST_SUCCESS
  ( argot_test::test_regularity< nil, ::argot_test::trivially_complete_profile >
    ( []{ return nil(); } )
  );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
