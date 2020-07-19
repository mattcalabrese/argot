/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/prov/squash.hpp>

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/variant_traits/get.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <type_traits>
#include <utility>

namespace {

namespace prov = argot::prov;
namespace receiver = argot::receiver;
namespace prov_traits = argot::prov_traits;
namespace tuple_traits = argot::tuple_traits;
namespace variant_traits = argot::variant_traits;

using argot::SameType;

using argot::discriminated_union;
using prov::conditional;
using prov::nothing;
using prov::nothing_t;
using prov::reference_to;
using prov::result_of_conditional_t;
using prov::result_of_squash;
using prov::result_of_squash_t;
using prov::result_of_reference_to_t;
using prov::result_of_value_of_t;
using prov::squash;
using prov::squash_fn;
using prov::value_of;

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( squash )
  , squash_fn const
  >
);

// TODO(mattcalabrese) Test when top-level provider is branching

// TODO(mattcalabrese)
//   Test that unary squash perform their compile-time optimizations (identity).
ARGOT_REGISTER_CONSTEXPR_TEST( test_nullary_squash )
{
  decltype( auto ) provider = squash( nothing );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash_t< nothing_t >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash< nothing_t >::type
    >
  );

  // Not required, but intended implementation detail.
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_of_squash_t< nothing_t >
    , nothing_t
    >
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
      , discriminated_union< argot::struct_<> >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
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
      , discriminated_union< argot::struct_<> >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_unary_nonbranch_squash )
{
  int one = 1;

  decltype( auto ) provider
    = squash( value_of( reference_to( std::move( one ) ) ) );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash_t
      < result_of_value_of_t< result_of_reference_to_t< int&& > > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash
      < result_of_value_of_t< result_of_reference_to_t< int&& > > >::type
    >
  );

  // Not required, but intended implementation detail.
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_of_squash_t
      < result_of_value_of_t< result_of_reference_to_t< int&& > > >
    , result_of_reference_to_t< int&& >
    >
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
      , discriminated_union< argot::struct_< int&& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
    auto& tup = variant_traits::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
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
      , discriminated_union< argot::struct_< int& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
    auto& tup = variant_traits::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_unary_branch_squash )
{
  int one = 1;
  long two = 2;

  decltype( auto ) one_provider
    = squash
      ( value_of
        ( conditional
          ( true
          , reference_to( std::move( one ) )
          , reference_to( std::move( two ) )
          )
        )
      );

  using one_provider_type = decltype( one_provider );

  decltype( auto ) two_provider
    = squash
      ( value_of
        ( conditional
          ( false
          , reference_to( std::move( one ) )
          , reference_to( std::move( two ) )
          )
        )
      );

  using two_provider_type = decltype( two_provider );

  ARGOT_CONCEPT_ENSURE( SameType< one_provider_type, two_provider_type > );

  using provider_type = one_provider_type;

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash_t
      < result_of_value_of_t
        < result_of_conditional_t
          < bool&&
          , result_of_reference_to_t< int&& >
          , result_of_reference_to_t< long&& >
          >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash
      < result_of_value_of_t
        < result_of_conditional_t
          < bool&&
          , result_of_reference_to_t< int&& >
          , result_of_reference_to_t< long&& >
          >
        >
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

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union< argot::struct_< int&& >, argot::struct_< long&& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

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

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union< argot::struct_< int&& >, argot::struct_< long&& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
      auto& tup = variant_traits::get< 1 >( provision_result );

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

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union< argot::struct_< int& >, argot::struct_< long& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

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

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union< argot::struct_< int& >, argot::struct_< long& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
      auto& tup = variant_traits::get< 1 >( provision_result );

      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 2 );
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &two );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_binary_nonbranch_squash )
{
  int one = 1;
  long two = 2;
  char three = 3;
  short four = 4;

  decltype( auto ) provider
    = squash
      ( value_of
        ( reference_to( std::move( one ), two )
        , reference_to( three, std::move( four ) )
        )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash_t
      < result_of_value_of_t
        < result_of_reference_to_t< int&&, long& >
        , result_of_reference_to_t< char&, short&& >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash
      < result_of_value_of_t
        < result_of_reference_to_t< int&&, long& >
        , result_of_reference_to_t< char&, short&& >
        >
      >::type
    >
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
      , discriminated_union< argot::struct_< int&&, long&, char&, short&& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
    auto& tup = variant_traits::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &three );
    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &four );
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
      , discriminated_union< argot::struct_< int&, long&, char&, short& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
    auto& tup = variant_traits::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &three );
    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &four );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_binary_branch_squash )
{
  int one = 1;
  long two = 2;
  short three = 3;
  long long four = 4;
  char a = 'a';
  wchar_t b = 'b';
  char16_t c = 'c';
  char32_t d = 'd';

  decltype( auto ) provider_one_a
    = squash
      ( value_of
        ( conditional
          ( true
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( true
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        )
      );

  decltype( auto ) provider_one_c
    = squash
      ( value_of
        ( conditional
          ( true
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( false
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        )
      );

  decltype( auto ) provider_three_a
    = squash
      ( value_of
        ( conditional
          ( false
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( true
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        )
      );

  decltype( auto ) provider_three_c
    = squash
      ( value_of
        ( conditional
          ( false
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( false
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        )
      );

  using provider_type = decltype( provider_one_a );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash_t
      < result_of_value_of_t
        < result_of_conditional_t
          < bool
          , result_of_reference_to_t< int&&, long& >
          , result_of_reference_to_t< short&, long long&& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< char&&, wchar_t& >
          , result_of_reference_to_t< char16_t&, char32_t&& >
          >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash
      < result_of_value_of_t
        < result_of_conditional_t
          < bool
          , result_of_reference_to_t< int&&, long& >
          , result_of_reference_to_t< short&, long long&& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< char&&, wchar_t& >
          , result_of_reference_to_t< char16_t&, char32_t&& >
          >
        >
      >::type
    >
  );

  // rvalue provision
  {
    // one a
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_one_a )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_< int&&, long&, char&&, wchar_t& >
          , argot::struct_< int&&, long&, char16_t&, char32_t&& >
          , argot::struct_< short&, long long&&, char&&, wchar_t& >
          , argot::struct_< short&, long long&&, char16_t&, char32_t&& >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
    }

    // one c
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_one_c )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_< int&&, long&, char&&, wchar_t& >
          , argot::struct_< int&&, long&, char16_t&, char32_t&& >
          , argot::struct_< short&, long long&&, char&&, wchar_t& >
          , argot::struct_< short&, long long&&, char16_t&, char32_t&& >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
      auto& tup = variant_traits::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
    }

    // three a
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_three_a )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_< int&&, long&, char&&, wchar_t& >
          , argot::struct_< int&&, long&, char16_t&, char32_t&& >
          , argot::struct_< short&, long long&&, char&&, wchar_t& >
          , argot::struct_< short&, long long&&, char16_t&, char32_t&& >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
      auto& tup = variant_traits::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
    }

    // three c
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_three_c )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_< int&&, long&, char&&, wchar_t& >
          , argot::struct_< int&&, long&, char16_t&, char32_t&& >
          , argot::struct_< short&, long long&&, char&&, wchar_t& >
          , argot::struct_< short&, long long&&, char16_t&, char32_t&& >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 3 );
      auto& tup = variant_traits::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
    }
  }

  // lvalue provision
  {
    // one a
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_one_a
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_< int&, long&, char&, wchar_t& >
          , argot::struct_< int&, long&, char16_t&, char32_t& >
          , argot::struct_< short&, long long&, char&, wchar_t& >
          , argot::struct_< short&, long long&, char16_t&, char32_t& >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
    }

    // one c
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_one_c
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_< int&, long&, char&, wchar_t& >
          , argot::struct_< int&, long&, char16_t&, char32_t& >
          , argot::struct_< short&, long long&, char&, wchar_t& >
          , argot::struct_< short&, long long&, char16_t&, char32_t& >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
      auto& tup = variant_traits::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
    }

    // three a
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_three_a
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_< int&, long&, char&, wchar_t& >
          , argot::struct_< int&, long&, char16_t&, char32_t& >
          , argot::struct_< short&, long long&, char&, wchar_t& >
          , argot::struct_< short&, long long&, char16_t&, char32_t& >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
      auto& tup = variant_traits::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
    }

    // three c
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_three_c
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_< int&, long&, char&, wchar_t& >
          , argot::struct_< int&, long&, char16_t&, char32_t& >
          , argot::struct_< short&, long long&, char&, wchar_t& >
          , argot::struct_< short&, long long&, char16_t&, char32_t& >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 3 );
      auto& tup = variant_traits::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_ternary_nonbranch_squash )
{
  int one = 1;
  long two = 2;
  char three = 3;
  short four = 4;
  long long five = 5;
  double six = 6.;

  decltype( auto ) provider
    = squash
      ( value_of
        ( reference_to( std::move( one ), two )
        , reference_to( three, std::move( four ) )
        , reference_to( std::move( five ), six )
        )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash_t
      < result_of_value_of_t
        < result_of_reference_to_t< int&&, long& >
        , result_of_reference_to_t< char&, short&& >
        , result_of_reference_to_t< long long&&, double& >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash
      < result_of_value_of_t
        < result_of_reference_to_t< int&&, long& >
        , result_of_reference_to_t< char&, short&& >
        , result_of_reference_to_t< long long&&, double& >
        >
      >::type
    >
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
      , discriminated_union
        < argot::struct_< int&&, long&, char&, short&&, long long&&, double& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
    auto& tup = variant_traits::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &three );
    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &four );
    ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &five );
    ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &six );
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
      , discriminated_union
        < argot::struct_< int&, long&, char&, short&, long long&, double& > >
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
    auto& tup = variant_traits::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &three );
    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &four );
    ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &five );
    ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &six );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_ternary_branch_squash )
{
  int one = 1;
  long two = 2;
  short three = 3;
  long long four = 4;
  char a = 'a';
  wchar_t b = 'b';
  char16_t c = 'c';
  char32_t d = 'd';
  unsigned u_one = 1;
  unsigned long u_two = 2;
  unsigned short u_three = 3;
  unsigned long long u_four = 4;

  decltype( auto ) provider_one_a_one
    = squash
      ( value_of
        ( conditional
          ( true
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( true
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        , conditional
          ( true
          , reference_to( std::move( u_one ), u_two )
          , reference_to( u_three, std::move( u_four ) )
          )
        )
      );

  decltype( auto ) provider_one_a_three
    = squash
      ( value_of
        ( conditional
          ( true
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( true
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        , conditional
          ( false
          , reference_to( std::move( u_one ), u_two )
          , reference_to( u_three, std::move( u_four ) )
          )
        )
      );

  decltype( auto ) provider_one_c_one
    = squash
      ( value_of
        ( conditional
          ( true
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( false
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        , conditional
          ( true
          , reference_to( std::move( u_one ), u_two )
          , reference_to( u_three, std::move( u_four ) )
          )
        )
      );

  decltype( auto ) provider_one_c_three
    = squash
      ( value_of
        ( conditional
          ( true
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( false
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        , conditional
          ( false
          , reference_to( std::move( u_one ), u_two )
          , reference_to( u_three, std::move( u_four ) )
          )
        )
      );

  decltype( auto ) provider_three_a_one
    = squash
      ( value_of
        ( conditional
          ( false
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( true
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        , conditional
          ( true
          , reference_to( std::move( u_one ), u_two )
          , reference_to( u_three, std::move( u_four ) )
          )
        )
      );

  decltype( auto ) provider_three_a_three
    = squash
      ( value_of
        ( conditional
          ( false
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( true
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        , conditional
          ( false
          , reference_to( std::move( u_one ), u_two )
          , reference_to( u_three, std::move( u_four ) )
          )
        )
      );

  decltype( auto ) provider_three_c_one
    = squash
      ( value_of
        ( conditional
          ( false
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( false
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        , conditional
          ( true
          , reference_to( std::move( u_one ), u_two )
          , reference_to( u_three, std::move( u_four ) )
          )
        )
      );

  decltype( auto ) provider_three_c_three
    = squash
      ( value_of
        ( conditional
          ( false
          , reference_to( std::move( one ), two )
          , reference_to( three, std::move( four ) )
          )
        , conditional
          ( false
          , reference_to( std::move( a ), b )
          , reference_to( c, std::move( d ) )
          )
        , conditional
          ( false
          , reference_to( std::move( u_one ), u_two )
          , reference_to( u_three, std::move( u_four ) )
          )
        )
      );

  using provider_type = decltype( provider_one_a_one );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash_t
      < result_of_value_of_t
        < result_of_conditional_t
          < bool
          , result_of_reference_to_t< int&&, long& >
          , result_of_reference_to_t< short&, long long&& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< char&&, wchar_t& >
          , result_of_reference_to_t< char16_t&, char32_t&& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< unsigned&&, unsigned long& >
          , result_of_reference_to_t< unsigned short&, unsigned long long&& >
          >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_squash
      < result_of_value_of_t
        < result_of_conditional_t
          < bool
          , result_of_reference_to_t< int&&, long& >
          , result_of_reference_to_t< short&, long long&& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< char&&, wchar_t& >
          , result_of_reference_to_t< char16_t&, char32_t&& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< unsigned&&, unsigned long& >
          , result_of_reference_to_t< unsigned short&, unsigned long long&& >
          >
        >
      >::type
    >
  );

  // rvalue provision
  {
    // one a one
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_one_a_one )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_one );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_two );
    }

    // one a three
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_one_a_three )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
      auto& tup = variant_traits::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_three );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_four );
    }

    // one c one
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_one_c_one )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
      auto& tup = variant_traits::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_one );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_two );
    }

    // one c three
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_one_c_three )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 3 );
      auto& tup = variant_traits::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_three );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_four );
    }

    // three a one
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_three_a_one )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 4 );
      auto& tup = variant_traits::get< 4 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_one );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_two );
    }

    // three a three
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_three_a_three )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 5 );
      auto& tup = variant_traits::get< 5 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_three );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_four );
    }

    // three c one
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_three_c_one )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 6 );
      auto& tup = variant_traits::get< 6 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_one );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_two );
    }

    // three c three
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_three_c_three )
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < int&&, long&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char&&, wchar_t&
            , unsigned short&, unsigned long long&&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned&&, unsigned long&
            >
          , argot::struct_
            < short&, long long&&, char16_t&, char32_t&&
            , unsigned short&, unsigned long long&&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 7 );
      auto& tup = variant_traits::get< 7 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_three );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_four );
    }
  }

  // lvalue provision
  {
    // one a one
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_one_a_one
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_one );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_two );
    }

    // one a three
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_one_a_three
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
      auto& tup = variant_traits::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_three );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_four );
    }

    // one c one
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_one_c_one
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
      auto& tup = variant_traits::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_one );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_two );
    }

    // one c three
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_one_c_three
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 3 );
      auto& tup = variant_traits::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_three );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_four );
    }

    // three a one
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_three_a_one
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 4 );
      auto& tup = variant_traits::get< 4 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_one );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_two );
    }

    // three a three
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_three_a_three
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 5 );
      auto& tup = variant_traits::get< 5 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &b );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_three );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_four );
    }

    // three c one
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_three_c_one
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 6 );
      auto& tup = variant_traits::get< 6 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_one );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_two );
    }

    // three c three
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_three_c_three
          , receiver::return_argument_references()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < int&, long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char&, wchar_t&
            , unsigned short&, unsigned long long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned&, unsigned long&
            >
          , argot::struct_
            < short&, long long&, char16_t&, char32_t&
            , unsigned short&, unsigned long long&
            >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 7 );
      auto& tup = variant_traits::get< 7 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &three );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &four );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &d );
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &u_three );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &u_four );
    }
  }

  return 0;
}

// TODO(mattcalabrese) Test squash with a top-level branching provider.

ARGOT_EXECUTE_TESTS();

}  // namespace
