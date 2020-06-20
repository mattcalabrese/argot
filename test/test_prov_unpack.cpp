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
#include <argot/prov/unpack.hpp>
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

using prov::unpack;
using prov::unpack_fn;
using prov::result_of_unpack;
using prov::result_of_unpack_t;
using receiver::return_argument_references;
using argot::ArgumentProvider;
using argot::PersistentArgumentProvider;
using argot::SameType;

ARGOT_REGISTER_CONSTEXPR_TEST( test_unpack_nullary )
{
  {
    using function_object_type = decltype( prov::unpack );

    ARGOT_CONCEPT_ENSURE( SameType< function_object_type, unpack_fn const > );
  }

  using tuple_type = std::tuple<>;
  tuple_type tup_to_unpack{};

  decltype( auto ) provider = unpack( tup_to_unpack );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, result_of_unpack_t< tuple_type& > > );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, result_of_unpack< tuple_type& >::type > );

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

ARGOT_REGISTER_CONSTEXPR_TEST( test_unpack_nullary_moved )
{
  using tuple_type = std::tuple<>;
  tuple_type tup_to_unpack{};

  decltype( auto ) provider = unpack( std::move( tup_to_unpack ) );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, result_of_unpack_t< tuple_type&& > > );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, result_of_unpack< tuple_type&& >::type > );

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

ARGOT_REGISTER_CONSTEXPR_TEST( test_unpack_ternary )
{
  using tuple_type = std::tuple< int, float, char >;
  tuple_type tup_to_unpack( 1, 2.f, '3' );

  decltype( auto ) provider = unpack( tup_to_unpack );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, result_of_unpack_t< tuple_type& > > );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, result_of_unpack< tuple_type& >::type > );

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
    ( &tuple_traits::get< 0 >( tup ), &std::get< 0 >( tup_to_unpack ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( tup ), &std::get< 1 >( tup_to_unpack ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( tup ), &std::get< 2 >( tup_to_unpack ) );
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
    ( &tuple_traits::get< 0 >( tup ), &std::get< 0 >( tup_to_unpack ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( tup ), &std::get< 1 >( tup_to_unpack ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( tup ), &std::get< 2 >( tup_to_unpack ) );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_unpack_ternary_moved )
{
  using tuple_type = std::tuple< int, float, char >;
  tuple_type tup_to_unpack( 1, 2.f, '3' );

  decltype( auto ) provider = unpack( std::move( tup_to_unpack ) );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, result_of_unpack_t< tuple_type&& > > );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, result_of_unpack< tuple_type&& >::type > );

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
    ( &tuple_traits::get< 0 >( tup ), &std::get< 0 >( tup_to_unpack ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( tup ), &std::get< 1 >( tup_to_unpack ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( tup ), &std::get< 2 >( tup_to_unpack ) );
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
    ( &tuple_traits::get< 0 >( tup ), &std::get< 0 >( tup_to_unpack ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( tup ), &std::get< 1 >( tup_to_unpack ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( tup ), &std::get< 2 >( tup_to_unpack ) );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
