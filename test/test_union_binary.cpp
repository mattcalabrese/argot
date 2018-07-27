/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/union_.hpp>

#include <argot/concepts/constructible.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_value.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>
#include <argot/union_traits/alternative_type.hpp>
#include <argot/union_traits/get.hpp>
#include <argot/union_traits/index_constant.hpp>
#include <argot/union_traits/index_type.hpp>
#include <argot/union_traits/num_alternatives.hpp>

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>

#include "regularity_archetypes.hpp"
#include "regularity_facilities.hpp"
#include "regularity_testing.hpp"

// TODO(mattcalabrese) Test "odd" types (references, void).

namespace {

namespace union_traits = argot::union_traits;

using argot::Constructible;
using argot::Not;
using argot::SameType;
using argot::SameValue;
using argot::UnionLike;

using argot::union_;
using argot::in_place_index_with_result;

using argot_test::syntactic_regularity_profile_of_t;

template< int I >
using int_ = std::integral_constant< int, I >;

template< int I >
inline constexpr int_< I > int_v{};

struct constexpr_accumulate_fn
{
  constexpr int operator ()( std::initializer_list< int > ilist ) const
  {
    int result = 0;

    for( int v : ilist )
      result += v;

    return result;
  }
} inline constexpr constexpr_accumulate{};

template< int I >
struct trivial_constructor_trivial_destructor
{
  trivial_constructor_trivial_destructor() = default;
  ~trivial_constructor_trivial_destructor() = default;

  explicit constexpr trivial_constructor_trivial_destructor
  ( std::initializer_list< int > ilist, int& a, int const& b, int&& c
  , int_< I >
  )
    : value( constexpr_accumulate( ilist ) + a + b + c ) {}

  explicit constexpr trivial_constructor_trivial_destructor
  ( int& a, int const& b, int&& c, int_< I > )
    : value( a + b + c ) {}

  int value;
};

template< int I >
struct trivial_constructor_nontrivial_destructor
{
  trivial_constructor_nontrivial_destructor() = default;
  ~trivial_constructor_nontrivial_destructor() { *destroyed = true; }

  explicit constexpr trivial_constructor_nontrivial_destructor
  ( std::initializer_list< int > ilist, bool& destroyed_init, int_< I > )
    : destroyed( &destroyed_init )
    , value( constexpr_accumulate( ilist ) ) {}

  explicit constexpr trivial_constructor_nontrivial_destructor
  ( bool& destroyed_init, int& a, int const& b, int&& c, int_< I > )
    : destroyed( &destroyed_init ), value( a + b + c ) {}

  bool* destroyed;
  int value;
};

template< int I >
struct nontrivial_constructor_trivial_destructor
{
  constexpr nontrivial_constructor_trivial_destructor() noexcept {}
  ~nontrivial_constructor_trivial_destructor() = default;

  explicit constexpr nontrivial_constructor_trivial_destructor
  ( std::initializer_list< int > ilist, int& a, int const& b, int&& c
  , int_< I >
  )
    : value( constexpr_accumulate( ilist ) + a + b + c ) {}

  explicit constexpr nontrivial_constructor_trivial_destructor
  ( int& a, int const& b, int&& c, int_< I > )
    : value( a + b + c ) {}

  int value;
};

template< int I >
struct nontrivial_constructor_nontrivial_destructor
{
  constexpr nontrivial_constructor_nontrivial_destructor() noexcept {}
  ~nontrivial_constructor_nontrivial_destructor() noexcept
  {
    *destroyed = true;
  }

  explicit constexpr nontrivial_constructor_nontrivial_destructor
  ( std::initializer_list< int > ilist, bool& destroyed_init, int_< I > )
    : destroyed( &destroyed_init )
    , value( constexpr_accumulate( ilist ) ) {}

  explicit constexpr nontrivial_constructor_nontrivial_destructor
  ( bool& destroyed_init, int& a, int const& b, int&& c, int_< I > )
    : destroyed( &destroyed_init ), value( a + b + c ) {}

