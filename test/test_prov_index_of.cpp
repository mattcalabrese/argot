/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/index_of.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_single_argument_value.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <cstddef>
#include <type_traits>
#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace variant_traits = argot::variant_traits;

using argot::SameType;

using argot::discriminated_union;
using prov::index_of;
using prov::index_of_fn;

using generator_type = decltype( index_of );

ARGOT_CONCEPT_ENSURE
( SameType
  < generator_type
  , index_of_fn const
  >
);

ARGOT_REGISTER_CONSTEXPR_TEST( test_basic )
{
  using variant_type = std::variant<char, short, int, long, char>;

  variant_type const v0( std::in_place_index< 0 > );
  variant_type const v1( std::in_place_index< 1 > );
  variant_type const v2( std::in_place_index< 2 > );
  variant_type const v3( std::in_place_index< 3 > );
  variant_type const v4( std::in_place_index< 4 > );

  auto provider_0 = index_of( v0 );
  auto provider_1 = index_of( v1 );
  auto provider_2 = index_of( v2 );
  auto provider_3 = index_of( v3 );
  auto provider_4 = index_of( v4 );

  // 0
  {
    // rvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_0 )
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
    }

    // lvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_0
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 0 );
    }
  }

  // 1
  {
    // rvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_1 )
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
    }

    // lvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_1
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 1 );
    }
  }

  // 2
  {
    // rvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_2 )
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
    }

    // lvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_2
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 2 );
    }
  }

  // 3
  {
    // rvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_3 )
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 3 );
    }

    // lvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_3
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 3 );
    }
  }

  // 4
  {
    // rvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_4 )
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 4 );
    }

    // lvalue provision
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_4
          , receiver::return_single_argument_value()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , discriminated_union
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( variant_traits::index_of( provision_result ), 4 );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
