/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/alternative_of.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_references.hpp>

#include <tuple>
#include <type_traits>

#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;

using argot::SameType;

using prov::alternative_of;
using prov::alternative_of_fn;

struct a {};
struct b {};
struct c {};

using generator_type = decltype( alternative_of );

ARGOT_CONCEPT_ENSURE
( SameType
  < generator_type
  , alternative_of_fn const
  >
);

ARGOT_REGISTER_CONSTEXPR_TEST( test_access_unary )
{
  using variant_type = std::variant< a >;

  variant_type var;
  variant_type const& const_var = var;

  auto provider_lvalue = alternative_of( var );
  auto provider_const_lvalue = alternative_of( const_var );
  auto provider_rvalue = alternative_of( std::move( var ) );

  // lvalue provision
  {
    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_lvalue
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< std::tuple< a& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &std::get< 0 >( var ) );
    }

    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_const_lvalue
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< std::tuple< a const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &std::get< 0 >( var ) );
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_rvalue
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< std::tuple< a& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &std::get< 0 >( var ) );
    }
  }

  // rvalue provision
  {
    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_lvalue )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< std::tuple< a& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &std::get< 0 >( var ) );
    }

    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_const_lvalue )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< std::tuple< a const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &std::get< 0 >( var ) );
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_rvalue )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant< std::tuple< a&& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &std::get< 0 >( var ) );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_access_ternary )
{
  using variant_type = std::variant< a, b, c >;

  variant_type var_a;
  variant_type const& const_var_a = var_a;
  variant_type var_b( std::in_place_index< 1 > );
  variant_type const& const_var_b = var_b;
  variant_type var_c( std::in_place_index< 2 > );
  variant_type const& const_var_c = var_c;

  auto provider_a_lvalue = alternative_of( var_a );
  auto provider_a_const_lvalue = alternative_of( const_var_a );
  auto provider_a_rvalue = alternative_of( std::move( var_a ) );
  auto provider_b_lvalue = alternative_of( var_b );
  auto provider_b_const_lvalue = alternative_of( const_var_b );
  auto provider_b_rvalue = alternative_of( std::move( var_b ) );
  auto provider_c_lvalue = alternative_of( var_c );
  auto provider_c_const_lvalue = alternative_of( const_var_c );
  auto provider_c_rvalue = alternative_of( std::move( var_c ) );

  // a
  {
    // lvalue provision
    {
      // lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_a_lvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 0 );
        auto& tup = std::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 0 >( var_a ) );
      }

      // const lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_a_const_lvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a const& >
            , std::tuple< b const& >
            , std::tuple< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 0 );
        auto& tup = std::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 0 >( var_a ) );
      }

      // rvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_a_rvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 0 );
        auto& tup = std::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 0 >( var_a ) );
      }
    }

    // rvalue provision
    {
      // lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_a_lvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 0 );
        auto& tup = std::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 0 >( var_a ) );
      }

      // const lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_a_const_lvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a const& >
            , std::tuple< b const& >
            , std::tuple< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 0 );
        auto& tup = std::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 0 >( var_a ) );
      }

      // rvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_a_rvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a&& >, std::tuple< b&& >, std::tuple< c&& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 0 );
        auto& tup = std::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 0 >( var_a ) );
      }
    }
  }

  // b
  {
    // lvalue provision
    {
      // lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_b_lvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 1 );
        auto& tup = std::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 1 >( var_b ) );
      }

      // const lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_b_const_lvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a const& >
            , std::tuple< b const& >
            , std::tuple< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 1 );
        auto& tup = std::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 1> ( var_b ) );
      }

      // rvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_b_rvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 1 );
        auto& tup = std::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 1 >( var_b ) );
      }
    }

    // rvalue provision
    {
      // lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_b_lvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 1 );
        auto& tup = std::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 1 >( var_b ) );
      }

      // const lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_b_const_lvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a const& >
            , std::tuple< b const& >
            , std::tuple< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 1 );
        auto& tup = std::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 1 >( var_b ) );
      }

      // rvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_b_rvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a&& >, std::tuple< b&& >, std::tuple< c&& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 1 );
        auto& tup = std::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 1 >( var_b ) );
      }
    }
  }

  // c
  {
    // lvalue provision
    {
      // lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_c_lvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 2 );
        auto& tup = std::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 2 >( var_c ) );
      }

      // const lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_c_const_lvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a const& >
            , std::tuple< b const& >
            , std::tuple< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 2 );
        auto& tup = std::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 2 >( var_c ) );
      }

      // rvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( provider_c_rvalue
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 2 );
        auto& tup = std::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 2 >( var_c ) );
      }
    }

    // rvalue provision
    {
      // lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_c_lvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a& >, std::tuple< b& >, std::tuple< c& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 2 );
        auto& tup = std::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 2 >( var_c ) );
      }

      // const lvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_c_const_lvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a const& >
            , std::tuple< b const& >
            , std::tuple< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 2 );
        auto& tup = std::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 2 >( var_c ) );
      }

      // rvalue
      {
        decltype( auto ) provision_result
          = prov_traits::provide
            ( std::move( provider_c_rvalue )
            , receiver::return_argument_references()
            );

        using provision_result_type
          = decltype( provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < provision_result_type
          , std::variant
            < std::tuple< a&& >, std::tuple< b&& >, std::tuple< c&& > >
          >
        );

        ARGOT_TEST_EQ( provision_result.index(), 2 );
        auto& tup = std::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &std::get< 0 >( tup ), &std::get< 2 >( var_c ) );
      }
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
