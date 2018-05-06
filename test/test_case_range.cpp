/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/case/case_range.hpp>
#include <argot/concepts/case_labels.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/value_list.hpp>

namespace {

using argot::access_raw_concept_map;
using argot::CaseLabels;
using argot::SameType;
using argot::case_range;
using argot::value_list_t;

enum class fake_range { neg1 = -1, zero, one, two, three = 3 };

ARGOT_REGISTER_CONSTEXPR_TEST( test_basic_range )
{
  // TODO(mattcalabrese) Test the result type calculators.

  auto int_range = case_range< -1, 3 >;
  using case_type = decltype( int_range );
  (void)int_range;

  ARGOT_CONCEPT_ENSURE( CaseLabels< case_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_type > >::case_values_t
    , value_list_t< -1, 0, 1, 2 >
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_long_range )
{
  // TODO(mattcalabrese) Test the result type calculators.

  auto long_range
    = case_range< -1l, 3l >;
  using case_type = decltype( long_range );
  (void)long_range;

  ARGOT_CONCEPT_ENSURE( CaseLabels< case_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_type > >::case_values_t
    , value_list_t< -1l, 0l, 1l, 2l >
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_short_range )
{
  // TODO(mattcalabrese) Test the result type calculators.

  auto short_range
    = case_range< static_cast< short >( -1 ), static_cast< short >( 3 ) >;
  using case_type = decltype( short_range );
  (void)short_range;

  ARGOT_CONCEPT_ENSURE( CaseLabels< case_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_type > >::case_values_t
    , value_list_t< -1, 0, 1, 2 >
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_short_mixed_range )
{
  // TODO(mattcalabrese) Test the result type calculators.

  auto mixed_range
    = case_range< -1, static_cast< short >( 3 ) >;
  using case_type = decltype( mixed_range );
  (void)mixed_range;

  ARGOT_CONCEPT_ENSURE( CaseLabels< case_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_type > >::case_values_t
    , value_list_t< -1, 0, 1, 2 >
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_long_mixed_range )
{
  // TODO(mattcalabrese) Test the result type calculators.

  auto mixed_range
    = case_range< -1l, static_cast< short >( 3 ) >;
  using case_type = decltype( mixed_range );
  (void)mixed_range;

  ARGOT_CONCEPT_ENSURE( CaseLabels< case_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_type > >::case_values_t
    , value_list_t< -1l, 0l, 1l, 2l >
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_enum_range )
{
  // TODO(mattcalabrese) Test the result type calculators.

  auto enum_range = case_range< fake_range::neg1, fake_range::three >;
  using case_type = decltype( enum_range );
  (void)enum_range;

  ARGOT_CONCEPT_ENSURE( CaseLabels< case_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_type > >::case_values_t
    , value_list_t< -1, 0, 1, 2 >
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_mixed_enum_range )
{
  // TODO(mattcalabrese) Test the result type calculators.

  auto enum_range = case_range< -1, fake_range::three >;
  using case_type = decltype( enum_range );
  (void)enum_range;

  ARGOT_CONCEPT_ENSURE( CaseLabels< case_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_type > >::case_values_t
    , value_list_t< -1, 0, 1, 2 >
    >
  );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
