/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/tuple_index.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_single_argument_value.hpp>
#include <argot/tuple_traits/index_type.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace tuple_traits = argot::tuple_traits;
namespace variant_traits = argot::variant_traits;

using argot::SameType;

using argot::discriminated_union;
using prov::tuple_index;
using prov::tuple_index_fn;

// TODO(mattcalabrese) Test non-dynamic and test defaults
ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic )
{
  using tuple_type = std::tuple<char, short, int, long, long long>;

  using object_type
    = decltype( tuple_index< tuple_type > );

  auto constexpr object = tuple_index< tuple_type >;

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < object_type
    , tuple_index_fn< tuple_type > const
    >
  );

  using index_type_t = tuple_traits::index_type_t< tuple_type >;

  auto provider_0 = object( index_type_t{ 0 } );
  auto provider_1 = object( index_type_t{ 1 } );
  auto provider_2 = object( index_type_t{ 2 } );
  auto provider_3 = object( index_type_t{ 3 } );
  auto provider_4 = object( index_type_t{ 4 } );

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