  bool* destroyed;
  int value;
};

ARGOT_REGISTER_CONSTEXPR_TEST( test_union_binary_construct_constexpr )
{
  {
    using alt0_t = trivial_constructor_trivial_destructor< 0 >;
    using alt1_t = trivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( std::in_place_index< 0 >, zero, one, std::move( two )
                , int_v< 0 >
                );

      union_t const& const_un = un;

      auto const& res_const_lvalue = union_traits::get< 0 >( const_un );

      auto const&& res_const_rvalue
        = union_traits::get< 0 >( std::move( const_un ) );

      auto& res_lvalue = union_traits::get< 0 >( un );

      auto&& res_rvalue = union_traits::get< 0 >( std::move( un ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( std::in_place_index< 1 >, zero, one, std::move( two )
                , int_v< 1 >
                );

      union_t const& const_un = un;

      auto const& res_const_lvalue = union_traits::get< 1 >( const_un );

      auto const&& res_const_rvalue
        = union_traits::get< 1 >( std::move( const_un ) );

      auto& res_lvalue = union_traits::get< 1 >( un );

      auto&& res_rvalue = union_traits::get< 1 >( std::move( un ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

      ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 3 );
    }
  }

  {
    using alt0_t = nontrivial_constructor_trivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( std::in_place_index< 0 >, zero, one, std::move( two )
                , int_v< 0 >
                );

      union_t const& const_un = un;

      auto const& res_const_lvalue = union_traits::get< 0 >( const_un );

      auto const&& res_const_rvalue
        = union_traits::get< 0 >( std::move( const_un ) );

      auto& res_lvalue = union_traits::get< 0 >( un );

      auto&& res_rvalue = union_traits::get< 0 >( std::move( un ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( std::in_place_index< 1 >, zero, one, std::move( two )
                , int_v< 1 >
                );

      union_t const& const_un = un;

      auto const& res_const_lvalue = union_traits::get< 1 >( const_un );

      auto const&& res_const_rvalue
        = union_traits::get< 1 >( std::move( const_un ) );

      auto& res_lvalue = union_traits::get< 1 >( un );

      auto&& res_rvalue = union_traits::get< 1 >( std::move( un ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

      ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 3 );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_binary_construct_not_constexpr )
{
  {
    using alt0_t = trivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = trivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un
        ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two )
        , int_v< 0 >
        );

        union_t const& const_un = un;

        auto const& res_const_lvalue = union_traits::get< 0 >( const_un );

        auto const&& res_const_rvalue
          = union_traits::get< 0 >( std::move( const_un ) );

        auto& res_lvalue = union_traits::get< 0 >( un );

        auto&& res_rvalue = union_traits::get< 0 >( std::move( un ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un
        ( std::in_place_index< 1 >, destroyed, zero, one, std::move( two )
        , int_v< 1 >
        );

        union_t const& const_un = un;

        auto const& res_const_lvalue = union_traits::get< 1 >( const_un );

        auto const&& res_const_rvalue
          = union_traits::get< 1 >( std::move( const_un ) );

        auto& res_lvalue = union_traits::get< 1 >( un );

        auto&& res_rvalue = union_traits::get< 1 >( std::move( un ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

        ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  {
    using alt0_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un
        ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two )
        , int_v< 0 >
        );

        union_t const& const_un = un;

        auto const& res_const_lvalue = union_traits::get< 0 >( const_un );

        auto const&& res_const_rvalue
          = union_traits::get< 0 >( std::move( const_un ) );

        auto& res_lvalue = union_traits::get< 0 >( un );

        auto&& res_rvalue = union_traits::get< 0 >( std::move( un ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un
        ( std::in_place_index< 1 >, destroyed, zero, one, std::move( two )
        , int_v< 1 >
        );

        union_t const& const_un = un;

        auto const& res_const_lvalue = union_traits::get< 1 >( const_un );

        auto const&& res_const_rvalue
          = union_traits::get< 1 >( std::move( const_un ) );

        auto& res_lvalue = union_traits::get< 1 >( un );

        auto&& res_rvalue = union_traits::get< 1 >( std::move( un ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

        ARGOT_TEST_EQ
        ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

        ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_union_binary_construct_constexpr_ilist )
{
  {
    using alt0_t = trivial_constructor_trivial_destructor< 0 >;
    using alt1_t = trivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, { 3, 4, 5 }, zero, one, std::move( two )
      , int_v< 0 >
      );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 1 >, { 3, 4, 5 }, zero, one, std::move( two )
      , int_v< 1 >
      );

      ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 15 );
    }
  }

  {
    using alt0_t = nontrivial_constructor_trivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, { 3, 4, 5 }, zero, one, std::move( two )
      , int_v< 0 >
      );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 1 >, { 3, 4, 5 }, zero, one, std::move( two )
      , int_v< 1 >
      );

      ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 15 );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_binary_construct_not_constexpr_ilist )
{
  {
    using alt0_t = trivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = trivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      bool destroyed = false;

      {
        union_t un
        ( std::in_place_index< 0 >, { 3, 4, 5 }, destroyed
        , int_v< 0 >
        );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }

    {
      bool destroyed = false;

      {
        union_t un
        ( std::in_place_index< 1 >, { 3, 4, 5 }, destroyed
        , int_v< 1 >
        );

        ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  {
    using alt0_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      bool destroyed = false;

      {
        union_t un
        ( std::in_place_index< 0 >, { 3, 4, 5 }, destroyed
        , int_v< 0 >
        );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }

    {
      bool destroyed = false;

      {
        union_t un
        ( std::in_place_index< 1 >, { 3, 4, 5 }, destroyed
        , int_v< 1 >
        );

        ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_binary_emplace )
{
  {
    using alt0_t = trivial_constructor_trivial_destructor< 0 >;
    using alt1_t = trivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res = un.emplace< 0 >( zero, one, std::move( two )
                                            , int_v< 0 >
                                            );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt0_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res = un.emplace< 1 >( zero, one, std::move( two )
                                            , int_v< 1 >
                                            );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt1_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 1 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 3 );
    }
  }

  {
    using alt0_t = nontrivial_constructor_trivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res = un.emplace< 0 >( zero, one, std::move( two )
                                            , int_v< 0 >
                                            );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt0_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res = un.emplace< 1 >( zero, one, std::move( two )
                                            , int_v< 1 >
                                            );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt1_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 1 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 3 );
    }
  }

  {
    using alt0_t = trivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = trivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un;

        decltype( auto ) res
          = un.emplace< 0 >( destroyed, zero, one, std::move( two )
                           , int_v< 0 >
                           );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt0_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un;

        decltype( auto ) res
          = un.emplace< 1 >( destroyed, zero, one, std::move( two )
                           , int_v< 1 >
                           );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt1_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 1 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  {
    using alt0_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un;

        decltype( auto ) res
          = un.emplace< 0 >( destroyed, zero, one, std::move( two )
                           , int_v< 0 >
                           );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt0_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un;

        decltype( auto ) res
          = un.emplace< 1 >( destroyed, zero, one, std::move( two )
                           , int_v< 1 >
                           );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt1_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 1 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_binary_emplace_ilist )
{
  {
    using alt0_t = trivial_constructor_trivial_destructor< 0 >;
    using alt1_t = trivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res
        = un.emplace< 0 >( { 3, 4, 5 }, zero, one, std::move( two )
                         , int_v< 0 >
                         );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt0_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res
        = un.emplace< 1 >( { 3, 4, 5 }, zero, one, std::move( two )
                         , int_v< 1 >
                         );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt1_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 1 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 15 );
    }
  }

  {
    using alt0_t = nontrivial_constructor_trivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res
        = un.emplace< 0 >( { 3, 4, 5 }, zero, one, std::move( two )
                         , int_v< 0 >
                         );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt0_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res
        = un.emplace< 1 >( { 3, 4, 5 }, zero, one, std::move( two )
                         , int_v< 1 >
                         );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt1_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 1 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 15 );
    }
  }

  {
    using alt0_t = trivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = trivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      bool destroyed = false;

      {
        union_t un;

        decltype( auto ) res = un.emplace< 0 >( { 3, 4, 5 }, destroyed
                                              , int_v< 0 >
                                              );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt0_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }

    {
      bool destroyed = false;

      {
        union_t un;

        decltype( auto ) res = un.emplace< 1 >( { 3, 4, 5 }, destroyed
                                              , int_v< 1 >
                                              );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt1_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 1 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  {
    using alt0_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      bool destroyed = false;

      {
        union_t un;

        decltype( auto ) res = un.emplace< 0 >( { 3, 4, 5 }, destroyed
                                              , int_v< 0 >
                                              );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt0_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }

    {
      bool destroyed = false;

      {
        union_t un;

        decltype( auto ) res = un.emplace< 1 >( { 3, 4, 5 }, destroyed
                                              , int_v< 1 >
                                              );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt1_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 1 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 1 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_union_destroy_constexpr )
{
  {
    using alt0_t = trivial_constructor_trivial_destructor< 0 >;
    using alt1_t = trivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, zero, one, std::move( two )
      , int_v< 0 >
      );

      un.destroy< 0 >();
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 1 >, zero, one, std::move( two )
      , int_v< 1 >
      );

      un.destroy< 1 >();
    }
  }

  {
    using alt0_t = nontrivial_constructor_trivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_trivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, zero, one, std::move( two )
      , int_v< 0 >
      );

      un.destroy< 0 >();
    }

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 1 >, zero, one, std::move( two )
      , int_v< 1 >
      );

      un.destroy< 1 >();
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_destroy_not_constexpr )
{
  {
    using alt0_t = trivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = trivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two )
      , int_v< 0 >
      );

      ARGOT_TEST_FALSE( destroyed );

      un.destroy< 0 >();

      ARGOT_TEST_TRUE( destroyed );
    }

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 1 >, destroyed, zero, one, std::move( two )
      , int_v< 1 >
      );

      ARGOT_TEST_FALSE( destroyed );

      un.destroy< 1 >();

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  {
    using alt0_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using alt1_t = nontrivial_constructor_nontrivial_destructor< 1 >;
    using union_t = union_< alt0_t, alt1_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two )
      , int_v< 0 >
      );

      ARGOT_TEST_FALSE( destroyed );

      un.destroy< 0 >();

      ARGOT_TEST_TRUE( destroyed );
    }

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 1 >, destroyed, zero, one, std::move( two )
      , int_v< 1 >
      );

      ARGOT_TEST_FALSE( destroyed );

      un.destroy< 1 >();

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_regularity_homogeneous )
{
  using argot_test::combine_regularity_profiles_t;
  using argot_test::regularity_archetype;

  {
    using alt_prof
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch = regularity_archetype< alt_prof >;
    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    using un = union_< arch, arch >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< un >
      , expected_prof
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< un, expected_prof >
      ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
      )
    );
  }

