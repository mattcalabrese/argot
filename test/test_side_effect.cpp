/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/side_effect.hpp>

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/receiver_traits/receive.hpp>

#include <utility>

namespace {

using argot::SameType;

using argot::side_effect_fn;
using argot::side_effect;
using argot::result_of_side_effect;
using argot::result_of_side_effect_t;

namespace receiver_traits = argot::receiver_traits;

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( side_effect )
  , side_effect_fn const
  >
);

enum class provision_kind { not_called, destructive, persistent };

struct a {};
struct b {};
struct c {};

struct set_kind
{
  provision_kind& target; 
};

} // namespace

namespace argot {

template<>
struct make_concept_map< ArgumentProvider< ::set_kind > >
{
  template< class Receiver >
  static constexpr decltype( auto )
  provide( set_kind self, Receiver&& receiver )
  {
    self.target = provision_kind::destructive;

    b b_;
    return receiver_traits::receive
    ( ARGOT_FORWARD( Receiver )( receiver )
    , a(), b_, c()
    );
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< ::set_kind > >
{
  template< class Receiver >
  static constexpr decltype( auto )
  provide( set_kind self, Receiver&& receiver )
  {
    self.target = provision_kind::persistent;

    b b_;
    return receiver_traits::receive
    ( ARGOT_FORWARD( Receiver )( receiver )
    , a(), b_, c()
    );
  }
};

} // namespace argot

namespace {

ARGOT_REGISTER_CONSTEXPR_TEST( test_side_effect_no_args )
{
  {
    side_effect();

    using result_type = decltype( side_effect() );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect_t<>
      , void
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect<>::type
      , void
      >
    );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_side_effect_one_arg )
{
  // 1 provider, destructive
  {
    provision_kind side_effect_state = provision_kind::not_called;

    side_effect( set_kind{ side_effect_state } );

    using result_type
      = decltype( side_effect( set_kind{ side_effect_state } ) );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );

    ARGOT_TEST_EQ( side_effect_state, provision_kind::destructive );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect_t< set_kind >
      , void
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect< set_kind >::type
      , void
      >
    );
  }

  // 1 provider, lvalue persistent
  {
    provision_kind side_effect_state = provision_kind::not_called;
    set_kind set_kind_var{ side_effect_state };

    side_effect( set_kind_var );

    using result_type = decltype( side_effect( set_kind_var ) );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );

    ARGOT_TEST_EQ( side_effect_state, provision_kind::persistent );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect_t< set_kind& >
      , void
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect< set_kind& >::type
      , void
      >
    );
  }

  // 1 provider, const lvalue persistent
  {
    provision_kind side_effect_state = provision_kind::not_called;
    set_kind const set_kind_var{ side_effect_state };

    side_effect( set_kind_var );

    using result_type = decltype( side_effect( set_kind_var ) );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );

    ARGOT_TEST_EQ( side_effect_state, provision_kind::persistent );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect_t< set_kind const& >
      , void
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect< set_kind const& >::type
      , void
      >
    );
  }

  // 1 provider, const rvalue persistent
  {
    provision_kind side_effect_state = provision_kind::not_called;
    set_kind const set_kind_var{ side_effect_state };

    side_effect( std::move( set_kind_var ) );

    using result_type = decltype( side_effect( std::move( set_kind_var ) ) );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );

    ARGOT_TEST_EQ( side_effect_state, provision_kind::persistent );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect_t< set_kind const&& >
      , void
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect< set_kind const&& >::type
      , void
      >
    );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_side_effect_three_args )
{
  // 3 providers, destructive, persistent, destructive
  {
    provision_kind side_effect_state0 = provision_kind::not_called;
    provision_kind side_effect_state1 = provision_kind::not_called;
    provision_kind side_effect_state2 = provision_kind::not_called;

    set_kind set_kind_var0{ side_effect_state0 };
    set_kind const set_kind_var1{ side_effect_state1 };
    set_kind set_kind_var2{ side_effect_state2 };

    side_effect( std::move( set_kind_var0 )
               , set_kind_var1
               , std::move( set_kind_var2 )
               );

    using result_type
      = decltype
        ( side_effect
          ( std::move( set_kind_var0 )
          , set_kind_var1
          , std::move( set_kind_var2 )
          )
        );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );

    ARGOT_TEST_EQ( side_effect_state0, provision_kind::destructive );
    ARGOT_TEST_EQ( side_effect_state1, provision_kind::persistent );
    ARGOT_TEST_EQ( side_effect_state2, provision_kind::destructive );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect_t< set_kind&&, set_kind&, set_kind&& >
      , void
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_side_effect< set_kind&&, set_kind&, set_kind&& >
        ::type
      , void
      >
    );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
