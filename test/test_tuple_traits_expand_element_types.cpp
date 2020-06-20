/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/tuple_traits/expand_element_types.hpp>

#include <tuple>

namespace {

namespace tuple_traits = argot::tuple_traits;

template< class... >
struct result;

ARGOT_REGISTER_CONSTEXPR_TEST( test_expand_element_types )
{
  struct a{}; struct b{}; struct c{};

  ARGOT_CONCEPT_ENSURE
  ( argot::SameType
    < tuple_traits::expand_element_types_t
      < std::tuple<>, result >
    , result<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( argot::SameType
    < tuple_traits::expand_element_types_t
      < std::tuple< a >, result >
    , result< a >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( argot::SameType
    < tuple_traits::expand_element_types_t
      < std::tuple< a, b >, result >
    , result< a, b >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( argot::SameType
    < tuple_traits::expand_element_types_t
      < std::tuple< a, b, c >, result >
    , result< a, b, c >
    >
  );

  return 0;
}

ARGOT_EXECUTE_TESTS();

} // namespace
