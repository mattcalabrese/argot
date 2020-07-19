/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/variant_traits/get.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <type_traits>
#include <utility>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace tuple_traits = argot::tuple_traits;
namespace variant_traits = argot::variant_traits;

using argot::SameType;
using argot::discriminated_union;
using receiver_traits::argument_list_kinds_t;
using receiver_traits::argument_types_t;
using prov_traits::argument_list_kinds_of_destructive_t;
using prov_traits::argument_list_kinds_of_persistent_t;

ARGOT_REGISTER_CONSTEXPR_TEST( test_nullary_value_of )
{
  decltype( auto ) provider = prov::value_of();

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_value_of_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_value_of<>::type
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
      , discriminated_union< argot::struct_<> >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );
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
      , discriminated_union< argot::struct_<> >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_unary_value_of )
{
  bool const bool_true = true;

  decltype( auto ) provider
    = prov::value_of( bool_true );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_value_of_t< bool const& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_value_of< bool const& >::type
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
      , discriminated_union< argot::struct_< bool const& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );
    auto& tup = variant_traits::get< 0 >( args );

    ARGOT_TEST_NE( &tuple_traits::get< 0 >( tup ), &bool_true );
    ARGOT_TEST_TRUE( tuple_traits::get< 0 >( tup ) );
  }

  // rvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_destructive_t< provider_type >
      , argument_list_kinds_t< argument_types_t< bool&& > >
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
      , discriminated_union< argot::struct_< bool&& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );
    auto& tup = variant_traits::get< 0 >( args );

    ARGOT_TEST_NE( &tuple_traits::get< 0 >( tup ), &bool_true );
    ARGOT_TEST_TRUE( tuple_traits::get< 0 >( tup ) );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_nary_value_of )
{
  int int_1 = 1;
  char const char_a = 'a';
  bool const bool_true = true;

  decltype( auto ) provider
    = prov::value_of
      ( std::move( int_1 )
      , char_a
      , std::move( bool_true )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_value_of_t
      < int&&, char const&, bool const&& >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_value_of
      < int&&, char const&, bool const&& >::type
    >
  );

  // lvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_persistent_t< provider_type >
      , argument_list_kinds_t
        < argument_types_t< int const&, char const&, bool const& > >
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
      , discriminated_union
        < argot::struct_< int const&, char const&, bool const& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );
    auto& tup = variant_traits::get< 0 >( args );

    ARGOT_TEST_NE( &tuple_traits::get< 0 >( tup ), &int_1 );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );

    ARGOT_TEST_NE( &tuple_traits::get< 1 >( tup ), &char_a );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 'a' );

    ARGOT_TEST_NE( &tuple_traits::get< 2 >( tup ), &bool_true );
    ARGOT_TEST_TRUE( tuple_traits::get< 2 >( tup ) );
  }

  // rvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < argument_list_kinds_of_destructive_t< provider_type >
      , argument_list_kinds_t< argument_types_t< int&&, char&&, bool&& > >
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
      , discriminated_union
        < argot::struct_< int&&, char&&, bool&& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );
    auto& tup = variant_traits::get< 0 >( args );

    ARGOT_TEST_NE( &tuple_traits::get< 0 >( tup ), &int_1 );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );

    ARGOT_TEST_NE( &tuple_traits::get< 1 >( tup ), &char_a );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 'a' );

    ARGOT_TEST_NE( &tuple_traits::get< 2 >( tup ), &bool_true );
    ARGOT_TEST_TRUE( tuple_traits::get< 2 >( tup ) );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
