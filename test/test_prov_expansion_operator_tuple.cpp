/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/expand/expansion_operator.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/tuple_traits/get.hpp>

#include <tuple>
#include <type_traits>
#include <variant>

#include <type_traits>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace tuple_traits = argot::tuple_traits;

using receiver::return_argument_references;
using argot::ArgumentProvider;
using argot::PersistentArgumentProvider;
using argot::SameType;

ARGOT_REGISTER_CONSTEXPR_TEST( test_expand_nullary )
{
  using namespace argot::expansion_operator;

  using tuple_type = std::tuple<>;
  tuple_type tup_to_expand{};

  decltype( auto ) provider = +tup_to_expand;

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< provision_result_type, std::variant< argot::struct_<> > > );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< provision_result_type, std::variant< argot::struct_<> > > );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_expand_nullary_moved )
{
  using namespace argot::expansion_operator;

  using tuple_type = std::tuple<>;
  tuple_type tup_to_expand{};

  decltype( auto ) provider = +std::move( tup_to_expand );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< provision_result_type, std::variant< argot::struct_<> > > );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< provision_result_type, std::variant< argot::struct_<> > > );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_expand_ternary )
{
  using namespace argot::expansion_operator;

  using tuple_type = std::tuple< int, float, char >;
  tuple_type tup_to_expand( 1, 2.f, '3' );

  decltype( auto ) provider = +tup_to_expand;

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< argot::struct_< int&, float&, char& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( tup ), &std::get< 0 >( tup_to_expand ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( tup ), &std::get< 1 >( tup_to_expand ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( tup ), &std::get< 2 >( tup_to_expand ) );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< argot::struct_< int&, float&, char& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( tup ), &std::get< 0 >( tup_to_expand ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( tup ), &std::get< 1 >( tup_to_expand ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( tup ), &std::get< 2 >( tup_to_expand ) );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_expand_ternary_moved )
{
  using namespace argot::expansion_operator;

  using tuple_type = std::tuple< int, float, char >;
  tuple_type tup_to_expand( 1, 2.f, '3' );

  decltype( auto ) provider = +std::move( tup_to_expand );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< argot::struct_< int&&, float&&, char&& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( tup ), &std::get< 0 >( tup_to_expand ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( tup ), &std::get< 1 >( tup_to_expand ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( tup ), &std::get< 2 >( tup_to_expand ) );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< argot::struct_< int&, float&, char& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( tup ), &std::get< 0 >( tup_to_expand ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( tup ), &std::get< 1 >( tup_to_expand ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( tup ), &std::get< 2 >( tup_to_expand ) );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
