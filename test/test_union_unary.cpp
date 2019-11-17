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

#include "regularity_archetypes.hpp"
#include "regularity_facilities.hpp"
#include "regularity_testing.hpp"

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>

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

template< int >
struct trivial_constructor_trivial_destructor
{
  trivial_constructor_trivial_destructor() = default;
  ~trivial_constructor_trivial_destructor() = default;

  explicit constexpr trivial_constructor_trivial_destructor
  ( std::initializer_list< int > ilist, int& a, int const& b, int&& c )
    : value( constexpr_accumulate( ilist ) + a + b + c ) {}

  explicit constexpr trivial_constructor_trivial_destructor
  ( int& a, int const& b, int&& c )
    : value( a + b + c ) {}

  int value;
};

template< int >
struct trivial_constructor_nontrivial_destructor
{
  trivial_constructor_nontrivial_destructor() = default;
  ~trivial_constructor_nontrivial_destructor() { *destroyed = true; }

  explicit constexpr trivial_constructor_nontrivial_destructor
  ( std::initializer_list< int > ilist, bool& destroyed_init )
    : destroyed( &destroyed_init )
    , value( constexpr_accumulate( ilist ) ) {}

  explicit constexpr trivial_constructor_nontrivial_destructor
  ( bool& destroyed_init, int& a, int const& b, int&& c )
    : destroyed( &destroyed_init ), value( a + b + c ) {}

  bool* destroyed;
  int value;
};

template< int >
struct nontrivial_constructor_trivial_destructor
{
  constexpr nontrivial_constructor_trivial_destructor() noexcept {}
  ~nontrivial_constructor_trivial_destructor() = default;

  explicit constexpr nontrivial_constructor_trivial_destructor
  ( std::initializer_list< int > ilist, int& a, int const& b, int&& c )
    : value( constexpr_accumulate( ilist ) + a + b + c ) {}

  explicit constexpr nontrivial_constructor_trivial_destructor
  ( int& a, int const& b, int&& c )
    : value( a + b + c ) {}

  int value;
};

template< int >
struct nontrivial_constructor_nontrivial_destructor
{
  constexpr nontrivial_constructor_nontrivial_destructor() noexcept {}
  ~nontrivial_constructor_nontrivial_destructor() noexcept
  {
    *destroyed = true;
  }

  explicit constexpr nontrivial_constructor_nontrivial_destructor
  ( std::initializer_list< int > ilist, bool& destroyed_init )
    : destroyed( &destroyed_init )
    , value( constexpr_accumulate( ilist ) ) {}

  explicit constexpr nontrivial_constructor_nontrivial_destructor
  ( bool& destroyed_init, int& a, int const& b, int&& c )
    : destroyed( &destroyed_init ), value( a + b + c ) {}

  bool* destroyed;
  int value;
};

ARGOT_REGISTER_CONSTEXPR_TEST( test_union_unary_construct_constexpr )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( in_place_index_with_result< 0 >
                , []( auto& z, auto& o, auto&& t )
                  {
                    return alt_t( z, o, std::forward< decltype( t ) >( t ) );
                  }
                , zero, one, std::move( two )
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
  }

  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( std::in_place_index< 0 >, zero, one, std::move( two ) );
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
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( std::in_place_index< 0 >, zero, one, std::move( two ) );
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
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_unary_construct_not_constexpr )
{
  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un( in_place_index_with_result< 0 >
                  , []( auto& d, auto& z, auto& o, auto&& t )
                    {
                      return alt_t
                             ( d, z, o, std::forward< decltype( t ) >( t ) );
                    }
                  , destroyed, zero, one, std::move( two )
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
  }

  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un
        ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two ) );

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
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un
        ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two ) );

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
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_union_unary_construct_constexpr_ilist )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, { 3, 4, 5 }, zero, one, std::move( two ) );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, { 3, 4, 5 }, zero, one, std::move( two ) );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_unary_construct_not_constexpr_ilist )
{
  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;

      {
        union_t un
        ( std::in_place_index< 0 >, { 3, 4, 5 }, destroyed );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;

      {
        union_t un
        ( std::in_place_index< 0 >, { 3, 4, 5 }, destroyed );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_unary_emplace )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res = un.emplace< 0 >( zero, one, std::move( two ) );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res = un.emplace< 0 >( zero, one, std::move( two ) );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
    }
  }

  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un;

        decltype( auto ) res
          = un.emplace< 0 >( destroyed, zero, one, std::move( two ) );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        union_t un;

        decltype( auto ) res
          = un.emplace< 0 >( destroyed, zero, one, std::move( two ) );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_unary_emplace_ilist )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res
        = un.emplace< 0 >( { 3, 4, 5 }, zero, one, std::move( two ) );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un;

      decltype( auto ) res
        = un.emplace< 0 >( { 3, 4, 5 }, zero, one, std::move( two ) );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }
  }

  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;

      {
        union_t un;

        decltype( auto ) res = un.emplace< 0 >( { 3, 4, 5 }, destroyed );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;

      {
        union_t un;

        decltype( auto ) res = un.emplace< 0 >( { 3, 4, 5 }, destroyed );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_FALSE( destroyed );
    }
  }

  return 0;
}

