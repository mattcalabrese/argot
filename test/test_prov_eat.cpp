/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/eat.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_values.hpp>

#include <tuple>
#include <type_traits>
#include <variant>

namespace {

using argot::SameType;

ARGOT_REGISTER_CONSTEXPR_TEST( test_nullary )
{
  namespace prov = argot::prov;
  namespace prov_traits = argot::prov_traits;
  namespace receiver = argot::receiver;

  {
    using eat_type = decltype( prov::eat );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < eat_type
      , prov::eat_fn const
      >
    );
  }

  decltype( auto ) provider = prov::eat();

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_eat_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_eat<>::type
    >
  );

  // TODO(mattcalabrese) Move to different file (not required equality)
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

ARGOT_REGISTER_CONSTEXPR_TEST( test_nary )
{
  namespace prov = argot::prov;
  namespace prov_traits = argot::prov_traits;
  namespace receiver = argot::receiver;

  decltype( auto ) provider = prov::eat( 1, '2', 3. );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_eat_t< int, char, double >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_eat< int, char, double >::type
    >
  );

  // TODO(mattcalabrese) Move to different file (not required equality)
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
