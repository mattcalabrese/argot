/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/variant_indices.hpp>
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

using prov::variant_indices;
using prov::variant_indices_t;

// TODO(mattcalabrese) Make sure the proper index_type is used for weird tuples

// TODO(mattcalabrese) Check that the same argument provider type is used for
//                     tuples of the size and index type, but with different
//                     element types.
//                     Spec wouldn't require it, but this is an optimization.

ARGOT_REGISTER_CONSTEXPR_TEST( test_nullary_variant_indices )
{
  using variant_type = std::variant<>;

  {
    using provider_object_type = decltype( variant_indices< variant_type > );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provider_object_type
      , variant_indices_t< variant_type > const
      >
    );
  }

  auto provider = variant_indices< variant_type >;

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, variant_indices_t< variant_type > > );

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
      , std::variant< argot::struct_<> >
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
      , std::variant< argot::struct_<> >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_ternary_variant_indices )
{

  using variant_type = std::variant< int, float, double >;

  {
    using provider_object_type = decltype( variant_indices< variant_type > );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provider_object_type
      , variant_indices_t< variant_type > const
      >
    );
  }

  auto provider = variant_indices< variant_type >;

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType< provider_type, variant_indices_t< variant_type > > );

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
        < argot::struct_
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
        ( provider
        , receiver::return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < argot::struct_
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
