/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/access_union.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/variant_traits/get.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <tuple>
#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace tuple_traits = argot::tuple_traits;
namespace variant_traits = argot::variant_traits;

using argot::SameType;

using argot::discriminated_union;
using prov::access_union;
using prov::access_union_fn;

struct a {};
struct b {};
struct c {};

using generator_type = decltype( access_union );

ARGOT_CONCEPT_ENSURE
( SameType
  < generator_type
  , access_union_fn const
  >
);

ARGOT_REGISTER_CONSTEXPR_TEST( test_access_unary )
{
  using union_type = std::variant< a >;

  union_type var;
  union_type const& const_var = var;

  auto provider_lvalue = access_union( var, 0 );
  auto provider_const_lvalue = access_union( const_var, 0 );
  auto provider_rvalue = access_union( std::move( var ), 0 );

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
        , discriminated_union< argot::struct_< a& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var ) );
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
        , discriminated_union< argot::struct_< a const& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var ) );
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
        , discriminated_union< argot::struct_< a& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var ) );
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
        , discriminated_union< argot::struct_< a& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var ) );
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
        , discriminated_union< argot::struct_< a const& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var ) );
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
        , discriminated_union< argot::struct_< a&& > >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
      auto& tup = variant_traits::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var ) );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_access_ternary )
{
  using union_type = std::variant< a, b, c >;

  union_type var_a;
  union_type const& const_var_a = var_a;
  union_type var_b( std::in_place_index< 1 > );
  union_type const& const_var_b = var_b;
  union_type var_c( std::in_place_index< 2 > );
  union_type const& const_var_c = var_c;

  auto provider_a_lvalue = access_union( var_a, 0 );
  auto provider_a_const_lvalue = access_union( const_var_a, 0 );
  auto provider_a_rvalue = access_union( std::move( var_a ), 0 );
  auto provider_b_lvalue = access_union( var_b, 1 );
  auto provider_b_const_lvalue = access_union( const_var_b, 1 );
  auto provider_b_rvalue = access_union( std::move( var_b ), 1 );
  auto provider_c_lvalue = access_union( var_c, 2 );
  auto provider_c_const_lvalue = access_union( const_var_c, 2 );
  auto provider_c_rvalue = access_union( std::move( var_c ), 2 );

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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
        auto& tup = variant_traits::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var_a ) );
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
          , discriminated_union
            < argot::struct_< a const& >
            , argot::struct_< b const& >
            , argot::struct_< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
        auto& tup = variant_traits::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var_a ) );
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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
        auto& tup = variant_traits::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var_a ) );
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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
        auto& tup = variant_traits::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var_a ) );
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
          , discriminated_union
            < argot::struct_< a const& >
            , argot::struct_< b const& >
            , argot::struct_< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
        auto& tup = variant_traits::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var_a ) );
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
          , discriminated_union
            < argot::struct_< a&& >, argot::struct_< b&& >, argot::struct_< c&& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
        auto& tup = variant_traits::get< 0 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 0 >( var_a ) );
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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
        auto& tup = variant_traits::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 1 >( var_b ) );
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
          , discriminated_union
            < argot::struct_< a const& >
            , argot::struct_< b const& >
            , argot::struct_< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
        auto& tup = variant_traits::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 1> ( var_b ) );
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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
        auto& tup = variant_traits::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 1 >( var_b ) );
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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
        auto& tup = variant_traits::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 1 >( var_b ) );
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
          , discriminated_union
            < argot::struct_< a const& >
            , argot::struct_< b const& >
            , argot::struct_< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
        auto& tup = variant_traits::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 1 >( var_b ) );
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
          , discriminated_union
            < argot::struct_< a&& >, argot::struct_< b&& >, argot::struct_< c&& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
        auto& tup = variant_traits::get< 1 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 1 >( var_b ) );
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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
        auto& tup = variant_traits::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 2 >( var_c ) );
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
          , discriminated_union
            < argot::struct_< a const& >
            , argot::struct_< b const& >
            , argot::struct_< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
        auto& tup = variant_traits::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 2 >( var_c ) );
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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
        auto& tup = variant_traits::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 2 >( var_c ) );
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
          , discriminated_union
            < argot::struct_< a& >, argot::struct_< b& >, argot::struct_< c& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
        auto& tup = variant_traits::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 2 >( var_c ) );
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
          , discriminated_union
            < argot::struct_< a const& >
            , argot::struct_< b const& >
            , argot::struct_< c const& >
            >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
        auto& tup = variant_traits::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 2 >( var_c ) );
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
          , discriminated_union
            < argot::struct_< a&& >, argot::struct_< b&& >, argot::struct_< c&& > >
          >
        );

        ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
        auto& tup = variant_traits::get< 2 >( provision_result );

        ARGOT_TEST_EQ
        ( &tuple_traits::get< 0 >( tup ), &variant_traits::get< 2 >( var_c ) );
      }
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
