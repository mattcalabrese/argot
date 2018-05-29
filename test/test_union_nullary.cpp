/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/union_.hpp>

#include <argot/detail/constexpr_test.hpp>

#include <utility>

namespace {

namespace union_traits = argot::union_traits;

using argot::union_;

ARGOT_REGISTER_CONSTEXPR_TEST( test_union_nullary_construct_constexpr )
{
  using union_t = union_<>;

  union_t nullary_union;
  union_t const& nullary_union_const = nullary_union;

  // Copy
  {
    union_t other_union = nullary_union_const;
    other_union = nullary_union_const;
    (void)other_union;
  }

  // Move
  {
    union_t other_union = std::move( nullary_union );
    nullary_union = std::move( other_union );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
