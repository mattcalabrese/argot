/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/prov/lift_transform.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/receiver/return_argument_values.hpp>

#include <type_traits>
#include <utility>
#include <variant>

// TODO(mattcalabrese) If the provider only represents a single value, then the
//                     transformation should be executed as an rvalue.

namespace {

enum class foo1 { zero, a, b, c };
enum class bar1 { zero, a, b, c };

enum class foo2 { zero, a, b, c };
enum class bar2 { zero, a, b, c };

enum class foo3 { zero, a, b, c };
enum class bar3 { zero, a, b, c };

enum class foo4 { zero, a, b, c };
enum class bar4 { zero, a, b, c };

class tag1;
class tag2;
class tag3;

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;

using argot::SameType;

using prov::conditional;
using prov::group;
using prov::lift_transform;
using prov::reference_to;
using prov::result_of_conditional_t;
using prov::result_of_group_t;
using prov::result_of_lift_transform;
using prov::result_of_lift_transform_t;
using prov::result_of_reference_to_t;
using receiver::return_argument_references;
using receiver::return_argument_values;

template< class T, class... Tags >
struct wrapped_t
{
  static_assert( std::is_reference_v< T > );

  constexpr wrapped_t( T&& ref ) noexcept : ref( std::forward< T >( ref ) ) {}
  wrapped_t(wrapped_t&&) = default;
  wrapped_t& operator=(wrapped_t&&) = default;

  T&& ref;
};

template< class Tag >
struct wrap
{
  template< class T, class... OldTags >
  constexpr wrapped_t< T, OldTags..., Tag > operator ()
  ( wrapped_t< T, OldTags... > arg ) & = delete;

  template< class T >
  constexpr wrapped_t< T&&, Tag > operator ()( T&& arg ) & = delete;

  template< class T, class... OldTags >
  constexpr wrapped_t< T, OldTags..., Tag > operator ()
  ( wrapped_t< T, OldTags... > arg ) const&
  {
    return { std::forward< T >( arg.ref ) };
  }

