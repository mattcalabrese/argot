/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/discriminated_union.hpp>

#include <argot/detail/constexpr_test.hpp>

#include <utility>

namespace {

using argot::discriminated_union;

ARGOT_REGISTER_CONSTEXPR_TEST
( test_discriminated_union_nullary_construct_constexpr )
{
  using discriminated_union_t = discriminated_union<>;

  discriminated_union_t nullary_discriminated_union;
  (void)nullary_discriminated_union;

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
