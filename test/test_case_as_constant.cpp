/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/case/detail/as_constant.hpp>

#include <argot/impossible.hpp>
#include <argot/concepts/case_labels.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/persistent_switch_body_for_type.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_value.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>
#include <argot/receiver/return_single_argument_value.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_persistent.hpp>
#include <argot/switch_traits/argument_list_kinds_of_case_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/case_value_for_type_at.hpp>
#include <argot/switch_traits/case_values.hpp>
#include <argot/switch_traits/case_values_for_type.hpp>
#include <argot/switch_traits/destructive_provide_isolated_case.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_destructive.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/persistent_provide_isolated_case.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_destructive.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_persistent.hpp>
#include <argot/value_list.hpp>

#include <type_traits>
#include <utility>

namespace {

struct no_cases {};
struct test_cases {};

}

namespace argot {

template<>
struct make_concept_map< CaseLabels< no_cases > >
{
  using case_values_t = value_list_t<>;

  template< template< auto... > class Template >
  using expand_case_values_t = Template<>;
};

template<>
struct make_concept_map< CaseLabels< test_cases > >
{
  using case_values_t = value_list_t< 0, static_cast< short >( -1 ), 42l >;

  template< template< auto... > class Template >
  using expand_case_values_t = Template< 0, static_cast< short >( -1 ), 42l >;
};

}  // namespace argot

namespace {

namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace switch_traits = argot::switch_traits;

using argot::CaseLabels;
using argot::Not;
using argot::PersistentSwitchBodyCase;
using argot::PersistentSwitchBodyForType;
using argot::SameType;
using argot::SameValue;
using argot::SwitchBody;
using argot::SwitchBodyCase;
using argot::SwitchBodyForType;
using argot::access_raw_concept_map;
using argot::impossible;
using argot::case_detail::as_constant_t;
using argot::value_list_t;
using receiver::return_single_argument_value;
using receiver_traits::argument_list_kinds_t;
using receiver_traits::argument_types_t;
using switch_traits::argument_list_kinds_of_body_destructive_t;
using switch_traits::argument_list_kinds_of_body_persistent_t;
using switch_traits::argument_list_kinds_of_case_destructive_t;
using switch_traits::argument_list_kinds_of_case_persistent_t;
using switch_traits::case_value_for_type_at_v;
using switch_traits::case_values_for_type_t;
using switch_traits::case_values_t;
using switch_traits::destructive_provide_isolated_case;
using switch_traits::leading_argument_list_kinds_of_case_destructive_t;
using switch_traits::leading_argument_list_kinds_of_case_persistent_t;
using switch_traits::persistent_provide_isolated_case;
using switch_traits::trailing_argument_list_kinds_of_case_destructive_t;
using switch_traits::trailing_argument_list_kinds_of_case_persistent_t;

ARGOT_REGISTER_CONSTEXPR_TEST( test_as_constant_no_cases )
{
  using body_t = as_constant_t< no_cases >;

  body_t body{};
  static_cast< void >( body );

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

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_as_constant_basic )
{
  using body_t = as_constant_t< test_cases >;

  body_t body{};
  static_cast< void >( body );

  ARGOT_CONCEPT_ENSURE( SwitchBody< body_t > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_t< body_t >
    , value_list_t< 0, static_cast< short >( -1 ), 42l >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_for_type_t< body_t, int >
    , value_list_t< 0, -1, 42 >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 0 >
    , 0
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 1 >
    , -1
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 2 >
    , 42
    >
  );


  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, -1 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 42 > );

  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, 1 > > );

  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, -1 > );
  ARGOT_CONCEPT_ENSURE
  ( PersistentSwitchBodyCase< body_t, 42 > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 0 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 0 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, -1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, -1 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, -1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, -1 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 42 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 42 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 42 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 42 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_destructive_t< body_t, 0 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_persistent_t< body_t, 0 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_destructive_t< body_t, -1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_persistent_t< body_t, -1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_destructive_t< body_t, 42 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, -1 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_persistent_t< body_t, 42 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, -1 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_destructive_t< body_t, 0 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, -1 >&& >
      , argument_types_t< std::integral_constant< int, 42 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_persistent_t< body_t, 0 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, -1 >&& >
      , argument_types_t< std::integral_constant< int, 42 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_destructive_t< body_t, -1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 42 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_persistent_t< body_t, -1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 42 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_destructive_t< body_t, 42 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_persistent_t< body_t, 42 >
    , argument_list_kinds_t<>
    >
  );

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 0 >
        ( std::move( body ), return_single_argument_value() );
    static_cast< void >( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< std::integral_constant< int, 0 > >
      >
    );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< -1 >
        ( std::move( body ), return_single_argument_value() );
    static_cast< void >( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< std::integral_constant< int, -1 > >
      >
    );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 42 >
        ( std::move( body ), return_single_argument_value() );
    static_cast< void >( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< std::integral_constant< int, 42 > >
      >
    );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 0 >
        ( std::move( body ), return_single_argument_value() );
    static_cast< void >( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< std::integral_constant< int, 0 > >
      >
    );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< -1 >
        ( std::move( body ), return_single_argument_value() );
    static_cast< void >( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< std::integral_constant< int, -1 > >
      >
    );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 42 >
        ( std::move( body ), return_single_argument_value() );
    static_cast< void >( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< std::integral_constant< int, 42 > >
      >
    );
  }

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_destructive_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, -1 >&& >
      , argument_types_t< std::integral_constant< int, 42 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_persistent_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, -1 >&& >
      , argument_types_t< std::integral_constant< int, 42 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyForType< body_t, int > );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
