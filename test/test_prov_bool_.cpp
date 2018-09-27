/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/bool_.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_single_argument_value.hpp>

#include <tuple>
#include <type_traits>
#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;

using argot::SameType;

ARGOT_REGISTER_CONSTEXPR_TEST( test_integral_constant_false )
{
  decltype( auto ) provider
    = prov::bool_( std::integral_constant< bool, false >{} );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_bool_t< std::integral_constant< bool, false > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_bool_< std::integral_constant< bool, false > >::type
    >
  );

  // lvalue
  {
    decltype( auto ) args
      = prov_traits::provide
        ( provider
        , receiver::return_single_argument_value()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant< std::integral_constant< bool, false > >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  // rvalue
  {
    decltype( auto ) args
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_single_argument_value()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant< std::integral_constant< bool, false > >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_integral_constant_true )
{
  decltype( auto ) provider
    = prov::bool_( std::integral_constant< bool, true >{} );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_bool_t< std::integral_constant< bool, true > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_bool_< std::integral_constant< bool, true > >::type
    >
  );

  // lvalue
  {
    decltype( auto ) args
      = prov_traits::provide
        ( provider
        , receiver::return_single_argument_value()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant< std::integral_constant< bool, true > >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  // rvalue
  {
    decltype( auto ) args
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_single_argument_value()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant< std::integral_constant< bool, true > >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_false )
{
  decltype( auto ) provider = prov::bool_( false );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_bool_t< bool >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_bool_< bool >::type
    >
  );

  // lvalue
  {
    decltype( auto ) args
      = prov_traits::provide
        ( provider
        , receiver::return_single_argument_value()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant
        < std::integral_constant< bool, false >
        , std::integral_constant< bool, true >
        >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  // rvalue
  {
    decltype( auto ) args
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_single_argument_value()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant
        < std::integral_constant< bool, false >
        , std::integral_constant< bool, true >
        >
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_true )
{
  decltype( auto ) provider = prov::bool_( true );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_bool_t< bool >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , prov::result_of_bool_< bool >::type
    >
  );

  // lvalue
  {
    decltype( auto ) args
      = prov_traits::provide
        ( provider
        , receiver::return_single_argument_value()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant
        < std::integral_constant< bool, false >
        , std::integral_constant< bool, true >
        >
      >
    );

    ARGOT_TEST_EQ( args.index(), 1 );
  }

  // rvalue
  {
    decltype( auto ) args
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_single_argument_value()
        );

    using args_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < args_type
      , std::variant
        < std::integral_constant< bool, false >
        , std::integral_constant< bool, true >
        >
      >
    );

    ARGOT_TEST_EQ( args.index(), 1 );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
