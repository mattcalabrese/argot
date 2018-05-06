/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/access_tuple.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_references.hpp>

#include <tuple>
#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;

using argot::SameType;

using prov::access_tuple;
using prov::access_tuple_fn;

struct a {};
struct b {};
struct c {};

using generator_type = decltype( access_tuple );

ARGOT_CONCEPT_ENSURE
( SameType
  < generator_type
  , access_tuple_fn const
  >
);

ARGOT_REGISTER_CONSTEXPR_TEST( test_access_unary )
{
  using tuple_type = std::tuple< a >;

  tuple_type var;
  tuple_type const& const_var = var;

  auto provider_lvalue = access_tuple( var, 0 );
  auto provider_const_lvalue = access_tuple( const_var, 0 );
  auto provider_rvalue = access_tuple( std::move( var ), 0 );

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
  using tuple_type = std::tuple< a, b, c >;

  tuple_type source_tup;
  tuple_type const& const_tup = source_tup;

  auto provider_a_lvalue = access_tuple( source_tup, 0 );
  auto provider_a_const_lvalue = access_tuple( const_tup, 0 );
  auto provider_a_rvalue = access_tuple( std::move( source_tup ), 0 );

  auto provider_b_lvalue = access_tuple( source_tup, 1 );
  auto provider_b_const_lvalue = access_tuple( const_tup, 1 );
  auto provider_b_rvalue = access_tuple( std::move( source_tup ), 1 );

  auto provider_c_lvalue = access_tuple( source_tup, 2 );
  auto provider_c_const_lvalue = access_tuple( const_tup, 2 );
  auto provider_c_rvalue = access_tuple( std::move( source_tup ), 2 );

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
        ( &std::get< 0 >( tup ), &std::get< 0 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 0 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 0 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 0 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 0 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 0 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 1 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 1> ( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 1 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 1 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 1 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 1 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 2 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 2 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 2 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 2 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 2 >( source_tup ) );
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
        ( &std::get< 0 >( tup ), &std::get< 2 >( source_tup ) );
      }
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