  {
    using alt_prof
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch = regularity_archetype< alt_prof >;
    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    using un = union_< arch, arch >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< un >
      , expected_prof
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< un, expected_prof >
      ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
      )
    );
  }

  {
    using alt_prof
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch = regularity_archetype< alt_prof >;
    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::nothrow_destructor_profile
        >;

    using un = union_< arch, arch >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< un >
      , expected_prof
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< un, expected_prof >
      ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
      )
    );
  }

  {
    using alt_prof
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch = regularity_archetype< alt_prof >;
    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::nothrow_destructor_profile
        , argot_test::nothrow_swap_profile
        >;

    using un = union_< arch, arch >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< un >
      , expected_prof
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< un, expected_prof >
      ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
      )
    );
  }

  {
    using alt_prof
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch = regularity_archetype< alt_prof >;
    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using un = union_< arch, arch >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< un >
      , expected_prof
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< un, expected_prof >
      ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
      )
    );
  }

  {
    using alt_prof
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch = regularity_archetype< alt_prof >;
    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using un = union_< arch, arch >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< un >
      , expected_prof
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< un, expected_prof >
      ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
      )
    );
  }

  {
    using alt_prof
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch = regularity_archetype< alt_prof >;
    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using un = union_< arch, arch >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< un >
      , expected_prof
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< un, expected_prof >
      ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
      )
    );
  }

  {
    using alt_prof
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch = regularity_archetype< alt_prof >;
    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        , argot_test::nothrow_swap_profile
        >;

    using un = union_< arch, arch >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< un >
      , expected_prof
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< un, expected_prof >
      ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
      , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
      )
    );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_regularity_heterogeneous )
{
  using argot_test::combine_regularity_profiles_t;
  using argot_test::regularity_archetype;

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_destructor_profile // because stdlib defect
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile // because stdlib defect
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_destructor_profile // because stdlib defect
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile // because stdlib defect
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::nothrow_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        , argot_test::nothrow_swap_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::exceptional_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        , argot_test::nothrow_swap_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile\
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile\
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  {
    using alt_prof0
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using alt_prof1
      = combine_regularity_profiles_t
        < argot_test::no_default_constructor_profile
        , argot_test::trivial_copy_constructor_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    using arch0 = regularity_archetype< alt_prof0 >;
    using arch1 = regularity_archetype< alt_prof1 >;

    using expected_prof
      = combine_regularity_profiles_t
        < argot_test::nothrow_default_constructor_profile
        , argot_test::trivial_move_assign_profile
        , argot_test::trivial_copy_assign_profile
        , argot_test::trivial_destructor_profile
        >;

    {
      using un = union_< arch0, arch1 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch0::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch1::make, 5 ); }
        )
      );
    }

    {
      using un = union_< arch1, arch0 >;

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < syntactic_regularity_profile_of_t< un >
        , expected_prof
        >
      );

      ARGOT_TEST_SUCCESS
      ( argot_test::test_regularity< un, expected_prof >
        ( []{ return un( in_place_index_with_result< 0 >, arch1::make, 0 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 1 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 3 ); }
        , []{ return un( in_place_index_with_result< 0 >, arch1::make, 5 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 0 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 1 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 3 ); }
        , []{ return un( in_place_index_with_result< 1 >, arch0::make, 5 ); }
        )
      );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
