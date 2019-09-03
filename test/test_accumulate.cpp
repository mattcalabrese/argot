/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/accumulate.hpp>

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/receiver_traits/receive.hpp>

#include <utility>

namespace {

using argot::SameType;

using argot::accumulate_fn;
using argot::accumulate;

namespace receiver_traits = argot::receiver_traits;

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( accumulate )
  , accumulate_fn const
  >
);

struct a { int value = 1; };
struct b { int value = 10; };
struct c { int value = 100; };

struct prov_abc
{
};

} // namespace

namespace argot {

template<>
struct make_concept_map< ArgumentProvider< ::prov_abc > >
{
  template< class Receiver >
  static constexpr decltype( auto )
  provide( prov_abc self, Receiver&& receiver )
  {
    b b_;
    return receiver_traits::receive
    ( ARGOT_FORWARD( Receiver )( receiver )
    , a(), b_, c()
    );
  }
};

} // namespace argot

namespace {

constexpr auto add
  = []( auto& state, auto&& elem )
    {
      state += elem.value;
    };

ARGOT_REGISTER_CONSTEXPR_TEST( test_accumulate_no_args )
{
  {
    decltype( auto ) result
      = accumulate( add, 0 );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , int
      >
    );

    ARGOT_TEST_EQ( result, 0 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_accumulate_one_arg )
{
  // 1 provider, destructive
  {
    decltype( auto ) result
      = accumulate( add, 0, prov_abc() );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , int
      >
    );

    ARGOT_TEST_EQ( result, 111 );
  }

  // 1 provider, lvalue persistent
  {
    prov_abc prov_abc_var;

    decltype( auto ) result = accumulate( add, 0, prov_abc_var );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , int
      >
    );

    ARGOT_TEST_EQ( result, 111 );
  }

  // 1 provider, const lvalue persistent
  {
    prov_abc const prov_abc_var;

    decltype( auto ) result = accumulate( add, 0, prov_abc_var );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , int
      >
    );

    ARGOT_TEST_EQ( result, 111 );
  }

  // 1 provider, const rvalue persistent
  {
    prov_abc const prov_abc_var;

    decltype( auto ) result = accumulate( add, 0, std::move( prov_abc_var ) );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , int
      >
    );

    ARGOT_TEST_EQ( result, 111 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_accumulate_three_args )
{
  {
    prov_abc prov_abc_var0;
    prov_abc const prov_abc_var1;
    prov_abc prov_abc_var2;

    decltype( auto ) result
      = accumulate( add, 0
                  , std::move( prov_abc_var0 )
                  , prov_abc_var1
                  , std::move( prov_abc_var2 )
                  );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , int
      >
    );

    ARGOT_TEST_EQ( result, 333 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_accumulate_not_providers )
{
  // 3 providers, destructive, persistent, destructive
  {
    decltype( auto ) result
      = accumulate( add, 0
                  , a(), b(), c(), a()
                  );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , int
      >
    );

    ARGOT_TEST_EQ( result, 112 );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
