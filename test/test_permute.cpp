/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/permute.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>

namespace {

using argot::SameType;
using argot::call_detail::permute_t;
using argot::receiver_traits::argument_list_kinds_t;
using argot::receiver_traits::argument_types_t;

using int_float = argument_types_t< int&, float& >;
using char_double = argument_types_t< char&, double& >;
using short_long = argument_types_t< short&, long& >;
using bool_void = argument_types_t< bool&, void*& >;
using wchar_t_unsigned = argument_types_t< wchar_t&, unsigned& >;
using array_fun = argument_types_t< int (&)[1], int (&)() >;

using int_float_char_double = argument_types_t< int&, float&, char&, double& >;
using int_float_short_long = argument_types_t< int&, float&, short&, long& >;

using char_double_short_long
  = argument_types_t< char&, double&, short&, long& >;

using char_double_char_double
  = argument_types_t< char&, double&, char&, double& >;

using int_float_bool_void = argument_types_t< int&, float&, bool&, void*& >;
using char_double_bool_void = argument_types_t< char&, double&, bool&, void*& >;

using int_float_short_long_wchar_t_unsigned
  = argument_types_t< int&, float&, short&, long&, wchar_t&, unsigned& >;

using int_float_short_long_array_fun
  = argument_types_t< int&, float&, short&, long&, int (&)[1], int (&)() >;

using int_float_bool_void_wchar_t_unsigned
  = argument_types_t< int&, float&, bool&, void*&, wchar_t&, unsigned& >;

using int_float_bool_void_array_fun
  = argument_types_t< int&, float&, bool&, void*&, int (&)[1], int (&)() >;

using char_double_short_long_wchar_t_unsigned
  = argument_types_t< char&, double&, short&, long&, wchar_t&, unsigned& >;

using char_double_short_long_array_fun
  = argument_types_t< char&, double&, short&, long&, int (&)[1], int (&)() >;

using char_double_bool_void_wchar_t_unsigned
  = argument_types_t< char&, double&, bool&, void*&, wchar_t&, unsigned& >;

using char_double_bool_void_array_fun
  = argument_types_t< char&, double&, bool&, void*&, int (&)[1], int (&)() >;

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t<>
  , argument_list_kinds_t< argument_types_t<> >
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t< argument_list_kinds_t<> >
  , argument_list_kinds_t<>
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t
    < argument_list_kinds_t<>
    , argument_list_kinds_t< int_float >
    >
  , argument_list_kinds_t<>
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t
    < argument_list_kinds_t< int_float >
    , argument_list_kinds_t<>
    >
  , argument_list_kinds_t<>
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t< argument_list_kinds_t<>
           , argument_list_kinds_t< int_float >
           , argument_list_kinds_t< char_double >
           >
  , argument_list_kinds_t<>
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t< argument_list_kinds_t< int_float >
           , argument_list_kinds_t<>
           , argument_list_kinds_t< char_double >
           >
  , argument_list_kinds_t<>
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t< argument_list_kinds_t< int_float >
           , argument_list_kinds_t< char_double >
           , argument_list_kinds_t<>
           >
  , argument_list_kinds_t<>
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t< argument_list_kinds_t<>, int_float >
  , argument_list_kinds_t<>
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t< argument_list_kinds_t< int_float > >
  , argument_list_kinds_t< int_float >
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t< argument_list_kinds_t< int_float, char_double > >
  , argument_list_kinds_t< int_float, char_double >
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t
    < argument_list_kinds_t< int_float >
    , argument_list_kinds_t< char_double >
    >
  , argument_list_kinds_t< int_float_char_double >
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t
    < argument_list_kinds_t< int_float, char_double >
    , argument_list_kinds_t< short_long >
    >
  , argument_list_kinds_t
    < int_float_short_long, char_double_short_long >
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t
    < argument_list_kinds_t< int_float >
    , argument_list_kinds_t< char_double, short_long >
    >
  , argument_list_kinds_t
    < int_float_char_double, int_float_short_long >
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t
    < argument_list_kinds_t< int_float, char_double >
    , argument_list_kinds_t< short_long, bool_void >
    >
  , argument_list_kinds_t
    < int_float_short_long, int_float_bool_void
    , char_double_short_long, char_double_bool_void
    >
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < permute_t< argument_list_kinds_t< int_float, char_double >
             , argument_list_kinds_t< short_long, bool_void >
             , argument_list_kinds_t< wchar_t_unsigned, array_fun >
             >
  , argument_list_kinds_t
    < int_float_short_long_wchar_t_unsigned
    , int_float_short_long_array_fun
    , int_float_bool_void_wchar_t_unsigned
    , int_float_bool_void_array_fun
    , char_double_short_long_wchar_t_unsigned
    , char_double_short_long_array_fun
    , char_double_bool_void_wchar_t_unsigned
    , char_double_bool_void_array_fun
    >
  >
);

}  // namespace
