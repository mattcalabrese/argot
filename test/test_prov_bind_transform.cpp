/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define ARGOT_NEW_CONSTEXPR_TEST

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/prov/bind_transform.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/receiver/return_argument_values.hpp>
#include <argot/receiver/return_single_argument_value.hpp>
#include <argot/receiver/return_argument_references.hpp>

#include <type_traits>
#include <utility>
#include <variant>

namespace {

enum class foo { zero, a, b, c };
enum class bar { zero, a, b, c };

enum class foo1 { zero, a, b, c };
enum class bar1 { zero, a, b, c };

enum class foo2 { zero, a, b, c };
enum class bar2 { zero, a, b, c };

enum class foo3 { zero, a, b, c };
enum class bar3 { zero, a, b, c };

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;

using argot::ArgumentProvider;
using argot::PersistentArgumentProvider;
using argot::SameType;
using prov::bind_transform;
using prov::conditional;
using prov::nothing;
using prov::nothing_t;
using prov::reference_to;
using prov::result_of_bind_transform;
using prov::result_of_bind_transform_t;
using prov::result_of_conditional_t;
using prov::result_of_reference_to_t;
using prov::result_of_value_of_t;
using prov::value_of;

struct lvalue_call_t {} constexpr lvalue_call{};
struct rvalue_call_t {} constexpr rvalue_call{};

struct tracked_forward_arguments_as_tuple_t
{
  template< class... P >
  constexpr result_of_conditional_t
  < bool&&
  , result_of_value_of_t< std::tuple< lvalue_call_t const&, P&&... > >
  , result_of_value_of_t< std::tuple< rvalue_call_t const&, P&&... > >
  >
  operator ()( P&&... args ) const&
  {
    return conditional
    ( true
    , value_of
      ( std::forward_as_tuple( lvalue_call, std::forward< P >( args )... ) )
    , value_of
      ( std::forward_as_tuple( rvalue_call, std::forward< P >( args )... ) )
    );
  }

  template< class... P >
  constexpr result_of_conditional_t
  < bool&&
  , result_of_value_of_t< std::tuple< lvalue_call_t const&, P&&... > >
  , result_of_value_of_t< std::tuple< rvalue_call_t const&, P&&... > >
  >
  operator ()( P&&... args ) &&
  {
    return conditional
    ( false
    , value_of
      ( std::forward_as_tuple( lvalue_call, std::forward< P >( args )... ) )
    , value_of
      ( std::forward_as_tuple( rvalue_call, std::forward< P >( args )... ) )
    );
  }
} constexpr tracked_forward_arguments_as_tuple{};

ARGOT_REGISTER_CONSTEXPR_TEST( test_bind_transform_nullary )
{
  int a = 1;
  double b = 2;

  decltype( auto ) provider
    = bind_transform( reference_to( std::move( a ), std::move( b ) ) );

  using result_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< result_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< result_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_bind_transform_t
      < result_of_reference_to_t< int&&, double&& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_bind_transform
      < result_of_reference_to_t< int&&, double&& > >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< int&&, double&& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &b );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , receiver::return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< int&, double& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &b );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonbranching_unary_bind_transform )
{
  foo foo_a = foo::a;
  bar bar_b = bar::b;

  decltype( auto ) provider
    = bind_transform
      ( reference_to( std::move( foo_a ), bar_b )
      , tracked_forward_arguments_as_tuple
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_bind_transform_t
      < prov::result_of_reference_to_t< foo&&, bar& >
      , tracked_forward_arguments_as_tuple_t const&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_bind_transform
      < prov::result_of_reference_to_t< foo&&, bar& >
      , tracked_forward_arguments_as_tuple_t const&
      >::type
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
      , std::variant
        < std::tuple< std::tuple< lvalue_call_t const&, foo&& >
                    , std::tuple< lvalue_call_t const&, bar& >
                    >
        , std::tuple< std::tuple< lvalue_call_t const&, foo&& >
                    , std::tuple< rvalue_call_t const&, bar& >
                    >
        , std::tuple< std::tuple< rvalue_call_t const&, foo&& >
                    , std::tuple< lvalue_call_t const&, bar& >
                    >
        , std::tuple< std::tuple< rvalue_call_t const&, foo&& >
                    , std::tuple< rvalue_call_t const&, bar& >
                    >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& top_tup = std::get< 0 >( provision_result );
    auto& tup0 = std::get< 0 >( top_tup );
    auto& tup1 = std::get< 1 >( top_tup );

    ARGOT_TEST_EQ( &std::get< 0 >( tup0 ), &lvalue_call );
    ARGOT_TEST_EQ( &std::get< 1 >( tup0 ), &foo_a );
    ARGOT_TEST_EQ( &std::get< 0 >( tup1 ), &lvalue_call );
    ARGOT_TEST_EQ( &std::get< 1 >( tup1 ), &bar_b );
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
        < std::tuple< std::tuple< lvalue_call_t const&, foo& >
                    , std::tuple< lvalue_call_t const&, bar& >
                    >
        , std::tuple< std::tuple< lvalue_call_t const&, foo& >
                    , std::tuple< rvalue_call_t const&, bar& >
                    >
        , std::tuple< std::tuple< rvalue_call_t const&, foo& >
                    , std::tuple< lvalue_call_t const&, bar& >
                    >
        , std::tuple< std::tuple< rvalue_call_t const&, foo& >
                    , std::tuple< rvalue_call_t const&, bar& >
                    >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& top_tup = std::get< 0 >( provision_result );
    auto& tup0 = std::get< 0 >( top_tup );
    auto& tup1 = std::get< 1 >( top_tup );

    ARGOT_TEST_EQ( &std::get< 0 >( tup0 ), &lvalue_call );
    ARGOT_TEST_EQ( &std::get< 1 >( tup0 ), &foo_a );
    ARGOT_TEST_EQ( &std::get< 0 >( tup1 ), &lvalue_call );
    ARGOT_TEST_EQ( &std::get< 1 >( tup1 ), &bar_b );
  }

  return 0;
}

