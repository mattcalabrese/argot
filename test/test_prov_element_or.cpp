/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/call.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/prov/element_or.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/tuple_traits/get.hpp>

#include <optional>
#include <type_traits>
#include <utility>
#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace tuple_traits = argot::tuple_traits;

using argot::SameType;
using prov::element_or;
using prov::element_or_fn;
using prov::result_of_element_or;
using prov::result_of_element_or_t;
using receiver_traits::argument_list_kinds;
using receiver_traits::argument_list_kinds_t;
using receiver_traits::argument_types;
using receiver_traits::argument_types_t;

using provider_generator_type = decltype( element_or );

ARGOT_CONCEPT_ENSURE
( SameType< provider_generator_type, element_or_fn const > );

ARGOT_REGISTER_CONSTEXPR_TEST( test_engaged_lvalue_opt )
{
  int one = 1;
  std::optional< char > opt_value = 'a';

  decltype( auto ) provider = element_or( opt_value, one );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_t< std::optional< char >&, int& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or< std::optional< char >&, int& >::type
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
      , std::variant< argot::struct_< char& >, argot::struct_< int& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 'a' );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &*opt_value );
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
      , std::variant< argot::struct_< char& >, argot::struct_< int& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 'a' );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &*opt_value );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_engaged_rvalue_opt )
{
  int one = 1;
  std::optional< char > opt_value = 'a';

  decltype( auto ) provider
    = element_or( std::move( opt_value ), std::move( one ) );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_t< std::optional< char >&&, int&& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or< std::optional< char >&&, int&& >::type
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
      , std::variant< argot::struct_< char&& >, argot::struct_< int&& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 'a' );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &*opt_value );
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
      , std::variant< argot::struct_< char& >, argot::struct_< int& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 'a' );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &*opt_value );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_disengaged_lvalue_opt )
{
  int one = 1;
  std::optional< char > opt_value;

  decltype( auto ) provider = element_or( opt_value, one );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_t< std::optional< char >&, int& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or< std::optional< char >&, int& >::type
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
      , std::variant< argot::struct_< char& >, argot::struct_< int& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
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
      , std::variant< argot::struct_< char& >, argot::struct_< int& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_disengaged_rvalue_opt )
{
  int one = 1;
  std::optional< char > opt_value;

  decltype( auto ) provider
    = element_or( std::move( opt_value ), std::move( one ) );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or_t< std::optional< char >&&, int&& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_element_or< std::optional< char >&&, int&& >::type
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
      , std::variant< argot::struct_< char&& >, argot::struct_< int&& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
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
      , std::variant< argot::struct_< char& >, argot::struct_< int& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
