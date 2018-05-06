/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/case/detail/cast_value_list_elements.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/value_list.hpp>

namespace {

using argot::SameType;
using argot::case_detail::cast_value_list_elements_t;
using argot::value_list_t;

ARGOT_REGISTER_CONSTEXPR_TEST( test_cast )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < cast_value_list_elements_t< unsigned, value_list_t<> >
    , value_list_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < cast_value_list_elements_t< unsigned, value_list_t< 1, 2l, 5ll > >
    , value_list_t< 1u, 2u, 5u >
    >
  );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
