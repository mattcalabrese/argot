/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver/return_argument_references.hpp>

#include <tuple>
#include <type_traits>
#include <utility>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;

using argot::SameType;
using receiver_traits::argument_list_kinds_t;
using receiver_traits::argument_types_t;
using prov_traits::argument_list_kinds_of_destructive_t;
using prov_traits::argument_list_kinds_of_persistent_t;

ARGOT_REGISTER_CONSTEXPR_TEST( test_nullary_reference_to )
{
  decltype( auto ) provider = prov::reference_to();

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_reference_to_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_reference_to<>::type
    >
  );

  // Not required, but intentional implementation detail.
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::nothing_t
    >
  );

  // lvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_persistent_t< provider_type >
      , argument_list_kinds_t< argument_types_t<> >
      >
    );

    decltype( auto ) args
      = prov_traits::persistent_provide
        ( provider
        , receiver::return_argument_references()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant< std::tuple<> >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  // rvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_destructive_t< provider_type >
      , argument_list_kinds_t< argument_types_t<> >
      >
    );

    decltype( auto ) args
      = prov_traits::destructive_provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant< std::tuple<> >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_unary_reference_to )
{
  bool const bool_true = true;

  decltype( auto ) provider
    = prov::reference_to( bool_true );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_reference_to_t< bool const& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_reference_to< bool const& >::type
    >
  );

  // lvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_persistent_t< provider_type >
      , argument_list_kinds_t< argument_types_t< bool const& > >
      >
    );

    decltype( auto ) args
      = prov_traits::persistent_provide
        ( provider
        , receiver::return_argument_references()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant< std::tuple< bool const& > >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
    auto& tup = std::get< 0 >( args );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &bool_true );
    ARGOT_TEST_TRUE( std::get< 0 >( tup ) );
  }

  // rvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_destructive_t< provider_type >
      , argument_list_kinds_t< argument_types_t< bool const& > >
      >
    );

    decltype( auto ) args
      = prov_traits::destructive_provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant< std::tuple< bool const& > >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
    auto& tup = std::get< 0 >( args );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &bool_true );
    ARGOT_TEST_TRUE( std::get< 0 >( tup ) );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_nary_reference_to )
{
  int int_1 = 1;
  char const char_a = 'a';
  bool const bool_true = true;

  decltype( auto ) provider
    = prov::reference_to
      ( std::move( int_1 )
      , char_a
      , std::move( bool_true )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_reference_to_t
      < int&&, char const&, bool const&& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_reference_to
      < int&&, char const&, bool const&& >::type
    >
  );

  // lvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_persistent_t< provider_type >
      , argument_list_kinds_t
        < argument_types_t< int&, char const&, bool const& > >
      >
    );

    decltype( auto ) args
      = prov_traits::persistent_provide
        ( provider
        , receiver::return_argument_references()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant
        < std::tuple< int&, char const&, bool const& > >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
    auto& tup = std::get< 0 >( args );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &int_1 );
    ARGOT_TEST_EQ( std::get< 0 >( tup ), 1 );

    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &char_a );
    ARGOT_TEST_EQ( std::get< 1 >( tup ), 'a' );

    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bool_true );
    ARGOT_TEST_TRUE( std::get< 2 >( tup ) );
  }

  // rvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_destructive_t< provider_type >
      , argument_list_kinds_t
        < argument_types_t< int&&, char const&, bool const&& > >
      >
    );

    decltype( auto ) args
      = prov_traits::destructive_provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant
        < std::tuple< int&&, char const&, bool const&& > >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
    auto& tup = std::get< 0 >( args );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &int_1 );
    ARGOT_TEST_EQ( std::get< 0 >( tup ), 1 );

    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &char_a );
    ARGOT_TEST_EQ( std::get< 1 >( tup ), 'a' );

    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bool_true );
    ARGOT_TEST_TRUE( std::get< 2 >( tup ) );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
