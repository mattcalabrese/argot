/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/case/case_.hpp>
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
using argot::case_;
using argot::value_list_t;

enum class fake_bool : bool { false_ = false, true_ = true };

ARGOT_REGISTER_CONSTEXPR_TEST( test_true_false )
{
  // TODO(mattcalabrese) Test the result type calculators.

  auto case_true = case_< fake_bool::true_ >;
  using case_true_type = decltype( case_true );
  (void)case_true;

  auto case_false = case_< fake_bool::false_ >;
  using case_false_type = decltype( case_false );
  (void)case_false;

  ARGOT_CONCEPT_ENSURE( CaseLabels< case_true_type > );
  ARGOT_CONCEPT_ENSURE( CaseLabels< case_false_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_true_type > >
      ::case_values_t
    , value_list_t< fake_bool::true_ >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < typename access_raw_concept_map< CaseLabels< case_false_type > >
      ::case_values_t
    , value_list_t< fake_bool::false_ >
    >
  );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
