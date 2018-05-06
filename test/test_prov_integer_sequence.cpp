/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/integer_sequence.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_values.hpp>

#include <tuple>
#include <type_traits>
#include <variant>

#include <cstddef>
#include <type_traits>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;

using argot::SameType;

using prov::integer_sequence;
using prov::integer_sequence_t;

// TODO(mattcalabrese) Test that it yields prov::nothing if value is 0.
//                     This is just an optimization and not required.

ARGOT_REGISTER_CONSTEXPR_TEST( test_nullary_integer_sequence )
{
  short constexpr size = 0;

  {
    using provider_object_type = decltype( integer_sequence< size > );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provider_object_type
      , integer_sequence_t< size > const
      >
    );
  }

  auto provider = integer_sequence< size >;

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, integer_sequence_t< size > > );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple<> >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , receiver::return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple<> >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonzero_integer_sequence )
{
  short constexpr size = 7;

  {
    using provider_object_type = decltype( integer_sequence< size > );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provider_object_type
      , integer_sequence_t< size > const
      >
    );
  }

  auto provider = integer_sequence< size >;

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, integer_sequence_t< size > > );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < std::integral_constant< short, 0 >
          , std::integral_constant< short, 1 >
          , std::integral_constant< short, 2 >
          , std::integral_constant< short, 3 >
          , std::integral_constant< short, 4 >
          , std::integral_constant< short, 5 >
          , std::integral_constant< short, 6 >
          >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , receiver::return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < std::integral_constant< short, 0 >
          , std::integral_constant< short, 1 >
          , std::integral_constant< short, 2 >
          , std::integral_constant< short, 3 >
          , std::integral_constant< short, 4 >
          , std::integral_constant< short, 5 >
          , std::integral_constant< short, 6 >
          >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