#if 0

ARGOT_AUTO_CONSTEXPR_TEST( test_nonbranching_bind_transform )
{
  foo                foo_a = foo::a;
  foo const          const_foo_a = foo::a;

  bar                bar_a = bar::a;
  bar const          const_bar_a = bar::a;

  decltype( auto ) provider
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , reference_to( foo_a, std::move( foo_a ) )
      , reference_to( const_foo_a, std::move( const_foo_a ) )
      , reference_to( bar_a, std::move( bar_a ) )
      , reference_to( const_bar_a, std::move( const_bar_a ) )
      );

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_bind_transform_t
      < tracked_forward_arguments_as_tuple_t const&
      , prov::result_of_reference_to_t
        < foo&
        , foo&&
        >
      , prov::result_of_reference_to_t
        < foo const&
        , foo const&&
        >
      , prov::result_of_reference_to_t
        < bar&
        , bar&&
        >
      , prov::result_of_reference_to_t
        < bar const&
        , bar const&&
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_bind_transform
      < tracked_forward_arguments_as_tuple_t const&
      , prov::result_of_reference_to_t
        < foo&
        , foo&&
        >
      , prov::result_of_reference_to_t
        < foo const&
        , foo const&&
        >
      , prov::result_of_reference_to_t
        < bar&
        , bar&&
        >
      , prov::result_of_reference_to_t
        < bar const&
        , bar const&&
        >
      >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , receiver::return_single_argument_value()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < lvalue_call_t const&
          , foo&, foo&&, foo const&, foo const&&
          , bar&, bar&&, bar const&, bar const&&
          >
        , std::tuple
          < rvalue_call_t const&
          , foo&, foo&&, foo const&, foo const&&
          , bar&, bar&&, bar const&, bar const&&
          >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 1 );
    auto& tup = std::get< 1 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo_a );
    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo_a );
    ARGOT_TEST_EQ( &std::get< 3 >( tup ), &const_foo_a );
    ARGOT_TEST_EQ( &std::get< 4 >( tup ), &const_foo_a );
    ARGOT_TEST_EQ( &std::get< 5 >( tup ), &bar_a );
    ARGOT_TEST_EQ( &std::get< 6 >( tup ), &bar_a );
    ARGOT_TEST_EQ( &std::get< 7 >( tup ), &const_bar_a );
    ARGOT_TEST_EQ( &std::get< 8 >( tup ), &const_bar_a );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , receiver::return_single_argument_value()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < lvalue_call_t const&
          , foo&, foo&, foo const&, foo const&
          , bar&, bar&, bar const&, bar const&
          >
        , std::tuple
          < rvalue_call_t const&
          , foo&, foo&, foo const&, foo const&
          , bar&, bar&, bar const&, bar const&
          >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo_a );
    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo_a );
    ARGOT_TEST_EQ( &std::get< 3 >( tup ), &const_foo_a );
    ARGOT_TEST_EQ( &std::get< 4 >( tup ), &const_foo_a );
    ARGOT_TEST_EQ( &std::get< 5 >( tup ), &bar_a );
    ARGOT_TEST_EQ( &std::get< 6 >( tup ), &bar_a );
    ARGOT_TEST_EQ( &std::get< 7 >( tup ), &const_bar_a );
    ARGOT_TEST_EQ( &std::get< 8 >( tup ), &const_bar_a );
  }
};

