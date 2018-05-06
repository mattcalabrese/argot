/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/expand/expansion_operator.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/receiver/return_argument_references.hpp>

#include <type_traits>
#include <tuple>
#include <utility>

namespace {

namespace prov = argot::prov;
namespace receiver = argot::receiver;
namespace prov_traits = argot::prov_traits;

using argot::SameType;

using prov::conditional;
using prov::nothing;
using prov::nothing_t;
using prov::result_of_conditional_t;
using prov::result_of_value_of_t;
using prov::value_of;

// TODO(mattcalabrese) Test when top-level provider is branching

ARGOT_REGISTER_CONSTEXPR_TEST( test_unary_nonbranch_expand )
{
  using namespace argot::expansion_operator;

  int one = 1;

  ARGOT_CONCEPT_ENSURE
  ( argot::ExpandableArgumentProvider
    < decltype( value_of( std::forward_as_tuple( std::move( one ) ) ) )
    >
  );

  decltype( auto ) provider
    = +value_of( std::forward_as_tuple( std::move( one ) ) );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< int&& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , receiver::return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< int& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_binary_nonbranch_expand )
{
  using namespace argot::expansion_operator;

  int one = 1;
  long two = 2;
  char three = 3;
  short four = 4;

  decltype( auto ) provider
    = +value_of
      ( std::forward_as_tuple( std::move( one ), two )
      , std::forward_as_tuple( three, std::move( four ) )
      );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< int&&, long&, char&, short&& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &three );
    ARGOT_TEST_EQ( &std::get< 3 >( tup ), &four );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , receiver::return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< int&, long&, char&, short& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &three );
    ARGOT_TEST_EQ( &std::get< 3 >( tup ), &four );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_ternary_nonbranch_expand )
{
  using namespace argot::expansion_operator;

  int one = 1;
  long two = 2;
  char three = 3;
  short four = 4;
  long long five = 5;
  double six = 6.;

  decltype( auto ) provider
    = +value_of
      ( std::forward_as_tuple( std::move( one ), two )
      , std::forward_as_tuple( three, std::move( four ) )
      , std::forward_as_tuple( std::move( five ), six )
      );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple< int&&, long&, char&, short&&, long long&&, double& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &three );
    ARGOT_TEST_EQ( &std::get< 3 >( tup ), &four );
    ARGOT_TEST_EQ( &std::get< 4 >( tup ), &five );
    ARGOT_TEST_EQ( &std::get< 5 >( tup ), &six );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , receiver::return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple< int&, long&, char&, short&, long long&, double& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &three );
    ARGOT_TEST_EQ( &std::get< 3 >( tup ), &four );
    ARGOT_TEST_EQ( &std::get< 4 >( tup ), &five );
    ARGOT_TEST_EQ( &std::get< 5 >( tup ), &six );
  }

  return 0;
}

// TODO(mattcalabrese) Test expand with a top-level branching provider.

ARGOT_EXECUTE_TESTS();

}  // namespace
