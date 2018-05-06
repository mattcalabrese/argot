/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/empty_switch_body.hpp>

#include <argot/impossible.hpp>
#include <argot/concepts/case_labels.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/persistent_switch_body_for_type.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_value.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/concepts/switch_body_default.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_persistent.hpp>
#include <argot/switch_traits/case_values.hpp>
#include <argot/switch_traits/case_values_for_type.hpp>
#include <argot/value_list.hpp>

#include <type_traits>
#include <utility>

namespace {

namespace switch_traits = argot::switch_traits;
namespace receiver_traits = argot::receiver_traits;

using argot::empty_switch_body;
using argot::empty_switch_body_t;
using argot::Not;
using argot::PersistentSwitchBodyForType;
using argot::SameType;
using argot::SwitchBody;
using argot::SwitchBodyCase;
using argot::SwitchBodyDefault;
using argot::SwitchBodyForType;
using argot::value_list_t;
using receiver_traits::argument_list_kinds_t;
using switch_traits::argument_list_kinds_of_body_destructive_t;
using switch_traits::argument_list_kinds_of_body_persistent_t;
using switch_traits::case_value_for_type_at_v;
using switch_traits::case_values_for_type_t;
using switch_traits::case_values_t;

ARGOT_REGISTER_CONSTEXPR_TEST( test_empty_switch_body )
{
  // TODO(mattcalabrese) Do not initialize like this
  auto body = empty_switch_body;
  static_cast< void >( body );

  using body_t = decltype( body );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( empty_switch_body ), empty_switch_body_t const > );

  ARGOT_CONCEPT_ENSURE( SwitchBody< body_t > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_t< body_t >
    , value_list_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_for_type_t< body_t, int >
    , value_list_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_destructive_t< body_t, int >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_persistent_t< body_t, int >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyForType< body_t, int > );

  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, 0 > > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyDefault< body_t > > );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
