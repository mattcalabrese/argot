/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

// TODO(mattcalabrese) Heavily test all of this.

#include <argot/prov/switch_.hpp>

#include <argot/case/case_.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/default_.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/prov/unreachable.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/value_list.hpp>

#include <tuple>
#include <type_traits>
#include <variant>

#include "switch_body_models.hpp"

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace tuple_traits = argot::tuple_traits;

using argot::ArgumentProvider;
using argot::SameType;
using argot::UnhandledSwitchableValue;
using argot::value_list_t;
using prov::result_of_switch;
using prov::result_of_switch_t;
using prov::result_of_value_of_t;
using prov::switch_;
using prov::unreachable;
using prov::unreachable_t;
using prov::value_of;
using prov::value_of_fn;
using prov_traits::argument_list_kinds_of_destructive_t;
using prov_traits::argument_list_kinds_of_persistent_t;
using prov_traits::destructive_provide;
using receiver::return_argument_references;
using receiver_traits::argument_list_kinds_t;

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_explicit_bodies_dynamic )
{
  auto provider = switch_( 0 );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t< int&& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch< int&& >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_destructive_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_persistent_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_explicit_bodies_std_integral_constant )
{
  ARGOT_CONCEPT_ENSURE( UnhandledSwitchableValue< 0 > );

  // Silence the warning just for this test (or detect it somehow).
  auto provider = switch_( std::integral_constant< int, 0 >() );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < std::integral_constant< int, 0 >&& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < std::integral_constant< int, 0 >&& >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_destructive_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_persistent_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  // Purposefully not specified in docs as it should not be depended on, but
  // the implementation currently does this.
  ARGOT_CONCEPT_ENSURE( SameType< provider_type, unreachable_t > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_empty_bodies_dynamic )
{
  auto provider = switch_( 0, body_no_cases() );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < int&&
      , body_no_cases&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < int&&
      , body_no_cases&&
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_destructive_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_persistent_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_empty_bodies_std_integral_constant )
{
  ARGOT_CONCEPT_ENSURE( UnhandledSwitchableValue< 0, body_no_cases > );

  auto provider
    = switch_( std::integral_constant< int, 0 >(), body_no_cases() );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < std::integral_constant< int, 0 >&&
      , body_no_cases&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < std::integral_constant< int, 0 >&&
      , body_no_cases&&
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_destructive_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_persistent_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  // Purposefully not specified in docs as it should not be depended on, but
  // the implementation currently does this.
  ARGOT_CONCEPT_ENSURE( SameType< provider_type, unreachable_t > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_3_dynamic )
{
  auto provider_0 = switch_( 0, body_0_to_3() );
  auto provider_1 = switch_( 1, body_0_to_3() );
  auto provider_2 = switch_( 2, body_0_to_3() );

  using provider_type = decltype( provider_0 );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < int&&
      , body_0_to_3&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < int&&
      , body_0_to_3&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 >&& >
          , argot::struct_< std::integral_constant< int, 1 >&& >
          , argot::struct_< std::integral_constant< int, 2 >&& >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // 1
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_1 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 >&& >
          , argot::struct_< std::integral_constant< int, 1 >&& >
          , argot::struct_< std::integral_constant< int, 2 >&& >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 1 );
      auto& tup = std::get< 1 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 1 > );
    }

    // 2
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_2 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 >&& >
          , argot::struct_< std::integral_constant< int, 1 >&& >
          , argot::struct_< std::integral_constant< int, 2 >&& >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 2 );
      auto& tup = std::get< 2 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 2 > );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 > const& >
          , argot::struct_< std::integral_constant< int, 1 > const& >
          , argot::struct_< std::integral_constant< int, 2 > const& >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // 1
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_1
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 > const& >
          , argot::struct_< std::integral_constant< int, 1 > const& >
          , argot::struct_< std::integral_constant< int, 2 > const& >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 1 );
      auto& tup = std::get< 1 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 1 > );
    }

    // 2
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_2
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 > const& >
          , argot::struct_< std::integral_constant< int, 1 > const& >
          , argot::struct_< std::integral_constant< int, 2 > const& >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 2 );
      auto& tup = std::get< 2 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 2 > );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_3_static )
{
  auto provider_0
    = switch_( std::integral_constant< int, 0 >(), body_0_to_3() );

  auto provider_1
    = switch_( std::integral_constant< int, 1 >(), body_0_to_3() );

  auto provider_2
    = switch_( std::integral_constant< int, 2 >(), body_0_to_3() );

  using provider_0_type = decltype( provider_0 );
  using provider_1_type = decltype( provider_1 );
  using provider_2_type = decltype( provider_2 );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_0_type > );
  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_1_type > );
  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_2_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch_t
      < std::integral_constant< int, 0 >&&
      , body_0_to_3&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch
      < std::integral_constant< int, 0 >&&
      , body_0_to_3&&
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_1_type
    , result_of_switch_t
      < std::integral_constant< int, 1 >&&
      , body_0_to_3&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_1_type
    , result_of_switch
      < std::integral_constant< int, 1 >&&
      , body_0_to_3&&
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_2_type
    , result_of_switch_t
      < std::integral_constant< int, 2 >&&
      , body_0_to_3&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_2_type
    , result_of_switch
      < std::integral_constant< int, 2 >&&
      , body_0_to_3&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 >&& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // 1
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_1 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 1 >&& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 1 > );
    }

    // 2
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_2 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 2 >&& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 2 > );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 > const& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // 1
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_1
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 1 > const& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 1 > );
    }

    // 2
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_2
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 2 > const& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 2 > );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_unreachable_case_dynamic )
{
  auto provider_0
    = switch_
      ( 0
      , body_unreachable_case_10()
      , body_0_to_3()
      );

  auto provider_unreachable
    = switch_
      ( 10
      , body_unreachable_case_10()
      , body_0_to_3()
      );

  (void)provider_unreachable;

  using provider_type = decltype( provider_0 );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < int&&
      , body_unreachable_case_10&&
      , body_0_to_3
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < int&&
      , body_unreachable_case_10&&
      , body_0_to_3
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 >&& >
          , argot::struct_< std::integral_constant< int, 1 >&& >
          , argot::struct_< std::integral_constant< int, 2 >&& >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_< std::integral_constant< int, 0 > const& >
          , argot::struct_< std::integral_constant< int, 1 > const& >
          , argot::struct_< std::integral_constant< int, 2 > const& >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_unreachable_case_static )
{
  auto provider_0
    = switch_
      ( std::integral_constant< int, 0 >()
      , body_unreachable_case_10()
      , body_0_to_3()
      );

  auto provider_unreachable
    = switch_
      ( std::integral_constant< int, 10 >()
      , body_unreachable_case_10()
      , body_0_to_3()
      );

  (void)provider_unreachable;

  using provider_0_type = decltype( provider_0 );
  using provider_unreachable_type = decltype( provider_unreachable );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_0_type > );
  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_unreachable_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch_t
      < std::integral_constant< int, 0 >&&
      , body_unreachable_case_10&&
      , body_0_to_3
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch
      < std::integral_constant< int, 0 >&&
      , body_unreachable_case_10&&
      , body_0_to_3
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_unreachable_type
    , result_of_switch_t
      < std::integral_constant< int, 10 >&&
      , body_unreachable_case_10&&
      , body_0_to_3
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_unreachable_type
    , result_of_switch
      < std::integral_constant< int, 10 >&&
      , body_unreachable_case_10&&
      , body_0_to_3
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_max_dynamic )
{
  auto provider_0 = switch_( 0, body_0_to_max() );
  auto provider_submax
    = switch_( ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1, body_0_to_max() );

  using provider_type = decltype( provider_0 );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < int&&
      , body_0_to_max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < int&&
      , body_0_to_max&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_t
          < ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_submax )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_t
          < ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
        >
      );

      ARGOT_TEST_EQ
      ( args.index(), ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 );
      auto& tup = std::get< ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >
      );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_persistent_t
          < ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_submax
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_persistent_t
          < ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
        >
      );

      ARGOT_TEST_EQ
      ( args.index(), ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 );
      auto& tup = std::get< ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >
      );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_max_static )
{
  auto provider_0
    = switch_
      ( std::integral_constant< int, 0 >()
      , body_0_to_max()
      );

  auto provider_submax
    = switch_
      ( std::integral_constant< int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >()
      , body_0_to_max()
      );

  using provider_0_type = decltype( provider_0 );
  using provider_submax_type = decltype( provider_submax );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_0_type > );
  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_submax_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch_t
      < std::integral_constant< int, 0 >&&
      , body_0_to_max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch
      < std::integral_constant< int, 0 >&&
      , body_0_to_max&&
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_submax_type
    , result_of_switch_t
      < std::integral_constant< int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >&&
      , body_0_to_max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_submax_type
    , result_of_switch
      < std::integral_constant< int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >&&
      , body_0_to_max&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_submax )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_
            < std::integral_constant
              < int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >
      );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_submax
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_
            < std::integral_constant
              < int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 > const&
            >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >
      );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_supmax_dynamic )
{
  auto provider_0 = switch_( 0, body_0_to_supmax() );
  auto provider_max
    = switch_( ARGOT_MAX_PREPROCESSED_SWITCH_CASES, body_0_to_supmax() );

  using provider_type = decltype( provider_0 );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < int&&
      , body_0_to_supmax&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < int&&
      , body_0_to_supmax&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_t
          < ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_max )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_t
          < ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
        >
      );

      ARGOT_TEST_EQ
      ( args.index(), ARGOT_MAX_PREPROCESSED_SWITCH_CASES );
      auto& tup = std::get< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_persistent_t
          < ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_max
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_persistent_t
          < ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
        >
      );

      ARGOT_TEST_EQ
      ( args.index(), ARGOT_MAX_PREPROCESSED_SWITCH_CASES );
      auto& tup = std::get< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_supmax_static )
{
  auto provider_0
    = switch_
      ( std::integral_constant< int, 0 >()
      , body_0_to_supmax()
      );

  auto provider_max
    = switch_
      ( std::integral_constant< int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES >()
      , body_0_to_supmax()
      );

  using provider_0_type = decltype( provider_0 );
  using provider_max_type = decltype( provider_max );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_0_type > );
  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_max_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch_t
      < std::integral_constant< int, 0 >&&
      , body_0_to_supmax&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch
      < std::integral_constant< int, 0 >&&
      , body_0_to_supmax&&
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_max_type
    , result_of_switch_t
      < std::integral_constant< int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES >&&
      , body_0_to_supmax&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_max_type
    , result_of_switch
      < std::integral_constant< int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES >&&
      , body_0_to_supmax&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_max )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_
            < std::integral_constant
              < int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES >&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_max
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_
            < std::integral_constant
              < int, ARGOT_MAX_PREPROCESSED_SWITCH_CASES > const&
            >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_2max_dynamic )
{
  auto provider_0 = switch_( 0, body_0_to_2max() );
  auto provider_submax
    = switch_( 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1, body_0_to_2max() );

  using provider_type = decltype( provider_0 );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < int&&
      , body_0_to_2max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < int&&
      , body_0_to_2max&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_t
          < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_submax )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_t
          < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
        >
      );

      ARGOT_TEST_EQ
      ( args.index(), 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 );
      auto& tup
        = std::get< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >
      );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_persistent_t
          < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_submax
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_persistent_t
          < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
        >
      );

      ARGOT_TEST_EQ
      ( args.index(), 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 );
      auto& tup
        = std::get< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >
      );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_2max_static )
{
  auto provider_0
    = switch_
      ( std::integral_constant< int, 0 >()
      , body_0_to_2max()
      );

  auto provider_submax
    = switch_
      ( std::integral_constant
        < int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >()
      , body_0_to_2max()
      );

  using provider_0_type = decltype( provider_0 );
  using provider_submax_type = decltype( provider_submax );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_0_type > );
  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_submax_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch_t
      < std::integral_constant< int, 0 >&&
      , body_0_to_2max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch
      < std::integral_constant< int, 0 >&&
      , body_0_to_2max&&
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_submax_type
    , result_of_switch_t
      < std::integral_constant
        < int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >&&
      , body_0_to_2max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_submax_type
    , result_of_switch
      < std::integral_constant
        < int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >&&
      , body_0_to_2max&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_submax )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_
            < std::integral_constant
              < int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >
      );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_submax
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_
            < std::integral_constant
              < int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 > const&
            >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 >
      );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_sup2max_dynamic )
{
  auto provider_0 = switch_( 0, body_0_to_sup2max() );
  auto provider_2max
    = switch_( 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES, body_0_to_sup2max() );

  using provider_type = decltype( provider_0 );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch_t
      < int&&
      , body_0_to_sup2max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_switch
      < int&&
      , body_0_to_sup2max&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_t
          < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_2max )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_t
          < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
        >
      );

      ARGOT_TEST_EQ
      ( args.index(), 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES );
      auto& tup = std::get< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_persistent_t
          < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_2max
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , variant_of_argument_references_of_size_persistent_t
          < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
        >
      );

      ARGOT_TEST_EQ
      ( args.index(), 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES );
      auto& tup = std::get< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_0_to_sup2max_static )
{
  auto provider_0
    = switch_
      ( std::integral_constant< int, 0 >()
      , body_0_to_sup2max()
      );

  auto provider_2max
    = switch_
      ( std::integral_constant
        < int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >()
      , body_0_to_sup2max()
      );

  using provider_0_type = decltype( provider_0 );
  using provider_2max_type = decltype( provider_2max );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_0_type > );
  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_2max_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch_t
      < std::integral_constant< int, 0 >&&
      , body_0_to_sup2max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_0_type
    , result_of_switch
      < std::integral_constant< int, 0 >&&
      , body_0_to_sup2max&&
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_2max_type
    , result_of_switch_t
      < std::integral_constant< int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >&&
      , body_0_to_sup2max&&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_2max_type
    , result_of_switch
      < std::integral_constant< int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >&&
      , body_0_to_sup2max&&
      >::type
    >
  );

  // rvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_0 )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 >&& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::destructive_provide
          ( std::move( provider_2max )
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_
            < std::integral_constant
              < int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      );
    }
  }

  // lvalue
  {
    // 0
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_0
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant< argot::struct_< std::integral_constant< int, 0 > const& > >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup ), &integral_constant_v< 0 > );
    }

    // submax
    {
      decltype( auto ) args
        = prov_traits::persistent_provide
          ( provider_2max
          , return_argument_references()
          );

      using args_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < args_type
        , std::variant
          < argot::struct_
            < std::integral_constant
              < int, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES > const&
            >
          >
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );
      auto& tup = std::get< 0 >( args );

      ARGOT_TEST_EQ
      ( &tuple_traits::get< 0 >( tup )
      , &integral_constant_v< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
