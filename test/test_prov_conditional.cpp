/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/call.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/forward_arguments_as_tuple.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/reducer/to_boost_variant.hpp>
#include <argot/tuple_traits/get.hpp>

#include <type_traits>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace tuple_traits = argot::tuple_traits;

using argot::SameType;
using prov::conditional;
using prov::conditional_fn;
using prov::result_of_conditional;
using prov::result_of_conditional_t;
using receiver_traits::argument_list_kinds;
using receiver_traits::argument_list_kinds_t;
using receiver_traits::argument_types;
using receiver_traits::argument_types_t;

using provider_generator_type = decltype( conditional );

ARGOT_CONCEPT_ENSURE
( SameType< provider_generator_type, conditional_fn const > );

ARGOT_REGISTER_CONSTEXPR_TEST( test_basic_static_branch )
{
  int one = 1;
  long two = 2;

  decltype( auto ) one_provider
    = conditional
      ( std::true_type()
      , prov::reference_to( std::move( one ) )
      , prov::reference_to( std::move( two ) )
      );

  using one_provider_type = decltype( one_provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < one_provider_type
    , prov::result_of_conditional_t
      < std::true_type
      , prov::result_of_reference_to_t< int&& >
      , prov::result_of_reference_to_t< long&& >
      >
    >
  );

  decltype( auto ) two_provider
    = conditional
      ( std::false_type()
      , prov::reference_to( std::move( one ) )
      , prov::reference_to( std::move( two ) )
      );

  using two_provider_type = decltype( two_provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < two_provider_type
    , prov::result_of_conditional
      < std::false_type
      , prov::result_of_reference_to_t< int&& >
      , prov::result_of_reference_to_t< long&& >
      >::type
    >
  );

  // rvalue provision
  {
    // one_provider
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( one_provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< argot::struct_< int&& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    }

    // two_provider
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( two_provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< argot::struct_< long&& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 2 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &two );
    }
  }

  // lvalue provision
  {
    // one_provider
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( one_provider
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< argot::struct_< int& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    }

    // two_provider
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( two_provider
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< argot::struct_< long& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 2 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &two );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_basic_branch )
{
  int one = 1;
  long two = 2;

  decltype( auto ) one_provider
    = conditional
      ( true
      , prov::reference_to( std::move( one ) )
      , prov::reference_to( std::move( two ) )
      );

  using one_provider_type = decltype( one_provider );

  decltype( auto ) two_provider
    = conditional
      ( false
      , prov::reference_to( std::move( one ) )
      , prov::reference_to( std::move( two ) )
      );

  using two_provider_type = decltype( two_provider );

  ARGOT_CONCEPT_ENSURE( SameType< one_provider_type, two_provider_type > );

  using provider_type = one_provider_type;

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_conditional_t
      < bool&&
      , prov::result_of_reference_to_t< int&& >
      , prov::result_of_reference_to_t< long&& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_conditional
      < bool&&
      , prov::result_of_reference_to_t< int&& >
      , prov::result_of_reference_to_t< long&& >
      >::type
    >
  );

  // rvalue provision
  {
    // one_provider
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( one_provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< argot::struct_< int&& >, argot::struct_< long&& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    }

    // two_provider
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( two_provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< argot::struct_< int&& >, argot::struct_< long&& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 2 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &two );
    }
  }

  // lvalue provision
  {
    // one_provider
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( one_provider
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< argot::struct_< int& >, argot::struct_< long& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    }

    // two_provider
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( two_provider
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< argot::struct_< int& >, argot::struct_< long& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 2 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &two );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
