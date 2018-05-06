/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

using argot::SameType;

using argot::call_detail::concatenate;
using argot::receiver_traits::argument_list_kinds_t;

using int_float_char_double_short_long
  = argument_list_kinds_t< int, float, char, double, short, long >;

using int_float_char_double
  = argument_list_kinds_t< int, float, char, double >;

using int_float = argument_list_kinds_t< int, float >;
using char_double = argument_list_kinds_t< char, double >;
using short_long = argument_list_kinds_t< short, long >;

ARGOT_CONCEPT_ENSURE
( SameType< argument_list_kinds_t<>, concatenate<>::type > );

ARGOT_CONCEPT_ENSURE
( SameType
  < int_float
  , concatenate< int_float >::type
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < int_float_char_double
  , concatenate< int_float, char_double >::type
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < int_float_char_double_short_long
  , concatenate< int_float, char_double, short_long >::type
  >
);
