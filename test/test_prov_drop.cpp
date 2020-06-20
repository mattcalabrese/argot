/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/prov/drop.hpp>

#include <argot/concepts/exceptional_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/unpack.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/tuple_traits/get.hpp>

#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace tuple_traits = argot::tuple_traits;

using argot::SameType;

using prov::drop;
using prov::drop_fn;

struct a {};
struct b {};
struct c {};

using generator_type = decltype( drop );

ARGOT_CONCEPT_ENSURE
( SameType
  < generator_type
  , drop_fn const
  >
);

// TODO(mattcalabrese) Possibly test branching providers.

ARGOT_REGISTER_CONSTEXPR_TEST( test_static_drop_0 )
{
  constexpr std::integral_constant< std::size_t, 0 > zero{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop( zero, std::move( source_provider ) );

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
        , std::variant< argot::struct_< a&, b&, c const& > >
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
        , std::variant< argot::struct_< a&, b&, c const& > >
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
        , std::variant< argot::struct_< a&, b&, c const& > >
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
        , std::variant< argot::struct_< a&, b&&, c const& > >
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

ARGOT_REGISTER_CONSTEXPR_TEST( test_static_drop_1 )
{
  constexpr std::integral_constant< std::size_t, 1 > one{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop( one, std::move( source_provider ) );

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
        , std::variant< argot::struct_< b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

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
        , std::variant< argot::struct_< b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

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
        , std::variant< argot::struct_< b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

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
        , std::variant< argot::struct_< b&&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &b_ );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &c_ );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_static_drop_2 )
{
  constexpr std::integral_constant< std::size_t, 2 > two{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop( two, std::move( source_provider ) );

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
        , std::variant< argot::struct_< c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

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
        , std::variant< argot::struct_< c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

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
        , std::variant< argot::struct_< c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

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
        , std::variant< argot::struct_< c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& tup = std::get< 0 >( provision_result );

      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &c_ );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_static_drop_3 )
{
  constexpr std::integral_constant< std::size_t, 3 > three{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop( three, std::move( source_provider ) );

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
        , std::variant< argot::struct_<> >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
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
        , std::variant< argot::struct_<> >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
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
        , std::variant< argot::struct_<> >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
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
        , std::variant< argot::struct_<> >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_drop_0 )
{
  constexpr std::size_t zero = 0;

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop( zero, std::move( source_provider ) );

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

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_drop_1 )
{
  constexpr std::size_t one = 1;

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop( one, std::move( source_provider ) );

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

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_drop_2 )
{
  constexpr std::size_t two = 2;

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop( two, std::move( source_provider ) );

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

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_drop_3 )
{
  constexpr std::size_t three = 3;

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = drop( three, std::move( source_provider ) );

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
