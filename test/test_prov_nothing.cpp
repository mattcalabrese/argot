/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_values.hpp>

#include <tuple>
#include <type_traits>
#include <variant>

// TODO(mattcalabrese) Test SFINAE

namespace {

using argot::SameType;

ARGOT_REGISTER_CONSTEXPR_TEST( test_provision )
{
  namespace prov = argot::prov;
  namespace prov_traits = argot::prov_traits;
  namespace receiver = argot::receiver;

  {
    using nothing_type = decltype( prov::nothing );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < nothing_type
      , prov::nothing_t const
      >
    );
  }

  auto provider = prov::nothing;

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::nothing_t
    >
  );

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

ARGOT_EXECUTE_TESTS();

}  // namespace
