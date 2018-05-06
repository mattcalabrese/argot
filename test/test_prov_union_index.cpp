/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/union_index.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/union_traits/index_type.hpp>
#include <argot/receiver/return_single_argument_value.hpp>

#include <cstddef>
#include <type_traits>
#include <variant>

namespace {

using argot::SameType;

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace union_traits = argot::union_traits;
namespace receiver = argot::receiver;

using prov::union_index;
using prov::union_index_fn;

// TODO(mattcalabrese) Test non-dynamic and test defaults
ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic )
{
  using union_type = std::variant<char, short, int, long, long long>;
  using index_type = union_traits::index_type_t< union_type >;

  using object_type = decltype( union_index< union_type > );

  auto constexpr object = union_index< union_type >;

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < object_type
    , union_index_fn< union_type > const
    >
  );

  auto provider_0 = object( index_type{ 0 } );
  auto provider_1 = object( index_type{ 1 } );
  auto provider_2 = object( index_type{ 2 } );
  auto provider_3 = object( index_type{ 3 } );
  auto provider_4 = object( index_type{ 4 } );

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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 4 );
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
        , std::variant
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
          , std::integral_constant< std::size_t, 3 >
          , std::integral_constant< std::size_t, 4 >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 4 );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