ARGOT_AUTO_CONSTEXPR_TEST( test_branching_unary_bind_transform )
{
  foo foo_a = foo::a;
  bar bar_b = bar::b;

  decltype( auto ) provider_foo_a
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( true
        , reference_to( std::move( foo_a ) )
        , reference_to( bar_b )
        )
      );

  decltype( auto ) provider_bar_b
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( false
        , reference_to( std::move( foo_a ) )
        , reference_to( bar_b )
        )
      );

  using provider_type = decltype( provider_foo_a );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_bind_transform_t
      < tracked_forward_arguments_as_tuple_t const&
      , result_of_conditional_t
        < bool
        , prov::result_of_reference_to_t< foo&& >
        , prov::result_of_reference_to_t< bar& >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_bind_transform
      < tracked_forward_arguments_as_tuple_t const&
      , result_of_conditional_t
        < bool
        , prov::result_of_reference_to_t< foo&& >
        , prov::result_of_reference_to_t< bar& >
        >
      >::type
    >
  );

  // rvalue provision
  {
    // foo branch
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_foo_a )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo&& >
          , std::tuple< rvalue_call_t const&, foo&& >
          , std::tuple< lvalue_call_t const&, bar& >
          , std::tuple< rvalue_call_t const&, bar& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo_a );
    }

    // bar branch
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_bar_b )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo&& >
          , std::tuple< rvalue_call_t const&, foo&& >
          , std::tuple< lvalue_call_t const&, bar& >
          , std::tuple< rvalue_call_t const&, bar& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
      auto& tup = std::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar_b );
    }
  }

  // lvalue provision
  {
    // foo branch
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_foo_a
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo& >
          , std::tuple< rvalue_call_t const&, foo& >
          , std::tuple< lvalue_call_t const&, bar& >
          , std::tuple< rvalue_call_t const&, bar& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo_a );
    }

    // bar branch
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_bar_b
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo& >
          , std::tuple< rvalue_call_t const&, foo& >
          , std::tuple< lvalue_call_t const&, bar& >
          , std::tuple< rvalue_call_t const&, bar& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar_b );
    }
  }
};

// TODO(mattcalabrese) Uncomment these

