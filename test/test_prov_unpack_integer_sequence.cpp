/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/unpack_integer_sequence.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_values.hpp>

#include <tuple>
#include <type_traits>
#include <variant>

#include <cstddef>
#include <type_traits>

namespace {

using argot::SameType;

// TODO(mattcalabrese) Test more cases
ARGOT_REGISTER_CONSTEXPR_TEST( test_provision )
{
  namespace prov = argot::prov;
  namespace prov_traits = argot::prov_traits;
  namespace receiver = argot::receiver;

  {
    using function_object_type
      = decltype( prov::unpack_integer_sequence );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < function_object_type
      , prov::unpack_integer_sequence_fn const
      >
    );
  }

  using integer_sequence_type = std::make_index_sequence< 3 >;

  decltype( auto ) provider
    = prov::unpack_integer_sequence( integer_sequence_type{} );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_unpack_integer_sequence_t
      < integer_sequence_type >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_unpack_integer_sequence
      < integer_sequence_type >::type
    >
  );

  // rvalue provision
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
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
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
        ( std::move( provider )
        , receiver::return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < std::integral_constant< std::size_t, 0 >
          , std::integral_constant< std::size_t, 1 >
          , std::integral_constant< std::size_t, 2 >
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
