/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

// TODO(mattcalabrese) Add SFINAE checks for combining bodies with duplicates.
// TODO(mattcalabrese) Test binary, ternary, and larger N-ary combine.

#include <argot/switch_traits/combine.hpp>

#include "switch_body_models.hpp"

#include <argot/impossible.hpp>
#include <argot/case/case_range.hpp>
#include <argot/case/case_set.hpp>
#include <argot/case/detail/provided.hpp>
#include <argot/concepts/case_labels.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/concepts/persistent_switch_body_for_type.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_value.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/concepts/switch_body_default.hpp>
#include <argot/concepts/switch_body_default_for_type.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/receiver/return_argument_references.hpp>
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
#include <argot/switch_traits/destructive_provide_isolated_default.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_destructive.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_default_destructive.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_default_persistent.hpp>
#include <argot/switch_traits/persistent_provide_isolated_case.hpp>
#include <argot/switch_traits/persistent_provide_isolated_default.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_destructive.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_default_destructive.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_default_persistent.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/value_list.hpp>

#include <type_traits>
#include <utility>

namespace {

namespace prov = argot::prov;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace switch_traits = argot::switch_traits;
namespace tuple_traits = argot::tuple_traits;

using argot::impossible;
using argot::case_detail::provided_t;
using argot::case_range;
using argot::case_set;
using argot::case_set_t;
using argot::CaseLabels;
using argot::empty_switch_body_t;
using argot::Not;
using argot::PersistentSwitchBodyCase;
using argot::PersistentSwitchBodyDefaultForType;
using argot::PersistentSwitchBodyForType;
using argot::SameType;
using argot::SameValue;
using argot::SwitchBody;
using argot::SwitchBodyCase;
using argot::SwitchBodyDefault;
using argot::SwitchBodyDefaultForType;
using argot::SwitchBodyForType;
using argot::value_list_t;
using prov::result_of_value_of_t;
using prov::value_of;
using receiver::return_argument_references;
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
using switch_traits::combine;
using switch_traits::combine_t;
using switch_traits::destructive_provide_isolated_case;
using switch_traits::destructive_provide_isolated_default;
using switch_traits::leading_argument_list_kinds_of_case_destructive_t;
using switch_traits::leading_argument_list_kinds_of_case_persistent_t;
using switch_traits::leading_argument_list_kinds_of_default_destructive_t;
using switch_traits::leading_argument_list_kinds_of_default_persistent_t;
using switch_traits::persistent_provide_isolated_case;
using switch_traits::persistent_provide_isolated_default;
using switch_traits::trailing_argument_list_kinds_of_case_destructive_t;
using switch_traits::trailing_argument_list_kinds_of_case_persistent_t;
using switch_traits::trailing_argument_list_kinds_of_default_destructive_t;
using switch_traits::trailing_argument_list_kinds_of_default_persistent_t;

ARGOT_CONCEPT_ENSURE( SameType< decltype( combine ), combine_t const > );

ARGOT_REGISTER_CONSTEXPR_TEST( test_combine_nullary )
{
  auto body = combine();
  static_cast< void >( body );

  using body_t = decltype( body );

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

ARGOT_REGISTER_CONSTEXPR_TEST( test_combine_unary )
{
  auto body
    = combine( case_set< 0, static_cast< short >( -1 ), 42l >
               ( value_of( 5 ) )
             );

  using body_t = decltype( body );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < body_t
    , provided_t
      < case_set_t< 0, static_cast< short >( -1 ), 42l >
      , result_of_value_of_t< int&& >
      >
    >
  );

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
    , argument_list_kinds_t< argument_types_t< int&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 0 >
    , argument_list_kinds_t< argument_types_t< int const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, -1 >
    , argument_list_kinds_t< argument_types_t< int&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, -1 >
    , argument_list_kinds_t< argument_types_t< int const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 42 >
    , argument_list_kinds_t< argument_types_t< int&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 42 >
    , argument_list_kinds_t< argument_types_t< int const& > >
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
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_persistent_t< body_t, -1 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_destructive_t< body_t, 42 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < leading_argument_list_kinds_of_case_persistent_t< body_t, 42 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_destructive_t< body_t, 0 >
    , argument_list_kinds_t<>
    >
  );
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_persistent_t< body_t, 0 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_destructive_t< body_t, -1 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < trailing_argument_list_kinds_of_case_persistent_t< body_t, -1 >
    , argument_list_kinds_t<>
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

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< int >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ), 5 );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< -1 >
        ( std::move( body ), return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< int >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ), 5 );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 42 >
        ( std::move( body ), return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< int >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ), 5 );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 0 >
        ( std::move( body ), return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< int >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ), 5 );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< -1 >
        ( std::move( body ), return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< int >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ), 5 );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 42 >
        ( std::move( body ), return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< int >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ), 5 );
  }

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_destructive_t< body_t, int >
    , argument_list_kinds_t< argument_types_t< int&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_persistent_t< body_t, int >
    , argument_list_kinds_t< argument_types_t< int const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyDefault< body_t > > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_combine_no_default_with_default )
{
  auto body = combine( body_0_to_3(), body_default() );

  using body_t = decltype( body );

  ARGOT_CONCEPT_ENSURE( SwitchBody< body_t > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyDefault< body_t > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_t< body_t >
    , value_list_t< 0, 1, 2 >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_for_type_t< body_t, int >
    , value_list_t< 0, 1, 2 >
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
    , 1
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 2 >
    , 2
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 2 > );

  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 2 > );

  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, -1 > > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, 3 > > );

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
      < argument_types_t< std::integral_constant< int, 0 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 > const& > >
    >
  );

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_default
        ( std::move( body ), 4, return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< body_value_default_t >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ).value, 4 );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_default
        ( std::move( body ), 4, return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< persistent_body_value_default_t >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ).value, 4 );
  }

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_destructive_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, 1 >&& >
      , argument_types_t< std::integral_constant< int, 2 >&& >
      , argument_types_t< body_value_default_t&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_persistent_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 > const& >
      , argument_types_t< std::integral_constant< int, 1 > const& >
      , argument_types_t< std::integral_constant< int, 2 > const& >
      , argument_types_t< persistent_body_value_default_t&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyDefaultForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyDefaultForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyDefaultForType< body_t, long > > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_combine_default_with_no_default )
{
  auto body = combine( body_default(), body_0_to_3() );

  using body_t = decltype( body );

  ARGOT_CONCEPT_ENSURE( SwitchBody< body_t > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyDefault< body_t > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_t< body_t >
    , value_list_t< 0, 1, 2 >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_for_type_t< body_t, int >
    , value_list_t< 0, 1, 2 >
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
    , 1
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 2 >
    , 2
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 2 > );

  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 2 > );

  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, -1 > > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, 3 > > );

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
      < argument_types_t< std::integral_constant< int, 0 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 > const& > >
    >
  );

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_default
        ( std::move( body ), 4, return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< body_value_default_t >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ).value, 4 );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_default
        ( std::move( body ), 4, return_single_argument_value() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< persistent_body_value_default_t >
      >
    );

    ARGOT_TEST_EQ( std::get< 0 >( result ).value, 4 );
  }

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_destructive_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< body_value_default_t&& >
      , argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, 1 >&& >
      , argument_types_t< std::integral_constant< int, 2 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_persistent_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< persistent_body_value_default_t&& >
      , argument_types_t< std::integral_constant< int, 0 > const& >
      , argument_types_t< std::integral_constant< int, 1 > const& >
      , argument_types_t< std::integral_constant< int, 2 > const& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyDefaultForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyDefaultForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyDefaultForType< body_t, long > > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_combine_cases_with_unreachable )
{
  auto body = combine( body_0_to_3(), body_unreachable_case_10() );

  using body_t = decltype( body );

  ARGOT_CONCEPT_ENSURE( SwitchBody< body_t > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_t< body_t >
    , value_list_t< 0, 1, 2, 10 >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_for_type_t< body_t, int >
    , value_list_t< 0, 1, 2, 10 >
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
    , 1
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 2 >
    , 2
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 3 >
    , 10
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 2 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 10 > );

  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 2 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 10 > );

  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, -1 > > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, 3 > > );

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
      < argument_types_t< std::integral_constant< int, 0 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 10 >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 10 >
    , argument_list_kinds_t<>
    >
  );

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    using result_type
      = decltype
        ( destructive_provide_isolated_case< 10 >
          ( std::move( body ), return_argument_references() )
        );

    ARGOT_CONCEPT_ENSURE( SameType< result_type, impossible > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    using result_type
      = decltype
        ( persistent_provide_isolated_case< 10 >
          ( std::move( body ), return_argument_references() )
        );

    ARGOT_CONCEPT_ENSURE( SameType< result_type, impossible > );
  }

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_destructive_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, 1 >&& >
      , argument_types_t< std::integral_constant< int, 2 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_persistent_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 0 > const& >
      , argument_types_t< std::integral_constant< int, 1 > const& >
      , argument_types_t< std::integral_constant< int, 2 > const& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyDefaultForType< body_t, int > > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyForType< body_t, long > > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_combine_binary )
{
  auto body = combine( body_3_to_8(), body_0_to_3() );

  using body_t = decltype( body );

  ARGOT_CONCEPT_ENSURE( SwitchBody< body_t > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_t< body_t >
    , value_list_t< 3, 4, 5, 6, 7, 0, 1, 2 >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_for_type_t< body_t, int >
    , value_list_t< 3, 4, 5, 6, 7, 0, 1, 2 >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 0 >
    , 3
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 1 >
    , 4
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 2 >
    , 5
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 3 >
    , 6
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 4 >
    , 7
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 5 >
    , 0
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 6 >
    , 1
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 7 >
    , 2
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 2 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 3 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 4 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 5 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 6 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 7 > );

  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 2 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 3 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 4 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 5 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 6 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 7 > );

  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, -1 > > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, 8 > > );

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
      < argument_types_t< std::integral_constant< int, 0 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 3 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 3 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 3 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 3 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 4 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 4 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 4 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 4 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 5 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 5 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 5 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 5 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 6 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 6 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 6 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 6 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 7 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 7 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 7 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 7 > const& > >
    >
  );

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 3 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 3 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 3 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 4 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 4 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 4 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 5 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 5 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 5 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 6 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 6 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 6 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 7 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 7 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 7 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 3 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 3 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 3 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 4 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 4 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 4 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 5 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 5 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 5 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 6 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 6 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 6 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 7 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 7 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 7 > );
  }

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_destructive_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 3 >&& >
      , argument_types_t< std::integral_constant< int, 4 >&& >
      , argument_types_t< std::integral_constant< int, 5 >&& >
      , argument_types_t< std::integral_constant< int, 6 >&& >
      , argument_types_t< std::integral_constant< int, 7 >&& >
      , argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, 1 >&& >
      , argument_types_t< std::integral_constant< int, 2 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_persistent_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 3 > const& >
      , argument_types_t< std::integral_constant< int, 4 > const& >
      , argument_types_t< std::integral_constant< int, 5 > const& >
      , argument_types_t< std::integral_constant< int, 6 > const& >
      , argument_types_t< std::integral_constant< int, 7 > const& >
      , argument_types_t< std::integral_constant< int, 0 > const& >
      , argument_types_t< std::integral_constant< int, 1 > const& >
      , argument_types_t< std::integral_constant< int, 2 > const& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyDefault< body_t > > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_combine_ternary )
{
  auto body = combine( body_3_to_8(), body_0_to_3(), body_8_to_10() );

  using body_t = decltype( body );

  ARGOT_CONCEPT_ENSURE( SwitchBody< body_t > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_t< body_t >
    , value_list_t< 3, 4, 5, 6, 7, 0, 1, 2, 8, 9 >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < case_values_for_type_t< body_t, int >
    , value_list_t< 3, 4, 5, 6, 7, 0, 1, 2, 8, 9 >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 0 >
    , 3
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 1 >
    , 4
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 2 >
    , 5
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 3 >
    , 6
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 4 >
    , 7
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 5 >
    , 0
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 6 >
    , 1
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 7 >
    , 2
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 8 >
    , 8
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < case_value_for_type_at_v< body_t, int, 9 >
    , 9
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 2 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 3 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 4 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 5 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 6 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 7 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 8 > );
  ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_t, 9 > );

  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 0 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 1 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 2 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 3 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 4 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 5 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 6 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 7 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 8 > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_t, 9 > );

  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, -1 > > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_t, 10 > > );

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
      < argument_types_t< std::integral_constant< int, 0 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 1 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 1 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 2 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 2 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 3 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 3 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 3 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 3 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 4 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 4 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 4 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 4 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 5 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 5 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 5 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 5 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 6 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 6 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 6 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 6 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 7 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 7 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 7 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 7 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 8 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 8 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 8 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 8 > const& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_destructive_t< body_t, 9 >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 9 >&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_case_persistent_t< body_t, 9>
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 9 > const& > >
    >
  );

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 3 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 3 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 3 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 4 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 4 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 4 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 5 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 5 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 5 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 6 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 6 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 6 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 7 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 7 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 7 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 8 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 8 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 8 > );
  }

  {
    decltype( auto ) result
      = destructive_provide_isolated_case< 9 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 9 >&& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 9 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 0 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 0 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 1 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 1 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 1 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 2 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 2 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 2 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 3 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 3 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 3 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 4 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 4 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 4 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 5 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 5 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 5 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 6 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 6 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 6 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 7 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 7 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 7 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 8 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 8 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 8 > );
  }

  {
    decltype( auto ) result
      = persistent_provide_isolated_case< 9 >
        ( std::move( body ), return_argument_references() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < decltype( result )
      , std::variant< argot::struct_< std::integral_constant< int, 9 > const& > >
      >
    );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( std::get< 0 >( result ) ), &integral_constant_v< 9 > );
  }

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_destructive_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 3 >&& >
      , argument_types_t< std::integral_constant< int, 4 >&& >
      , argument_types_t< std::integral_constant< int, 5 >&& >
      , argument_types_t< std::integral_constant< int, 6 >&& >
      , argument_types_t< std::integral_constant< int, 7 >&& >
      , argument_types_t< std::integral_constant< int, 0 >&& >
      , argument_types_t< std::integral_constant< int, 1 >&& >
      , argument_types_t< std::integral_constant< int, 2 >&& >
      , argument_types_t< std::integral_constant< int, 8 >&& >
      , argument_types_t< std::integral_constant< int, 9 >&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_body_persistent_t< body_t, int >
    , argument_list_kinds_t
      < argument_types_t< std::integral_constant< int, 3 > const& >
      , argument_types_t< std::integral_constant< int, 4 > const& >
      , argument_types_t< std::integral_constant< int, 5 > const& >
      , argument_types_t< std::integral_constant< int, 6 > const& >
      , argument_types_t< std::integral_constant< int, 7 > const& >
      , argument_types_t< std::integral_constant< int, 0 > const& >
      , argument_types_t< std::integral_constant< int, 1 > const& >
      , argument_types_t< std::integral_constant< int, 2 > const& >
      , argument_types_t< std::integral_constant< int, 8 > const& >
      , argument_types_t< std::integral_constant< int, 9 > const& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE( SwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyForType< body_t, int > );
  ARGOT_CONCEPT_ENSURE( Not< SwitchBodyDefault< body_t > > );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