ARGOT_AUTO_CONSTEXPR_TEST( test_branching_ternary_bind_transform )
{
  foo1 foo1_a = foo1::a;
  bar1 bar1_b = bar1::b;

  foo2 foo2_a = foo2::a;
  bar2 bar2_b = bar2::b;

  foo3 foo3_a = foo3::a;
  bar3 bar3_b = bar3::b;

  decltype( auto ) provider_a_a_a
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( true
        , reference_to( std::move( foo1_a ) )
        , reference_to( bar1_b )
        )
      , conditional
        ( true
        , reference_to( std::move( foo2_a ) )
        , reference_to( bar2_b )
        )
      , conditional
        ( true
        , reference_to( std::move( foo3_a ) )
        , reference_to( bar3_b )
        )
      );

  decltype( auto ) provider_a_a_b
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( true
        , reference_to( std::move( foo1_a ) )
        , reference_to( bar1_b )
        )
      , conditional
        ( true
        , reference_to( std::move( foo2_a ) )
        , reference_to( bar2_b )
        )
      , conditional
        ( false
        , reference_to( std::move( foo3_a ) )
        , reference_to( bar3_b )
        )
      );

  decltype( auto ) provider_a_b_a
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( true
        , reference_to( std::move( foo1_a ) )
        , reference_to( bar1_b )
        )
      , conditional
        ( false
        , reference_to( std::move( foo2_a ) )
        , reference_to( bar2_b )
        )
      , conditional
        ( true
        , reference_to( std::move( foo3_a ) )
        , reference_to( bar3_b )
        )
      );

  decltype( auto ) provider_a_b_b
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( true
        , reference_to( std::move( foo1_a ) )
        , reference_to( bar1_b )
        )
      , conditional
        ( false
        , reference_to( std::move( foo2_a ) )
        , reference_to( bar2_b )
        )
      , conditional
        ( false
        , reference_to( std::move( foo3_a ) )
        , reference_to( bar3_b )
        )
      );

  decltype( auto ) provider_b_a_a
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( false
        , reference_to( std::move( foo1_a ) )
        , reference_to( bar1_b )
        )
      , conditional
        ( true
        , reference_to( std::move( foo2_a ) )
        , reference_to( bar2_b )
        )
      , conditional
        ( true
        , reference_to( std::move( foo3_a ) )
        , reference_to( bar3_b )
        )
      );

  decltype( auto ) provider_b_a_b
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( false
        , reference_to( std::move( foo1_a ) )
        , reference_to( bar1_b )
        )
      , conditional
        ( true
        , reference_to( std::move( foo2_a ) )
        , reference_to( bar2_b )
        )
      , conditional
        ( false
        , reference_to( std::move( foo3_a ) )
        , reference_to( bar3_b )
        )
      );

  decltype( auto ) provider_b_b_a
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( false
        , reference_to( std::move( foo1_a ) )
        , reference_to( bar1_b )
        )
      , conditional
        ( false
        , reference_to( std::move( foo2_a ) )
        , reference_to( bar2_b )
        )
      , conditional
        ( true
        , reference_to( std::move( foo3_a ) )
        , reference_to( bar3_b )
        )
      );

  decltype( auto ) provider_b_b_b
    = bind_transform
      ( tracked_forward_arguments_as_tuple
      , conditional
        ( false
        , reference_to( std::move( foo1_a ) )
        , reference_to( bar1_b )
        )
      , conditional
        ( false
        , reference_to( std::move( foo2_a ) )
        , reference_to( bar2_b )
        )
      , conditional
        ( false
        , reference_to( std::move( foo3_a ) )
        , reference_to( bar3_b )
        )
      );


  using provider_type = decltype( provider_a_a_a );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_bind_transform_t
      < tracked_forward_arguments_as_tuple_t const&
      , result_of_conditional_t
        < bool
        , prov::result_of_reference_to_t< foo1&& >
        , prov::result_of_reference_to_t< bar1& >
        >
      , result_of_conditional_t
        < bool
        , prov::result_of_reference_to_t< foo2&& >
        , prov::result_of_reference_to_t< bar2& >
        >
      , result_of_conditional_t
        < bool
        , prov::result_of_reference_to_t< foo3&& >
        , prov::result_of_reference_to_t< bar3& >
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_bind_transform
      < tracked_forward_arguments_as_tuple_t const&
      , result_of_conditional_t
        < bool
        , prov::result_of_reference_to_t< foo1&& >
        , prov::result_of_reference_to_t< bar1& >
        >
      , result_of_conditional_t
        < bool
        , prov::result_of_reference_to_t< foo2&& >
        , prov::result_of_reference_to_t< bar2& >
        >
      , result_of_conditional_t
        < bool
        , prov::result_of_reference_to_t< foo3&& >
        , prov::result_of_reference_to_t< bar3& >
        >
      >::type
    >
  );

  // rvalue provision
  {
    // branch0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_a_a_a )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo1_a );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo2_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &foo3_a );
    }

    // branch1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_a_a_b )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
      auto& tup = std::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo1_a );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo2_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &bar3_b );
    }

    // branch2
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_a_b_a )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 5 );
      auto& tup = std::get< 5 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo1_a );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bar2_b );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &foo3_a );
    }

    // branch3
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_a_b_b )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 7 );
      auto& tup = std::get< 7 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo1_a );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bar2_b );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &bar3_b );
    }

    // branch4
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_b_a_a )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(),9 );
      auto& tup = std::get< 9 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo2_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &foo3_a );
    }

    // branch5
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_b_a_b )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 11 );
      auto& tup = std::get< 11 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo2_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &bar3_b );
    }

    // branch6
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_b_b_a )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 13 );
      auto& tup = std::get< 13 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bar2_b );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &foo3_a );
    }

    // branch7
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_b_b_b )
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3&& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 15 );
      auto& tup = std::get< 15 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &rvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bar2_b );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &bar3_b );
    }
  }

  // lvalue provision
  {
    // branch0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_a_a_a
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo1_a );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo2_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &foo3_a );
    }

    // branch1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_a_a_b
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo1_a );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo2_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &bar3_b );
    }

    // branch2
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_a_b_a
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 4 );
      auto& tup = std::get< 4 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo1_a );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bar2_b );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &foo3_a );
    }

    // branch3
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_a_b_b
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 6 );
      auto& tup = std::get< 6 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &foo1_a );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bar2_b );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &bar3_b );
    }

    // branch4
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_b_a_a
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 8 );
      auto& tup = std::get< 8 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo2_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &foo3_a );
    }

    // branch5
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_b_a_b
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 10 );
      auto& tup = std::get< 10 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &foo2_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &bar3_b );
    }

    // branch6
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_b_b_a
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 12 );
      auto& tup = std::get< 12 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bar2_b );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &foo3_a );
    }

    // branch7
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_b_b_b
          , receiver::return_single_argument_value()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple< lvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, foo1&, bar2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, foo2&, bar3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, foo3& >
          , std::tuple< lvalue_call_t const&, bar1&, bar2&, bar3& >
          , std::tuple< rvalue_call_t const&, bar1&, bar2&, bar3& >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 14 );
      auto& tup = std::get< 14 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ), &lvalue_call );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ), &bar2_b );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ), &bar3_b );
    }
  }
};

#endif

ARGOT_EXECUTE_TESTS();

}  // namespace