  template< class T >
  constexpr wrapped_t< T&&, Tag > operator ()( T&& arg ) const&
  {
    return { std::forward< T >( arg ) };
  }
};

ARGOT_REGISTER_CONSTEXPR_TEST( test_lift_transform_nullary )
{
  foo1 foo_a = foo1::a;
  bar1 bar_b = bar1::b;

  decltype( auto ) provider
    = lift_transform( prov::reference_to( std::move( foo_a ), bar_b ) );

  using result_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform_t< result_of_reference_to_t< foo1&&, bar1& > >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform
      < result_of_reference_to_t< foo1&&, bar1& > >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< foo1&&, bar1& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &foo_a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar_b );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , return_argument_references()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant< std::tuple< foo1&, bar1& > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &foo_a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &bar_b );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_lift_transform_nonbranching )
{
  foo1 foo_a = foo1::a;
  bar1 bar_b = bar1::b;

  decltype( auto ) provider
    = lift_transform
      ( reference_to( std::move( foo_a ), bar_b )
      , wrap< tag1 >()
      );

  using result_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform_t
      < result_of_reference_to_t< foo1&&, bar1& >
      , wrap< tag1 >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform
      < result_of_reference_to_t< foo1&&, bar1& >
      , wrap< tag1 >
      >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple< wrapped_t< foo1&&, tag1 >, wrapped_t< bar1&, tag1 > > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo_a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar_b );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple< wrapped_t< foo1&, tag1 >, wrapped_t< bar1&, tag1 > > >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo_a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar_b );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_lift_transform_nonbranching_binary )
{
  foo1 foo_a = foo1::a;
  bar1 bar_b = bar1::b;

  decltype( auto ) provider
    = lift_transform
      ( reference_to( std::move( foo_a ), bar_b )
      , wrap< tag1 >(), wrap< tag2 >()
      );

  using result_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform_t
      < result_of_reference_to_t< foo1&&, bar1& >
      , wrap< tag1 >, wrap< tag2 >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform
      < result_of_reference_to_t< foo1&&, bar1& >
      , wrap< tag1 >, wrap< tag2 >
      >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < wrapped_t< foo1&&, tag1, tag2 >, wrapped_t< bar1&, tag1, tag2 > >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo_a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar_b );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < wrapped_t< foo1&, tag1, tag2 >, wrapped_t< bar1&, tag1, tag2 > >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo_a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar_b );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_lift_transform_nonbranching_ternary )
{
  foo1 foo_a = foo1::a;
  bar1 bar_b = bar1::b;

  decltype( auto ) provider
    = lift_transform
      ( reference_to( std::move( foo_a ), bar_b )
      , wrap< tag1 >(), wrap< tag2 >(), wrap< tag3 >()
      );

  using result_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform_t
      < result_of_reference_to_t< foo1&&, bar1& >
      , wrap< tag1 >, wrap< tag2 >, wrap< tag3 >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform
      < result_of_reference_to_t< foo1&&, bar1& >
      , wrap< tag1 >, wrap< tag2 >, wrap< tag3 >
      >::type
    >
  );

  // rvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( std::move( provider )
        , return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < wrapped_t< foo1&&, tag1, tag2, tag3 >
          , wrapped_t< bar1&, tag1, tag2, tag3 >
          >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo_a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar_b );
  }

  // lvalue provision
  {
    decltype( auto ) provision_result
      = prov_traits::provide
        ( provider
        , return_argument_values()
        );

    using provision_result_type = decltype( provision_result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < provision_result_type
      , std::variant
        < std::tuple
          < wrapped_t< foo1&, tag1, tag2, tag3 >
          , wrapped_t< bar1&, tag1, tag2, tag3 >
          >
        >
      >
    );

    ARGOT_TEST_EQ( provision_result.index(), 0 );
    auto& tup = std::get< 0 >( provision_result );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo_a );
    ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar_b );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_lift_transform_branching )
{
  foo1 foo1_a = foo1::a;
  bar1 bar1_b = bar1::b;

  foo2 foo2_a = foo2::a;
  bar2 bar2_b = bar2::b;

  foo3 foo3_a = foo3::a;
  bar3 bar3_b = bar3::b;

  foo4 foo4_a = foo4::a;
  bar4 bar4_b = bar4::b;

  decltype( auto ) provider_0_0
    = lift_transform
      ( group
        ( conditional
          ( true
          , reference_to( std::move( foo1_a ), bar1_b )
          , reference_to( std::move( foo2_a ), bar2_b )
          )
        , conditional
          ( true
          , reference_to( std::move( foo3_a ), bar3_b )
          , reference_to( std::move( foo4_a ), bar4_b )
          )
        )
      , wrap< tag1 >()
      );


  decltype( auto ) provider_0_1
    = lift_transform
      ( group
        ( conditional
          ( true
          , reference_to( std::move( foo1_a ), bar1_b )
          , reference_to( std::move( foo2_a ), bar2_b )
          )
        , conditional
          ( false
          , reference_to( std::move( foo3_a ), bar3_b )
          , reference_to( std::move( foo4_a ), bar4_b )
          )
        )
      , wrap< tag1 >()
      );


  decltype( auto ) provider_1_0
    = lift_transform
      ( group
        ( conditional
          ( false
          , reference_to( std::move( foo1_a ), bar1_b )
          , reference_to( std::move( foo2_a ), bar2_b )
          )
        , conditional
          ( true
          , reference_to( std::move( foo3_a ), bar3_b )
          , reference_to( std::move( foo4_a ), bar4_b )
          )
        )
      , wrap< tag1 >()
      );


  decltype( auto ) provider_1_1
    = lift_transform
      ( group
        ( conditional
          ( false
          , reference_to( std::move( foo1_a ), bar1_b )
          , reference_to( std::move( foo2_a ), bar2_b )
          )
        , conditional
          ( false
          , reference_to( std::move( foo3_a ), bar3_b )
          , reference_to( std::move( foo4_a ), bar4_b )
          )
        )
      , wrap< tag1 >()
      );

  using result_type = decltype( provider_0_0 );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform_t
      < result_of_group_t
        < result_of_conditional_t
          < bool
          , result_of_reference_to_t< foo1&&, bar1& >
          , result_of_reference_to_t< foo2&&, bar2& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< foo3&&, bar3& >
          , result_of_reference_to_t< foo4&&, bar4& >
          >
        >
      , wrap< tag1 >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform
      < result_of_group_t
        < result_of_conditional_t
          < bool
          , result_of_reference_to_t< foo1&&, bar1& >
          , result_of_reference_to_t< foo2&&, bar2& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< foo3&&, bar3& >
          , result_of_reference_to_t< foo4&&, bar4& >
          >
        >
      , wrap< tag1 >
      >::type
    >
  );

  // rvalue provision
  {
    // 0_0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_0_0 )
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo3&&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo1&&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo4&&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo3&&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo4&&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo1_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo3_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar3_b );
    }

    // 0_1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_0_1 )
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo3&&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo1&&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo4&&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo3&&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo4&&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo1_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo4_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar4_b );
    }

    // 1_0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_1_0 )
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo3&&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo1&&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo4&&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo3&&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo4&&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo2_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar2_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo3_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar3_b );
    }

    // 1_1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_1_1 )
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo3&&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo1&&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo4&&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo3&&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo4&&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
      auto& tup = std::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo2_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar2_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo4_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar4_b );
    }
  }

  // lvalue provision
  {
    // 0_0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_0_0
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo3&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo1&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo4&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo3&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo4&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo1_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo3_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar3_b );
    }

    // 0_1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_0_1
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo3&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo1&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo4&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo3&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo4&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo1_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo4_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar4_b );
    }

    // 1_0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_1_0
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo3&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo1&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo4&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo3&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo4&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo2_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar2_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo3_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar3_b );
    }

    // 1_1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_1_1
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo3&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo1&, tag1 >
            , wrapped_t< bar1&, tag1 >
            , wrapped_t< foo4&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo3&, tag1 >
            , wrapped_t< bar3&, tag1 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1 >
            , wrapped_t< bar2&, tag1 >
            , wrapped_t< foo4&, tag1 >
            , wrapped_t< bar4&, tag1 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
      auto& tup = std::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo2_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar2_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo4_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar4_b );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_lift_transform_branching_ternary )
{
  foo1 foo1_a = foo1::a;
  bar1 bar1_b = bar1::b;

  foo2 foo2_a = foo2::a;
  bar2 bar2_b = bar2::b;

  foo3 foo3_a = foo3::a;
  bar3 bar3_b = bar3::b;

  foo4 foo4_a = foo4::a;
  bar4 bar4_b = bar4::b;

  decltype( auto ) provider_0_0
    = lift_transform
      ( group
        ( conditional
          ( true
          , reference_to( std::move( foo1_a ), bar1_b )
          , reference_to( std::move( foo2_a ), bar2_b )
          )
        , conditional
          ( true
          , reference_to( std::move( foo3_a ), bar3_b )
          , reference_to( std::move( foo4_a ), bar4_b )
          )
        )
      , wrap< tag1 >(), wrap< tag2 >(), wrap< tag3 >()
      );


  decltype( auto ) provider_0_1
    = lift_transform
      ( group
        ( conditional
          ( true
          , reference_to( std::move( foo1_a ), bar1_b )
          , reference_to( std::move( foo2_a ), bar2_b )
          )
        , conditional
          ( false
          , reference_to( std::move( foo3_a ), bar3_b )
          , reference_to( std::move( foo4_a ), bar4_b )
          )
        )
      , wrap< tag1 >(), wrap< tag2 >(), wrap< tag3 >()
      );


  decltype( auto ) provider_1_0
    = lift_transform
      ( group
        ( conditional
          ( false
          , reference_to( std::move( foo1_a ), bar1_b )
          , reference_to( std::move( foo2_a ), bar2_b )
          )
        , conditional
          ( true
          , reference_to( std::move( foo3_a ), bar3_b )
          , reference_to( std::move( foo4_a ), bar4_b )
          )
        )
      , wrap< tag1 >(), wrap< tag2 >(), wrap< tag3 >()
      );


  decltype( auto ) provider_1_1
    = lift_transform
      ( group
        ( conditional
          ( false
          , reference_to( std::move( foo1_a ), bar1_b )
          , reference_to( std::move( foo2_a ), bar2_b )
          )
        , conditional
          ( false
          , reference_to( std::move( foo3_a ), bar3_b )
          , reference_to( std::move( foo4_a ), bar4_b )
          )
        )
      , wrap< tag1 >(), wrap< tag2 >(), wrap< tag3 >()
      );

  using result_type = decltype( provider_0_0 );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform_t
      < result_of_group_t
        < result_of_conditional_t
          < bool
          , result_of_reference_to_t< foo1&&, bar1& >
          , result_of_reference_to_t< foo2&&, bar2& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< foo3&&, bar3& >
          , result_of_reference_to_t< foo4&&, bar4& >
          >
        >
      , wrap< tag1 >, wrap< tag2 >, wrap< tag3 >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < result_type
    , result_of_lift_transform
      < result_of_group_t
        < result_of_conditional_t
          < bool
          , result_of_reference_to_t< foo1&&, bar1& >
          , result_of_reference_to_t< foo2&&, bar2& >
          >
        , result_of_conditional_t
          < bool
          , result_of_reference_to_t< foo3&&, bar3& >
          , result_of_reference_to_t< foo4&&, bar4& >
          >
        >
      , wrap< tag1 >, wrap< tag2 >, wrap< tag3 >
      >::type
    >
  );

  // rvalue provision
  {
    // 0_0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_0_0 )
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo3&&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo1&&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo4&&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo3&&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo4&&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo1_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo3_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar3_b );
    }

    // 0_1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_0_1 )
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo3&&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo1&&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo4&&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo3&&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo4&&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo1_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo4_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar4_b );
    }

    // 1_0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_1_0 )
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo3&&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo1&&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo4&&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo3&&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo4&&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo2_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar2_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo3_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar3_b );
    }

    // 1_1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider_1_1 )
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo3&&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo1&&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo4&&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo3&&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo4&&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
      auto& tup = std::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo2_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar2_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo4_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar4_b );
    }
  }

  // lvalue provision
  {
    // 0_0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_0_0
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo3&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo1&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo4&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo3&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo4&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo1_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo3_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar3_b );
    }

    // 0_1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_0_1
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo3&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo1&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo4&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo3&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo4&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo1_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar1_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo4_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar4_b );
    }

    // 1_0
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_1_0
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo3&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo1&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo4&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo3&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo4&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo2_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar2_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo3_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar3_b );
    }

    // 1_1
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider_1_1
          , return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < std::tuple
            < wrapped_t< foo1&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo3&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo1&, tag1, tag2, tag3 >
            , wrapped_t< bar1&, tag1, tag2, tag3 >
            , wrapped_t< foo4&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo3&, tag1, tag2, tag3 >
            , wrapped_t< bar3&, tag1, tag2, tag3 >
            >
          , std::tuple
            < wrapped_t< foo2&, tag1, tag2, tag3 >
            , wrapped_t< bar2&, tag1, tag2, tag3 >
            , wrapped_t< foo4&, tag1, tag2, tag3 >
            , wrapped_t< bar4&, tag1, tag2, tag3 >
            >
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
      auto& tup = std::get< 3 >( provision_result );

      ARGOT_TEST_EQ( &std::get< 0 >( tup ).ref, &foo2_a );
      ARGOT_TEST_EQ( &std::get< 1 >( tup ).ref, &bar2_b );
      ARGOT_TEST_EQ( &std::get< 2 >( tup ).ref, &foo4_a );
      ARGOT_TEST_EQ( &std::get< 3 >( tup ).ref, &bar4_b );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
