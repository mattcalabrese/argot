/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy chunk http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/prov/chunk.hpp>

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_value.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov_traits/argument_list_kinds_of.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/receiver/return_argument_values.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/tuple_traits/element_type.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/tuple_traits/num_elements.hpp>
#include <argot/variant_traits/alternative_type.hpp>
#include <argot/variant_traits/get.hpp>
#include <argot/variant_traits/num_alternatives.hpp>

#include <variant>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace tuple_traits = argot::tuple_traits;
namespace variant_traits = argot::variant_traits;

using argot::ArgumentProvider;
using argot::SameType;
using argot::SameValue;

using receiver_traits::argument_list_kinds_t;
using receiver_traits::argument_types_t;

using prov::chunk;
using prov::chunk_fn;

struct a {};
struct b {};
struct c {};

using generator_type = decltype( chunk );

ARGOT_CONCEPT_ENSURE
( SameType
  < generator_type
  , chunk_fn const
  >
);

// TODO(mattcalabrese) Possibly test branching providers.

ARGOT_REGISTER_CONSTEXPR_TEST( test_static_chunk_1 )
{
  constexpr std::integral_constant< std::size_t, 1 > one{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = chunk( one, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 3 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup_t, 1 >;
      using chunk2_t = tuple_traits::element_type_t< arg_tup_t, 2 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk2_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk2_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 2 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk2_provision_result_type
          = decltype( chunk2_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk2_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk2_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 3 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup_t, 1 >;
      using chunk2_t = tuple_traits::element_type_t< arg_tup_t, 2 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk2_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk2_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 2 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk2_provision_result_type
          = decltype( chunk2_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk2_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk2_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 3 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup_t, 1 >;
      using chunk2_t = tuple_traits::element_type_t< arg_tup_t, 2 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk2_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk2_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 2 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk2_provision_result_type
          = decltype( chunk2_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk2_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk2_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 3 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup_t, 1 >;
      using chunk2_t = tuple_traits::element_type_t< arg_tup_t, 2 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk2_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< b&& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk2_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 2 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk2_provision_result_type
          = decltype( chunk2_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk2_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk2_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_static_chunk_2 )
{
  constexpr std::integral_constant< std::size_t, 2 > two{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = chunk( two, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 2 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup_t, 1 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 2 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup_t, 1 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 2 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup_t, 1 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 2 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup_t, 1 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_static_chunk_3 )
{
  constexpr std::integral_constant< std::size_t, 3 > three{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = chunk( three, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 1 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 1 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 1 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 1 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_static_chunk_4 )
{
  constexpr std::integral_constant< std::size_t, 4 > four{};

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = chunk( four, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 1 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 1 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 1 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 1 )
        >
      );
    
      using arg_tup_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < tuple_traits::num_elements_v< arg_tup_t >
        , static_cast< std::size_t >( 1 )
        >
      );

      using chunk0_t = tuple_traits::element_type_t< arg_tup_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      ARGOT_TEST_EQ( provision_result.index(), 0 );
      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_chunk_1 )
{
  constexpr std::size_t one = 1;

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = chunk( one, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup0_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup0_t, 1 >;
      using chunk2_t = tuple_traits::element_type_t< arg_tup0_t, 2 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk2_t > );

      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk2_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 2 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk2_provision_result_type
          = decltype( chunk2_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk2_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk2_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup0_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup0_t, 1 >;
      using chunk2_t = tuple_traits::element_type_t< arg_tup0_t, 2 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk2_t > );

      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk2_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 2 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk2_provision_result_type
          = decltype( chunk2_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk2_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk2_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup0_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup0_t, 1 >;
      using chunk2_t = tuple_traits::element_type_t< arg_tup0_t, 2 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk2_t > );

      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk2_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 2 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk2_provision_result_type
          = decltype( chunk2_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk2_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk2_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b&& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 0 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup0_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup0_t, 1 >;
      using chunk2_t = tuple_traits::element_type_t< arg_tup0_t, 2 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk2_t > );

      auto& arg_tup = std::get< 0 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< b&& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk2_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 2 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk2_provision_result_type
          = decltype( chunk2_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk2_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk2_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_chunk_2 )
{
  constexpr std::size_t two = 2;

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = chunk( two, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup1_t, 1 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );

      auto& arg_tup = std::get< 1 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup1_t, 1 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );

      auto& arg_tup = std::get< 1 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup1_t, 1 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );

      auto& arg_tup = std::get< 1 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b&& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 1 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup0_t, 0 >;
      using chunk1_t = tuple_traits::element_type_t< arg_tup0_t, 1 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );
      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk1_t > );

      auto& arg_tup = std::get< 1 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
      }

      {
        decltype( auto ) chunk1_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 1 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk1_provision_result_type
          = decltype( chunk1_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk1_provision_result_type
          , std::variant< argot::struct_< c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk1_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &c_ );
      }
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_chunk_3 )
{
  constexpr std::size_t three = 3;

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = chunk( three, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      auto& arg_tup = std::get< 2 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      auto& arg_tup = std::get< 2 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      auto& arg_tup = std::get< 2 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b&& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      auto& arg_tup = std::get< 2 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_dynamic_chunk_4 )
{
  constexpr std::size_t four = 4;

  a a_{};
  b b_{};
  c const c_{};

  auto source_provider
    = prov::reference_to( a_, std::move( b_ ), c_ );

  auto provider = chunk( four, std::move( source_provider ) );

  // lvalue provision
  {
    // const lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::as_const( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      auto& arg_tup = std::get< 2 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }

    // lvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( provider
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      auto& arg_tup = std::get< 2 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( arg_tup )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }
  }

  // rvalue provision
  {
    // const rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( std::as_const( provider ) )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      auto& arg_tup = std::get< 2 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }

    // rvalue
    {
      decltype( auto ) provision_result
        = prov_traits::provide
          ( std::move( provider )
          , receiver::return_argument_values()
          );

      using provision_result_type
        = decltype( provision_result );

      ARGOT_CONCEPT_ENSURE
      ( SameValue
        < variant_traits::num_alternatives_v< provision_result_type >
        , static_cast< std::size_t >( 3 )
        >
      );
    
      using arg_tup0_t
        = variant_traits::alternative_type_t< provision_result_type, 0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 1 > >
        , argument_list_kinds_t< argument_types_t< b&& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup0_t, 2 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup1_t
        = variant_traits::alternative_type_t< provision_result_type, 1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&& > >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup1_t, 1 > >
        , argument_list_kinds_t< argument_types_t< c const& > >
        >
      );

      using arg_tup2_t
        = variant_traits::alternative_type_t< provision_result_type, 2 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < prov_traits::argument_list_kinds_of_t
          < tuple_traits::element_type_t< arg_tup2_t, 0 > >
        , argument_list_kinds_t< argument_types_t< a&, b&&, c const& > >
        >
      );

      ARGOT_TEST_EQ( provision_result.index(), 2 );

      using chunk0_t = tuple_traits::element_type_t< arg_tup1_t, 0 >;

      ARGOT_CONCEPT_ENSURE( ArgumentProvider< chunk0_t > );

      auto& arg_tup = std::get< 2 >( provision_result );

      {
        decltype( auto ) chunk0_provision_result
          = prov_traits::provide
            ( tuple_traits::get< 0 >( std::move( arg_tup ) )
            , receiver::return_argument_references()
            );

        using chunk0_provision_result_type
          = decltype( chunk0_provision_result );

        ARGOT_CONCEPT_ENSURE
        ( SameType
          < chunk0_provision_result_type
          , std::variant< argot::struct_< a&, b&&, c const& > >
          >
        );

        auto& nested_args = std::get< 0 >( chunk0_provision_result );

        ARGOT_TEST_EQ( &tuple_traits::get< 0 >( nested_args ), &a_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 1 >( nested_args ), &b_ );
        ARGOT_TEST_EQ( &tuple_traits::get< 2 >( nested_args ), &c_ );
      }
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
