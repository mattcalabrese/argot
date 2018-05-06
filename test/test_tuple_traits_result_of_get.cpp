/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/tuple_traits/result_of_get.hpp>

#include <tuple>
#include <type_traits>

namespace tuple_traits = argot::tuple_traits;

struct a{}; struct b{}; struct c{};

using tuple_type = std::tuple< a, b, c >;

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type&, 0 >
  , a&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type const&, 0 >
  , a const&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type&&, 0 >
  , a&&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type, 0 >
  , a&&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type&, 1 >
  , b&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type const&, 1 >
  , b const&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type&&, 1 >
  , b&&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type, 1 >
  , b&&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type&, 2 >
  , c&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type const&, 2 >
  , c const&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type&&, 2 >
  , c&&
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < tuple_traits::result_of_get_t< tuple_type, 2 >
  , c&&
  >::value

);

// TODO(mattcalabrese) Test SFINAE behavior