// TODO(mattcalabrese) Make this constexpr in C++20
ARGOT_REGISTER_TEST( test_union_destroy_constexpr )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      un.destroy< 0 >();
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      un.destroy< 0 >();
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_destroy_not_constexpr )
{
  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two ) );

      ARGOT_TEST_FALSE( destroyed );

      un.destroy< 0 >();

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un
      ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two ) );

      ARGOT_TEST_FALSE( destroyed );

      un.destroy< 0 >();

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_reference )
{
  {
    using alt_t = int const&;
    using union_t = union_< alt_t >;

    {
      int const five = 5;
      int const ten = 10;

      union_t un( in_place_index_with_result< 0 >
                , [ &five ]( int ) -> int const& { return five; }
                , 0
                );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &five );

      un = union_t( in_place_index_with_result< 0 >
                  , [ &ten ]( int ) -> int const& { return ten; }
                  , 0
                  );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 10 );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &ten );

      un.destroy< 0 >();
    }

    {
      int const five = 5;
      int const ten = 10;

      union_t un( std::in_place_index< 0 >, five );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &five );

      un = union_t( std::in_place_index< 0 >, ten );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 10 );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &ten );

      un.destroy< 0 >();
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_union_reference_emplace )
{
  {
    using alt_t = int const&;
    using union_t = union_< alt_t >;

    {
      int const five = 5;

      union_t un;
      decltype( auto ) emplace_result = un.emplace< 0 >( five );

      ARGOT_CONCEPT_ENSURE
      ( SameType< decltype( emplace_result ), int const& > );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );
      ARGOT_TEST_EQ( &emplace_result, &five );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &five );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_union_const )
{
  {
    using alt_t = int const;
    using union_t = union_< alt_t >;

    {
      union_t un( in_place_index_with_result< 0 >
                , []( int ) { return 5; }
                , 0
                );

      decltype( auto ) assign_result = un.assign< 0 >( 5 );

      ARGOT_CONCEPT_ENSURE
      ( SameType< decltype( assign_result ), int const& > );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );

      un = union_t( in_place_index_with_result< 0 >
                  , []( int ) { return 10; }
                  , 0
                  );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 10 );
    }

    {
      union_t un( std::in_place_index< 0 >, 5 );
      decltype( auto ) assign_result = un.assign< 0 >( 5 );

      ARGOT_CONCEPT_ENSURE
      ( SameType< decltype( assign_result ), int const& > );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );

      un = union_t( std::in_place_index< 0 >, 10 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 10 );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_union_unary_assign_constexpr )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( std::in_place_index< 0 > );

      decltype( auto ) res
        = un.assign< 0 >( alt_t( zero, one, std::move( two ) ) );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using union_t = union_< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      union_t un( std::in_place_index< 0 > );

      decltype( auto ) res
        = un.assign< 0 >( alt_t( zero, one, std::move( two ) ) );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );
    }
  }

  return 0;
}

template< class AlternativeProfile, class ExpectedUnionProfile >
constexpr ::argot::call_detail::constexpr_block_result_t
test_union_of_archetype_regularity()
{
  using arch = argot_test::regularity_archetype< AlternativeProfile >;

  using un = union_< arch >;

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < syntactic_regularity_profile_of_t< un >
    , ExpectedUnionProfile
    >
  );

  ARGOT_TEST_SUCCESS
  ( argot_test::test_regularity< un, ExpectedUnionProfile >
    ( []{ return un( in_place_index_with_result< 0 >, arch::make, 0 ); }
    , []{ return un( in_place_index_with_result< 0 >, arch::make, 1 ); }
    , []{ return un( in_place_index_with_result< 0 >, arch::make, 3 ); }
    , []{ return un( in_place_index_with_result< 0 >, arch::make, 5 ); }
    )
  );

  return 0;
}


ARGOT_REGISTER_TEST( test_union_regularity )
{
  using argot_test::combine_regularity_profiles_t;

  ARGOT_TEST_SUCCESS
  ( test_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::exceptional_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::nothrow_destructor_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_move_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_destructor_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::exceptional_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_move_assign_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::nothrow_destructor_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::trivial_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_move_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_move_assign_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::trivial_destructor_profile
      , argot_test::nothrow_swap_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_destructor_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_move_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_destructor_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::trivial_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_move_assign_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::trivial_destructor_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::trivial_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_move_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_move_assign_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::trivial_destructor_profile
      , argot_test::nothrow_swap_profile
      >
    >()
  );

  return 0;
}

// TODO(mattcalabrese) test initializer_list for assign.

ARGOT_EXECUTE_TESTS();

}  // namespace
