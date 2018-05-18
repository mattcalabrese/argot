/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/call.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/forward_arguments_as_tuple.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/element_or_provision.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <optional>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;

using argot::SameType;
using prov::conditional;
using prov::element_or_provision;
using prov::element_or_provision_fn;
using prov::reference_to;
using prov::result_of_element_or_provision;
using prov::result_of_element_or_provision_t;
using prov::result_of_conditional_t;
using prov::result_of_reference_to_t;
using receiver_traits::argument_list_kinds;
using receiver_traits::argument_list_kinds_t;
using receiver_traits::argument_types;
using receiver_traits::argument_types_t;

using provider_generator_type = decltype( element_or_provision );

ARGOT_CONCEPT_ENSURE
( SameType< provider_generator_type, element_or_provision_fn const > );

ARGOT_REGISTER_CONSTEXPR_TEST( test_engaged_lvalue_opt )
{
  int one = 1;
  long two = 2;

  std::optional< char > opt_value = 'a';

  decltype( auto ) provider
    = element_or_provision
      ( opt_value
      , conditional
        ( true
        , reference_to( one )
        , reference_to( std::move( two ) )
        )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_provision_t
      < std::optional< char >&
      , result_of_conditional_t
        < bool&&
        , result_of_reference_to_t< int& >
        , result_of_reference_to_t< long&& >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_provision
      < std::optional< char >&
      , result_of_conditional_t
        < bool&&
        , result_of_reference_to_t< int& >
        , result_of_reference_to_t< long&& >
        >
      >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::destructive_provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using provision_result_type
      = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< char& >
                    , std::tuple< int& >, std::tuple< long&& >
                    >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( std::get< 0 >( tup ), 'a' );
    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &*opt_value );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::persistent_provide
        ( provider
        , receiver::return_argument_references()
        );

    using provision_result_type
      = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< char& >
                    , std::tuple< int& >, std::tuple< long& >
                    >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( std::get< 0 >( tup ), 'a' );
    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &*opt_value );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_engaged_rvalue_opt )
{
  int one = 1;
  long two = 2;

  std::optional< char > opt_value = 'a';

  decltype( auto ) provider
    = element_or_provision
      ( std::move( opt_value )
      , conditional
        ( true
        , reference_to( one )
        , reference_to( std::move( two ) )
        )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_provision_t
      < std::optional< char >&&
      , result_of_conditional_t
        < bool&&
        , result_of_reference_to_t< int& >
        , result_of_reference_to_t< long&& >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_provision
      < std::optional< char >&&
      , result_of_conditional_t
        < bool&&
        , result_of_reference_to_t< int& >
        , result_of_reference_to_t< long&& >
        >
      >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::destructive_provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using provision_result_type
      = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< char&& >
                    , std::tuple< int& >, std::tuple< long&& >
                    >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( std::get< 0 >( tup ), 'a' );
    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &*opt_value );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::persistent_provide
        ( provider
        , receiver::return_argument_references()
        );

    using provision_result_type
      = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< char& >
                    , std::tuple< int& >, std::tuple< long& >
                    >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( std::get< 0 >( tup ), 'a' );
    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &*opt_value );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_disengaged_lvalue_opt )
{
  int one = 1;
  long two = 2;

  std::optional< char > opt_value;

  decltype( auto ) provider
    = element_or_provision
      ( opt_value
      , conditional
        ( true
        , reference_to( one )
        , reference_to( std::move( two ) )
        )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_provision_t
      < std::optional< char >&
      , result_of_conditional_t
        < bool&&
        , result_of_reference_to_t< int& >
        , result_of_reference_to_t< long&& >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_provision
      < std::optional< char >&
      , result_of_conditional_t
        < bool&&
        , result_of_reference_to_t< int& >
        , result_of_reference_to_t< long&& >
        >
      >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::destructive_provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using provision_result_type
      = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< char& >
                    , std::tuple< int& >, std::tuple< long&& >
                    >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( std::get< 0 >( tup ), 1 );
    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::persistent_provide
        ( provider
        , receiver::return_argument_references()
        );

    using provision_result_type
      = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< char& >
                    , std::tuple< int& >, std::tuple< long& >
                    >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( std::get< 0 >( tup ), 1 );
    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_disengaged_rvalue_opt )
{
  int one = 1;
  long two = 2;

  std::optional< char > opt_value;

  decltype( auto ) provider
    = element_or_provision
      ( std::move( opt_value )
      , conditional
        ( true
        , reference_to( one )
        , reference_to( std::move( two ) )
        )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_provision_t
      < std::optional< char >&&
      , result_of_conditional_t
        < bool&&
        , result_of_reference_to_t< int& >
        , result_of_reference_to_t< long&& >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_provision
      < std::optional< char >&&
      , result_of_conditional_t
        < bool&&
        , result_of_reference_to_t< int& >
        , result_of_reference_to_t< long&& >
        >
      >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::destructive_provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using provision_result_type
      = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< char&& >
                    , std::tuple< int& >, std::tuple< long&& >
                    >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( std::get< 0 >( tup ), 1 );
    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::persistent_provide
        ( provider
        , receiver::return_argument_references()
        );

    using provision_result_type
      = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< char& >
                    , std::tuple< int& >, std::tuple< long& >
                    >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( std::get< 0 >( tup ), 1 );
    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
