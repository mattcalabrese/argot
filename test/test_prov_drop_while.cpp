/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/prov/drop_while.hpp>

#include <argot/concepts/exceptional_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/unpack.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/tuple_traits/get.hpp>

#include <tuple>
#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace tuple_traits = argot::tuple_traits;

using argot::SameType;

using prov::drop_while;
using prov::drop_while_fn;

struct a {};
struct b {};
struct c {};

struct never
{
  template< class T >
  constexpr std::false_type operator()( T ) const { return {}; }
};

struct is_a
  : private never
{
  using never::operator();
  constexpr std::true_type operator()( a ) const { return {}; }
};

struct is_a_or_b
  : private is_a
{
  using is_a::operator();
  constexpr std::true_type operator()( b ) const { return {}; }
};

struct is_a_or_b_or_c
  : private is_a_or_b
{
  using is_a_or_b::operator();
  constexpr std::true_type operator()( c ) const { return {}; }
};

struct dynamic_never
{
  template< class T >
  constexpr bool operator()( T ) const { return false; }
};

struct dynamic_is_a
  : private dynamic_never
{
  using dynamic_never::operator();
  constexpr bool operator()( a ) const { return true; }
};

struct dynamic_is_a_or_b
  : private dynamic_is_a
{
  using dynamic_is_a::operator();
  constexpr bool operator()( b ) const { return true; }
};

struct dynamic_is_a_or_b_or_c
  : private dynamic_is_a_or_b
{
  using dynamic_is_a_or_b::operator();
  constexpr bool operator()( c ) const { return true; }
};

using generator_type = decltype( drop_while );

ARGOT_CONCEPT_ENSURE
( SameType
  < generator_type
  , drop_while_fn const
  >
);

// TODO(mattcalabrese) Possibly test branching providers.
// TODO(mattcalabrese) Support and test conditions that return
// true_type/false_type as having minimal branches.

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_drop_while_0 )
{
  constexpr dynamic_never condition{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop_while( condition, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &a_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c_ );
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &a_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c_ );
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &a_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c_ );
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&&, c const& >
          , argot::struct_< b&&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &a_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &c_ );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_drop_while_1 )
{
  constexpr dynamic_is_a condition{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop_while( condition, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &c_ );
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &c_ );
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &c_ );
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&&, c const& >
          , argot::struct_< b&&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );
      auto& tup = std::get< 1 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &c_ );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_drop_while_2 )
{
  constexpr dynamic_is_a_or_b condition{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop_while( condition, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &c_ );
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &c_ );
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &c_ );
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&&, c const& >
          , argot::struct_< b&&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );
      auto& tup = std::get< 2 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &c_ );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_drop_while_3 )
{
  constexpr dynamic_is_a_or_b_or_c condition{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop_while( condition, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&, c const& >
          , argot::struct_< b&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_references()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < provision_result_type
        , std::variant
          < argot::struct_< a&, b&&, c const& >
          , argot::struct_< b&&, c const& >
          , argot::struct_< c const& >
          , argot::struct_<>
          >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 3 );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
