/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/discriminated_union.hpp>

#include <argot/concepts/constructible.hpp>
#include <argot/concepts/equality_comparable.hpp>
#include <argot/concepts/inequality_comparable.hpp>
#include <argot/concepts/less_than_comparable.hpp>
#include <argot/concepts/less_equal_comparable.hpp>
#include <argot/concepts/greater_equal_comparable.hpp>
#include <argot/concepts/greater_than_comparable.hpp>
#include <argot/concepts/nothrow_equality_comparable.hpp>
#include <argot/concepts/nothrow_inequality_comparable.hpp>
#include <argot/concepts/nothrow_less_than_comparable.hpp>
#include <argot/concepts/nothrow_less_equal_comparable.hpp>
#include <argot/concepts/nothrow_greater_equal_comparable.hpp>
#include <argot/concepts/nothrow_greater_than_comparable.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_value.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>
#include <argot/union_traits/alternative_type.hpp>
#include <argot/union_traits/get.hpp>
#include <argot/union_traits/index_constant.hpp>
#include <argot/union_traits/index_type.hpp>
#include <argot/union_traits/num_alternatives.hpp>
#include <argot/variant_traits/index_of.hpp>
#include <argot/void_.hpp>

#include "regularity_archetypes.hpp"
#include "regularity_facilities.hpp"
#include "regularity_testing.hpp"

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>

// TODO(mattcalabrese) Finish testing "odd" types (references, void, const).

// TODO(mattcalabrese) Test copy, assign, and triviality.

namespace {

namespace union_traits = argot::union_traits;
namespace variant_traits = argot::variant_traits;

using argot::Constructible;
using argot::EqualityComparable;
using argot::InequalityComparable;
using argot::LessThanComparable;
using argot::LessEqualComparable;
using argot::GreaterEqualComparable;
using argot::GreaterThanComparable;
using argot::Not;
using argot::NothrowEqualityComparable;
using argot::NothrowInequalityComparable;
using argot::NothrowLessThanComparable;
using argot::NothrowLessEqualComparable;
using argot::NothrowGreaterEqualComparable;
using argot::NothrowGreaterThanComparable;
using argot::SameType;

using argot::discriminated_union;
using argot::void_;
using argot::in_place_index_with_result;

using argot_test::syntactic_regularity_profile_of_t;

template< bool Exists, bool IsNoexcept >
struct bool_ret
{
  template< bool Enable = Exists, std::enable_if_t< Enable, int > = 0 >
  constexpr explicit operator bool() const noexcept( IsNoexcept )
  {
    return value;
  }

  bool value;
};

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

enum class eq_compare_kind { none, noexcept_, not_noexcept, dubious };
enum class less_compare_kind { none, noexcept_, not_noexcept, dubious };
enum class swap_kind { none, noexcept_, not_noexcept };
enum class hash_kind { none, noexcept_, not_noexcept, dubious };

template< int, eq_compare_kind EqComp = eq_compare_kind::none
             , less_compare_kind LessComp = less_compare_kind::none
             , swap_kind Swap = swap_kind::none
             , hash_kind Hash = hash_kind::none
             >
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

template< int V, eq_compare_kind EqComp, less_compare_kind LessComp
               , swap_kind Swap, hash_kind Hash
        , std::enable_if_t< EqComp != eq_compare_kind::none, int > = 0
        >
constexpr bool_ret
< EqComp != eq_compare_kind::none, EqComp != eq_compare_kind::dubious >
operator ==
( trivial_constructor_trivial_destructor< V, EqComp, LessComp, Swap, Hash >
    const& lhs
, trivial_constructor_trivial_destructor< V, EqComp, LessComp, Swap, Hash >
    const& rhs
)
noexcept( EqComp == eq_compare_kind::noexcept_ )
{
  return { lhs.value == rhs.value };
}

template< int V, eq_compare_kind EqComp, less_compare_kind LessComp
               , swap_kind Swap, hash_kind Hash
        >
constexpr bool_ret
< LessComp != less_compare_kind::none, LessComp != less_compare_kind::dubious >
operator <
( trivial_constructor_trivial_destructor< V, EqComp, LessComp, Swap, Hash >
    const& lhs
, trivial_constructor_trivial_destructor< V, EqComp, LessComp, Swap, Hash >
    const& rhs
)
noexcept( LessComp == less_compare_kind::noexcept_ )
{
  return { lhs.value < rhs.value };
}

template< int V, eq_compare_kind EqComp, less_compare_kind LessComp
               , swap_kind Swap, hash_kind Hash
        >
constexpr int /*return type shouldn't matter*/
swap
( trivial_constructor_trivial_destructor< V, EqComp, LessComp, Swap, Hash >& lhs
, trivial_constructor_trivial_destructor< V, EqComp, LessComp, Swap, Hash >& rhs
)
noexcept( Swap == swap_kind::noexcept_ )
{
  auto old_lhs = lhs.value;
  lhs.value = rhs.value;
  rhs.value = old_lhs;
  return 0;
}

template< int, eq_compare_kind EqComp = eq_compare_kind::none
             , less_compare_kind LessComp = less_compare_kind::none
             , swap_kind Swap = swap_kind::none
             , hash_kind Hash = hash_kind::none
             >
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

template< int, eq_compare_kind EqComp = eq_compare_kind::none
             , less_compare_kind LessComp = less_compare_kind::none
             , swap_kind Swap = swap_kind::none
             , hash_kind Hash = hash_kind::none
             >
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

template< int, eq_compare_kind EqComp = eq_compare_kind::none
             , less_compare_kind LessComp = less_compare_kind::none
             , swap_kind Swap = swap_kind::none
             , hash_kind Hash = hash_kind::none
             >
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


template< int V, eq_compare_kind EqComp, less_compare_kind LessComp
               , swap_kind Swap, hash_kind Hash
        >
constexpr int /*return type shouldn't matter*/
swap
( nontrivial_constructor_nontrivial_destructor
  < V, EqComp, LessComp, Swap, Hash >& lhs
, nontrivial_constructor_nontrivial_destructor
  < V, EqComp, LessComp, Swap, Hash >& rhs
)
noexcept( Swap == swap_kind::noexcept_ )
{
  auto old_lhs = lhs.value;
  lhs.value = rhs.value;
  rhs.value = old_lhs;
  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST
( test_discriminated_union_unary_construct_constexpr )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      discriminated_union_t const& const_un = un;

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
    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      discriminated_union_t const& const_un = un;

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

ARGOT_REGISTER_TEST( test_discriminated_union_unary_construct_not_constexpr )
{
  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< discriminated_union_t > );

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        discriminated_union_t un
        ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two ) );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        discriminated_union_t const& const_un = un;

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

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( Constructible< discriminated_union_t > );

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      {
        discriminated_union_t un
        ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two ) );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        discriminated_union_t const& const_un = un;

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

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST
( test_discriminated_union_unary_construct_constexpr_ilist )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un
      ( std::in_place_index< 0 >, { 3, 4, 5 }, zero, one, std::move( two ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un
      ( std::in_place_index< 0 >, { 3, 4, 5 }, zero, one, std::move( two ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST
( test_discriminated_union_unary_construct_not_constexpr_ilist )
{
  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      bool destroyed = false;

      {
        discriminated_union_t un
        ( std::in_place_index< 0 >, { 3, 4, 5 }, destroyed );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      bool destroyed = false;

      {
        discriminated_union_t un
        ( std::in_place_index< 0 >, { 3, 4, 5 }, destroyed );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_discriminated_union_unary_emplace )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un;

      decltype( auto ) res = un.emplace< 0 >( zero, one, std::move( two ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );

      int three = 3;
      int const four = 4;
      int five = 5;

      un.emplace< 0 >( three, four, std::move( five ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un;

      decltype( auto ) res = un.emplace< 0 >( zero, one, std::move( two ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );

      int three = 3;
      int const four = 4;
      int five = 5;

      un.emplace< 0 >( three, four, std::move( five ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
    }
  }

  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      bool other_destroyed = false;
      int three = 3;
      int const four = 4;
      int five = 5;

      {
        discriminated_union_t un;

        decltype( auto ) res
          = un.emplace< 0 >( destroyed, zero, one, std::move( two ) );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );

        ARGOT_TEST_FALSE( destroyed );

        un.emplace< 0 >( other_destroyed, three, four, std::move( five ) );

        ARGOT_TEST_TRUE( destroyed );

        ARGOT_TEST_FALSE( other_destroyed );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_TRUE( other_destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      bool other_destroyed = false;
      int three = 3;
      int const four = 4;
      int five = 5;

      {
        discriminated_union_t un;

        decltype( auto ) res
          = un.emplace< 0 >( destroyed, zero, one, std::move( two ) );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 3 );

        ARGOT_TEST_FALSE( destroyed );

        un.emplace< 0 >( other_destroyed, three, four, std::move( five ) );

        ARGOT_TEST_TRUE( destroyed );

        ARGOT_TEST_FALSE( other_destroyed );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );
      }

      ARGOT_TEST_TRUE( other_destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_discriminated_union_unary_emplace_ilist )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      int three = 3;
      int const four = 4;
      int five = 5;

      discriminated_union_t un;

      decltype( auto ) res
        = un.emplace< 0 >( { 3, 4, 5 }, zero, one, std::move( two ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );

      un.emplace< 0 >( { 6, 7, 8 }, three, four, std::move( five ) );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 33 );
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      int three = 3;
      int const four = 4;
      int five = 5;

      discriminated_union_t un;

      decltype( auto ) res
        = un.emplace< 0 >( { 3, 4, 5 }, zero, one, std::move( two ) );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 15 );

      un.emplace< 0 >( { 6, 7, 8 }, three, four, std::move( five ) );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 33 );
    }
  }

  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      bool destroyed = false;
      bool other_destroyed = false;

      {
        discriminated_union_t un;

        decltype( auto ) res = un.emplace< 0 >( { 3, 4, 5 }, destroyed );

        ARGOT_TEST_FALSE( destroyed );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );

        un.emplace< 0 >( { 6, 7, 8 }, other_destroyed );

        ARGOT_TEST_TRUE( destroyed );

        ARGOT_TEST_FALSE( other_destroyed );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 21 );
      }

      ARGOT_TEST_TRUE( other_destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      bool destroyed = false;
      bool other_destroyed = false;

      {
        discriminated_union_t un;

        decltype( auto ) res = un.emplace< 0 >( { 3, 4, 5 }, destroyed );

        ARGOT_TEST_FALSE( destroyed );

        ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

        ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), alt_t& > );

        ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &res );
        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 12 );

        un.emplace< 0 >( { 6, 7, 8 }, other_destroyed );

        ARGOT_TEST_TRUE( destroyed );

        ARGOT_TEST_FALSE( other_destroyed );

        ARGOT_TEST_EQ( union_traits::get< 0 >( un ).value, 21 );
      }

      ARGOT_TEST_TRUE( other_destroyed );
    }
  }

  return 0;
}

// TODO(mattcalabrese) Make this a constexpr test in C++20
ARGOT_REGISTER_TEST( test_discriminated_union_destroy_constexpr )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      un.destroy< 0 >();
    }
  }

  {
    using alt_t = nontrivial_constructor_trivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      un.destroy< 0 >();
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_discriminated_union_destroy_not_constexpr )
{
  {
    using alt_t = trivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un
      ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two ) );

      ARGOT_TEST_FALSE( destroyed );

      un.destroy< 0 >();

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  {
    using alt_t = nontrivial_constructor_nontrivial_destructor< 0 >;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      bool destroyed = false;
      int zero = 0;
      int const one = 1;
      int two = 2;

      discriminated_union_t un
      ( std::in_place_index< 0 >, destroyed, zero, one, std::move( two ) );

      ARGOT_TEST_FALSE( destroyed );

      un.destroy< 0 >();

      ARGOT_TEST_TRUE( destroyed );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_discriminated_union_reference )
{
  {
    using alt_t = int const&;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int const five = 5;
      int const ten = 10;

      discriminated_union_t un( std::in_place_index< 0 >, five );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &five );

      un = discriminated_union_t( std::in_place_index< 0 >, ten );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 10 );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &ten );

      un.destroy< 0 >();
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_discriminated_union_reference_emplace )
{
  {
    using alt_t = int const&;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      int const five = 5;

      discriminated_union_t un;
      decltype( auto ) emplace_result = un.emplace< 0 >( five );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_CONCEPT_ENSURE
      ( SameType< decltype( emplace_result ), int const& > );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );
      ARGOT_TEST_EQ( &emplace_result, &five );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un ), &five );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_discriminated_union_const )
{
  {
    using alt_t = int const;
    using discriminated_union_t = discriminated_union< alt_t >;

    {
      discriminated_union_t un( std::in_place_index< 0 >, 5 );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      decltype( auto ) assign_result = un.assign< 0 >( 5 );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_CONCEPT_ENSURE
      ( SameType< decltype( assign_result ), int const& > );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );

      un = discriminated_union_t( std::in_place_index< 0 >, 10 );

      ARGOT_TEST_EQ( variant_traits::index_of( un ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 10 );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_discriminated_union_unary_eq_compare )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( Not< EqualityComparable< discriminated_union_t > > );
    ARGOT_CONCEPT_ENSURE
    ( Not< InequalityComparable< discriminated_union_t > > );
  }

  {
    using alt_t
      = trivial_constructor_trivial_destructor
        < 0, eq_compare_kind::noexcept_ >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( EqualityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( InequalityComparable< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t const un_lhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_diff
      ( std::in_place_index< 0 >, three, one, std::move( two ) );

      // Self comparisons
      ARGOT_TEST_TRUE( un_lhs == un_lhs );
      ARGOT_TEST_TRUE( un_rhs == un_rhs );
      ARGOT_TEST_TRUE( un_diff == un_diff );

      // Practical comparisons
      ARGOT_TEST_TRUE( un_lhs == un_rhs );
      ARGOT_TEST_TRUE( un_rhs == un_lhs );
      ARGOT_TEST_FALSE( un_lhs == un_diff );
      ARGOT_TEST_FALSE( un_diff == un_lhs );

      // Not eq
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_TRUE( un_lhs != un_diff );

      ARGOT_TEST_TRUE( noexcept( un_lhs == un_lhs ) );
      ARGOT_TEST_TRUE( noexcept( un_lhs != un_lhs ) );
    }
  }

  {
    using alt_t
      = trivial_constructor_trivial_destructor
        < 0, eq_compare_kind::not_noexcept >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( EqualityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( InequalityComparable< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t const un_lhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_diff
      ( std::in_place_index< 0 >, three, one, std::move( two ) );

      // Self comparisons
      ARGOT_TEST_TRUE( un_lhs == un_lhs );
      ARGOT_TEST_TRUE( un_rhs == un_rhs );
      ARGOT_TEST_TRUE( un_diff == un_diff );

      // Practical comparisons
      ARGOT_TEST_TRUE( un_lhs == un_rhs );
      ARGOT_TEST_TRUE( un_rhs == un_lhs );
      ARGOT_TEST_FALSE( un_lhs == un_diff );
      ARGOT_TEST_FALSE( un_diff == un_lhs );

      // Not eq
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_TRUE( un_lhs != un_diff );

      ARGOT_TEST_FALSE( noexcept( un_lhs == un_lhs ) );
      ARGOT_TEST_FALSE( noexcept( un_lhs != un_lhs ) );
    }
  }

  {
    using alt_t
      = trivial_constructor_trivial_destructor
        < 0, eq_compare_kind::dubious >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( EqualityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( InequalityComparable< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t const un_lhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_diff
      ( std::in_place_index< 0 >, three, one, std::move( two ) );

      // Self comparisons
      ARGOT_TEST_TRUE( un_lhs == un_lhs );
      ARGOT_TEST_TRUE( un_rhs == un_rhs );
      ARGOT_TEST_TRUE( un_diff == un_diff );

      // Practical comparisons
      ARGOT_TEST_TRUE( un_lhs == un_rhs );
      ARGOT_TEST_TRUE( un_rhs == un_lhs );
      ARGOT_TEST_FALSE( un_lhs == un_diff );
      ARGOT_TEST_FALSE( un_diff == un_lhs );

      // Not eq
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_TRUE( un_lhs != un_diff );

      ARGOT_TEST_FALSE( noexcept( un_lhs == un_lhs ) );
      ARGOT_TEST_FALSE( noexcept( un_lhs != un_lhs ) );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_discriminated_union_unary_eq_compare_ref )
{
  {
    using alt_t = int&;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( EqualityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( InequalityComparable< discriminated_union_t > );

    {
      int zero = 0;
      int other_zero = 0;

      discriminated_union_t const un_lhs( std::in_place_index< 0 >, zero );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, zero );

      discriminated_union_t const un_diff
      ( std::in_place_index< 0 >, other_zero );

      // Self comparisons
      ARGOT_TEST_TRUE( un_lhs == un_lhs );
      ARGOT_TEST_TRUE( un_rhs == un_rhs );
      ARGOT_TEST_TRUE( un_diff == un_diff );

      // Practical comparisons
      ARGOT_TEST_TRUE( un_lhs == un_rhs );
      ARGOT_TEST_TRUE( un_rhs == un_lhs );
      ARGOT_TEST_FALSE( un_lhs == un_diff );
      ARGOT_TEST_FALSE( un_diff == un_lhs );

      // Not eq
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_TRUE( un_lhs != un_diff );

      ARGOT_TEST_TRUE( noexcept( un_lhs == un_lhs ) );
      ARGOT_TEST_TRUE( noexcept( un_lhs != un_lhs ) );
    }
  }

  {
    using alt_t = int&&;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( EqualityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( InequalityComparable< discriminated_union_t > );

    {
      int zero = 0;
      int other_zero = 0;

      discriminated_union_t const un_lhs
      ( std::in_place_index< 0 >, std::move( zero ) );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, std::move( zero ) );

      discriminated_union_t const un_diff
      ( std::in_place_index< 0 >, std::move( other_zero ) );

      // Self comparisons
      ARGOT_TEST_TRUE( un_lhs == un_lhs );
      ARGOT_TEST_TRUE( un_rhs == un_rhs );
      ARGOT_TEST_TRUE( un_diff == un_diff );

      // Practical comparisons
      ARGOT_TEST_TRUE( un_lhs == un_rhs );
      ARGOT_TEST_TRUE( un_rhs == un_lhs );
      ARGOT_TEST_FALSE( un_lhs == un_diff );
      ARGOT_TEST_FALSE( un_diff == un_lhs );

      // Not eq
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_TRUE( un_lhs != un_diff );

      ARGOT_TEST_TRUE( noexcept( un_lhs == un_lhs ) );
      ARGOT_TEST_TRUE( noexcept( un_lhs != un_lhs ) );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_discriminated_union_unary_less_compare )
{
  {
    using alt_t = trivial_constructor_trivial_destructor< 0 >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( Not< LessThanComparable< discriminated_union_t > > );
    ARGOT_CONCEPT_ENSURE( Not< LessEqualComparable< discriminated_union_t > > );
    ARGOT_CONCEPT_ENSURE
      ( Not< GreaterEqualComparable< discriminated_union_t > > );
    ARGOT_CONCEPT_ENSURE
    ( Not< GreaterThanComparable< discriminated_union_t > > );
  }

  {
    using alt_t
      = trivial_constructor_trivial_destructor
        < 0, eq_compare_kind::not_noexcept, less_compare_kind::noexcept_ >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( EqualityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( InequalityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( LessThanComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( LessEqualComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( GreaterEqualComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( GreaterThanComparable< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t const un_lhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_big
      ( std::in_place_index< 0 >, three, one, std::move( two ) );

      // Self comparisons
      ARGOT_TEST_TRUE( un_lhs == un_lhs );
      ARGOT_TEST_TRUE( un_rhs == un_rhs );
      ARGOT_TEST_TRUE( un_big == un_big );
      ARGOT_TEST_FALSE( un_lhs != un_lhs );
      ARGOT_TEST_FALSE( un_rhs != un_rhs );
      ARGOT_TEST_FALSE( un_big != un_big );
      ARGOT_TEST_FALSE( un_lhs < un_lhs );
      ARGOT_TEST_FALSE( un_rhs < un_rhs );
      ARGOT_TEST_FALSE( un_big < un_big );
      ARGOT_TEST_TRUE( un_lhs <= un_lhs );
      ARGOT_TEST_TRUE( un_rhs <= un_rhs );
      ARGOT_TEST_TRUE( un_big <= un_big );
      ARGOT_TEST_TRUE( un_lhs >= un_lhs );
      ARGOT_TEST_TRUE( un_rhs >= un_rhs );
      ARGOT_TEST_TRUE( un_big >= un_big );
      ARGOT_TEST_FALSE( un_lhs > un_lhs );
      ARGOT_TEST_FALSE( un_rhs > un_rhs );
      ARGOT_TEST_FALSE( un_big > un_big );

      // Practical comparisons
      ARGOT_TEST_TRUE( un_lhs == un_rhs );
      ARGOT_TEST_TRUE( un_rhs == un_lhs );
      ARGOT_TEST_FALSE( un_lhs == un_big );
      ARGOT_TEST_FALSE( un_big == un_lhs );
      ARGOT_TEST_FALSE( un_rhs == un_big );
      ARGOT_TEST_FALSE( un_big == un_rhs );
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_FALSE( un_rhs != un_lhs );
      ARGOT_TEST_TRUE( un_lhs != un_big );
      ARGOT_TEST_TRUE( un_big != un_lhs );
      ARGOT_TEST_TRUE( un_rhs != un_big );
      ARGOT_TEST_TRUE( un_big != un_rhs );
      ARGOT_TEST_FALSE( un_lhs < un_rhs );
      ARGOT_TEST_FALSE( un_rhs < un_lhs );
      ARGOT_TEST_TRUE( un_lhs < un_big );
      ARGOT_TEST_FALSE( un_big < un_lhs );
      ARGOT_TEST_TRUE( un_lhs <= un_rhs );
      ARGOT_TEST_TRUE( un_rhs <= un_lhs );
      ARGOT_TEST_TRUE( un_lhs <= un_big );
      ARGOT_TEST_FALSE( un_big <= un_lhs );
      ARGOT_TEST_TRUE( un_lhs >= un_rhs );
      ARGOT_TEST_TRUE( un_rhs >= un_lhs );
      ARGOT_TEST_FALSE( un_lhs >= un_big );
      ARGOT_TEST_TRUE( un_big >= un_lhs );
      ARGOT_TEST_FALSE( un_lhs > un_rhs );
      ARGOT_TEST_FALSE( un_rhs > un_lhs );
      ARGOT_TEST_FALSE( un_lhs > un_big );
      ARGOT_TEST_TRUE( un_big > un_lhs );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowEqualityComparable< discriminated_union_t > > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowInequalityComparable< discriminated_union_t > > );

      ARGOT_CONCEPT_ENSURE
      ( NothrowLessThanComparable< discriminated_union_t > );

      ARGOT_CONCEPT_ENSURE
      ( NothrowLessEqualComparable< discriminated_union_t > );

      ARGOT_CONCEPT_ENSURE
      ( NothrowGreaterThanComparable< discriminated_union_t > );

      ARGOT_CONCEPT_ENSURE
      ( NothrowGreaterEqualComparable< discriminated_union_t > );
    }
  }

  {
    using alt_t
      = trivial_constructor_trivial_destructor
        < 0, eq_compare_kind::noexcept_, less_compare_kind::not_noexcept >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( EqualityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( InequalityComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( LessThanComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( LessEqualComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( GreaterEqualComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( GreaterThanComparable< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t const un_lhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_big
      ( std::in_place_index< 0 >, three, one, std::move( two ) );

      // Self comparisons
      ARGOT_TEST_TRUE( un_lhs == un_lhs );
      ARGOT_TEST_TRUE( un_rhs == un_rhs );
      ARGOT_TEST_TRUE( un_big == un_big );
      ARGOT_TEST_FALSE( un_lhs != un_lhs );
      ARGOT_TEST_FALSE( un_rhs != un_rhs );
      ARGOT_TEST_FALSE( un_big != un_big );
      ARGOT_TEST_FALSE( un_lhs < un_lhs );
      ARGOT_TEST_FALSE( un_rhs < un_rhs );
      ARGOT_TEST_FALSE( un_big < un_big );
      ARGOT_TEST_TRUE( un_lhs <= un_lhs );
      ARGOT_TEST_TRUE( un_rhs <= un_rhs );
      ARGOT_TEST_TRUE( un_big <= un_big );
      ARGOT_TEST_TRUE( un_lhs >= un_lhs );
      ARGOT_TEST_TRUE( un_rhs >= un_rhs );
      ARGOT_TEST_TRUE( un_big >= un_big );
      ARGOT_TEST_FALSE( un_lhs > un_lhs );
      ARGOT_TEST_FALSE( un_rhs > un_rhs );
      ARGOT_TEST_FALSE( un_big > un_big );

      // Practical comparisons
      ARGOT_TEST_TRUE( un_lhs == un_rhs );
      ARGOT_TEST_TRUE( un_rhs == un_lhs );
      ARGOT_TEST_FALSE( un_lhs == un_big );
      ARGOT_TEST_FALSE( un_big == un_lhs );
      ARGOT_TEST_FALSE( un_rhs == un_big );
      ARGOT_TEST_FALSE( un_big == un_rhs );
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_FALSE( un_rhs != un_lhs );
      ARGOT_TEST_TRUE( un_lhs != un_big );
      ARGOT_TEST_TRUE( un_big != un_lhs );
      ARGOT_TEST_TRUE( un_rhs != un_big );
      ARGOT_TEST_TRUE( un_big != un_rhs );
      ARGOT_TEST_FALSE( un_lhs < un_rhs );
      ARGOT_TEST_FALSE( un_rhs < un_lhs );
      ARGOT_TEST_TRUE( un_lhs < un_big );
      ARGOT_TEST_FALSE( un_big < un_lhs );
      ARGOT_TEST_TRUE( un_lhs <= un_rhs );
      ARGOT_TEST_TRUE( un_rhs <= un_lhs );
      ARGOT_TEST_TRUE( un_lhs <= un_big );
      ARGOT_TEST_FALSE( un_big <= un_lhs );
      ARGOT_TEST_TRUE( un_lhs >= un_rhs );
      ARGOT_TEST_TRUE( un_rhs >= un_lhs );
      ARGOT_TEST_FALSE( un_lhs >= un_big );
      ARGOT_TEST_TRUE( un_big >= un_lhs );
      ARGOT_TEST_FALSE( un_lhs > un_rhs );
      ARGOT_TEST_FALSE( un_rhs > un_lhs );
      ARGOT_TEST_FALSE( un_lhs > un_big );
      ARGOT_TEST_TRUE( un_big > un_lhs );

      ARGOT_CONCEPT_ENSURE
      ( NothrowEqualityComparable< discriminated_union_t > );

      ARGOT_CONCEPT_ENSURE
      ( NothrowInequalityComparable< discriminated_union_t > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowLessThanComparable< discriminated_union_t > > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowLessEqualComparable< discriminated_union_t > > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowGreaterThanComparable< discriminated_union_t > > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowGreaterEqualComparable< discriminated_union_t > > );
    }
  }

  {
    using alt_t
      = trivial_constructor_trivial_destructor
        < 0, eq_compare_kind::noexcept_, less_compare_kind::dubious >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( LessThanComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( LessEqualComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( GreaterEqualComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( GreaterThanComparable< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t const un_lhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t const un_big
      ( std::in_place_index< 0 >, three, one, std::move( two ) );

      // Self comparisons
      ARGOT_TEST_TRUE( un_lhs == un_lhs );
      ARGOT_TEST_TRUE( un_rhs == un_rhs );
      ARGOT_TEST_TRUE( un_big == un_big );
      ARGOT_TEST_FALSE( un_lhs != un_lhs );
      ARGOT_TEST_FALSE( un_rhs != un_rhs );
      ARGOT_TEST_FALSE( un_big != un_big );
      ARGOT_TEST_FALSE( un_lhs < un_lhs );
      ARGOT_TEST_FALSE( un_rhs < un_rhs );
      ARGOT_TEST_FALSE( un_big < un_big );
      ARGOT_TEST_TRUE( un_lhs <= un_lhs );
      ARGOT_TEST_TRUE( un_rhs <= un_rhs );
      ARGOT_TEST_TRUE( un_big <= un_big );
      ARGOT_TEST_TRUE( un_lhs >= un_lhs );
      ARGOT_TEST_TRUE( un_rhs >= un_rhs );
      ARGOT_TEST_TRUE( un_big >= un_big );
      ARGOT_TEST_FALSE( un_lhs > un_lhs );
      ARGOT_TEST_FALSE( un_rhs > un_rhs );
      ARGOT_TEST_FALSE( un_big > un_big );

      // Practical comparisons
      ARGOT_TEST_TRUE( un_lhs == un_rhs );
      ARGOT_TEST_TRUE( un_rhs == un_lhs );
      ARGOT_TEST_FALSE( un_lhs == un_big );
      ARGOT_TEST_FALSE( un_big == un_lhs );
      ARGOT_TEST_FALSE( un_rhs == un_big );
      ARGOT_TEST_FALSE( un_big == un_rhs );
      ARGOT_TEST_FALSE( un_lhs != un_rhs );
      ARGOT_TEST_FALSE( un_rhs != un_lhs );
      ARGOT_TEST_TRUE( un_lhs != un_big );
      ARGOT_TEST_TRUE( un_big != un_lhs );
      ARGOT_TEST_TRUE( un_rhs != un_big );
      ARGOT_TEST_TRUE( un_big != un_rhs );
      ARGOT_TEST_FALSE( un_lhs < un_rhs );
      ARGOT_TEST_FALSE( un_rhs < un_lhs );
      ARGOT_TEST_TRUE( un_lhs < un_big );
      ARGOT_TEST_FALSE( un_big < un_lhs );
      ARGOT_TEST_TRUE( un_lhs <= un_rhs );
      ARGOT_TEST_TRUE( un_rhs <= un_lhs );
      ARGOT_TEST_TRUE( un_lhs <= un_big );
      ARGOT_TEST_FALSE( un_big <= un_lhs );
      ARGOT_TEST_TRUE( un_lhs >= un_rhs );
      ARGOT_TEST_TRUE( un_rhs >= un_lhs );
      ARGOT_TEST_FALSE( un_lhs >= un_big );
      ARGOT_TEST_TRUE( un_big >= un_lhs );
      ARGOT_TEST_FALSE( un_lhs > un_rhs );
      ARGOT_TEST_FALSE( un_rhs > un_lhs );
      ARGOT_TEST_FALSE( un_lhs > un_big );
      ARGOT_TEST_TRUE( un_big > un_lhs );

      ARGOT_CONCEPT_ENSURE
      ( NothrowEqualityComparable< discriminated_union_t > );

      ARGOT_CONCEPT_ENSURE
      ( NothrowInequalityComparable< discriminated_union_t > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowLessThanComparable< discriminated_union_t > > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowLessEqualComparable< discriminated_union_t > > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowGreaterThanComparable< discriminated_union_t > > );

      ARGOT_CONCEPT_ENSURE
      ( Not< NothrowGreaterEqualComparable< discriminated_union_t > > );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_discriminated_union_unary_less_compare_ref )
{
  {
    using alt_t = int&;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_CONCEPT_ENSURE( LessThanComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( LessEqualComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( GreaterEqualComparable< discriminated_union_t > );
    ARGOT_CONCEPT_ENSURE( GreaterThanComparable< discriminated_union_t > );

    {
      int zeros[ 2 ] = { 0, 0 };

      discriminated_union_t const un_lhs
      ( std::in_place_index< 0 >, zeros[ 0 ] );

      discriminated_union_t const un_rhs
      ( std::in_place_index< 0 >, zeros[ 0 ] );

      discriminated_union_t const un_big
      ( std::in_place_index< 0 >, zeros[ 1 ] );

      // Self comparisons
      ARGOT_TEST_FALSE( un_lhs < un_lhs );
      ARGOT_TEST_FALSE( un_rhs < un_rhs );
      ARGOT_TEST_FALSE( un_big < un_big );
      ARGOT_TEST_TRUE( un_lhs <= un_lhs );
      ARGOT_TEST_TRUE( un_rhs <= un_rhs );
      ARGOT_TEST_TRUE( un_big <= un_big );
      ARGOT_TEST_TRUE( un_lhs >= un_lhs );
      ARGOT_TEST_TRUE( un_rhs >= un_rhs );
      ARGOT_TEST_TRUE( un_big >= un_big );
      ARGOT_TEST_FALSE( un_lhs > un_lhs );
      ARGOT_TEST_FALSE( un_rhs > un_rhs );
      ARGOT_TEST_FALSE( un_big > un_big );

      // Practical comparisons
      ARGOT_TEST_FALSE( un_lhs < un_rhs );
      ARGOT_TEST_FALSE( un_rhs < un_lhs );
      ARGOT_TEST_TRUE( un_lhs < un_big );
      ARGOT_TEST_FALSE( un_big < un_lhs );
      ARGOT_TEST_TRUE( un_lhs <= un_rhs );
      ARGOT_TEST_TRUE( un_rhs <= un_lhs );
      ARGOT_TEST_TRUE( un_lhs <= un_big );
      ARGOT_TEST_FALSE( un_big <= un_lhs );
      ARGOT_TEST_TRUE( un_lhs >= un_rhs );
      ARGOT_TEST_TRUE( un_rhs >= un_lhs );
      ARGOT_TEST_FALSE( un_lhs >= un_big );
      ARGOT_TEST_TRUE( un_big >= un_lhs );
      ARGOT_TEST_FALSE( un_lhs > un_rhs );
      ARGOT_TEST_FALSE( un_rhs > un_lhs );
      ARGOT_TEST_FALSE( un_lhs > un_big );
      ARGOT_TEST_TRUE( un_big > un_lhs );

      ARGOT_TEST_TRUE( noexcept( un_lhs < un_lhs ) );
      ARGOT_TEST_TRUE( noexcept( un_lhs <= un_lhs ) );
      ARGOT_TEST_TRUE( noexcept( un_lhs >= un_lhs ) );
      ARGOT_TEST_TRUE( noexcept( un_lhs > un_lhs ) );
    }
  }

  return 0;
}

// TODO(mattcalabrese) Test odd constraint combinations
ARGOT_REGISTER_CONSTEXPR_TEST( test_discriminated_union_unary_swap_trivial )
{
  {
    using alt_t
      = trivial_constructor_trivial_destructor
        < 0, eq_compare_kind::none, less_compare_kind::none
        , swap_kind::noexcept_
        >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_TEST_TRUE( std::is_swappable_v< discriminated_union_t > );
    ARGOT_TEST_TRUE( std::is_nothrow_swappable_v< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t un_lhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t un_rhs
      ( std::in_place_index< 0 >, three, one, std::move( two ) );

      swap( un_lhs, un_rhs );

      ARGOT_TEST_EQ( variant_traits::index_of( un_lhs ), 0 );
      ARGOT_TEST_EQ( variant_traits::index_of( un_rhs ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un_lhs ).value, 6 );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un_rhs ).value, 3 );
    }
  }

  {
    using alt_t
      = trivial_constructor_trivial_destructor
        < 0, eq_compare_kind::none, less_compare_kind::none
        , swap_kind::not_noexcept
        >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_TEST_TRUE( std::is_swappable_v< discriminated_union_t > );
    ARGOT_TEST_FALSE( std::is_nothrow_swappable_v< discriminated_union_t > );

    {
      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t un_lhs
      ( std::in_place_index< 0 >, zero, one, std::move( two ) );

      discriminated_union_t un_rhs
      ( std::in_place_index< 0 >, three, one, std::move( two ) );

      swap( un_lhs, un_rhs );

      ARGOT_TEST_EQ( variant_traits::index_of( un_lhs ), 0 );
      ARGOT_TEST_EQ( variant_traits::index_of( un_rhs ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un_lhs ).value, 6 );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un_rhs ).value, 3 );
    }
  }

  return 0;
}

// TODO(mattcalabrese) Test odd constraint combinations
ARGOT_REGISTER_TEST( test_discriminated_union_unary_swap_nontrivial )
{
  {
    using alt_t
      = nontrivial_constructor_nontrivial_destructor
        < 0, eq_compare_kind::none, less_compare_kind::none
        , swap_kind::noexcept_
        >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_TEST_TRUE( std::is_swappable_v< discriminated_union_t > );
    ARGOT_TEST_TRUE( std::is_nothrow_swappable_v< discriminated_union_t > );

    {
      bool lhs_destroyed = false;
      bool rhs_destroyed = false;

      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t un_lhs
      ( std::in_place_index< 0 >, lhs_destroyed, zero, one, std::move( two ) );

      discriminated_union_t un_rhs
      ( std::in_place_index< 0 >, rhs_destroyed, three, one, std::move( two ) );

      swap( un_lhs, un_rhs );

      ARGOT_TEST_EQ( variant_traits::index_of( un_lhs ), 0 );
      ARGOT_TEST_EQ( variant_traits::index_of( un_rhs ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un_lhs ).value, 6 );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un_rhs ).value, 3 );
    }
  }

  {
    using alt_t
      = nontrivial_constructor_nontrivial_destructor
        < 0, eq_compare_kind::none, less_compare_kind::none
        , swap_kind::not_noexcept
        >;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_TEST_TRUE( std::is_swappable_v< discriminated_union_t > );
    ARGOT_TEST_FALSE( std::is_nothrow_swappable_v< discriminated_union_t > );

    {
      bool lhs_destroyed = false;
      bool rhs_destroyed = false;

      int zero = 0;
      int const one = 1;
      int two = 2;
      int three = 3;

      discriminated_union_t un_lhs
      ( std::in_place_index< 0 >, lhs_destroyed, zero, one, std::move( two ) );

      discriminated_union_t un_rhs
      ( std::in_place_index< 0 >, rhs_destroyed, three, one, std::move( two ) );

      swap( un_lhs, un_rhs );

      ARGOT_TEST_EQ( variant_traits::index_of( un_lhs ), 0 );
      ARGOT_TEST_EQ( variant_traits::index_of( un_rhs ), 0 );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un_lhs ).value, 6 );
      ARGOT_TEST_EQ( union_traits::get< 0 >( un_rhs ).value, 3 );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_discriminated_union_unary_swap_ref )
{
  {
    using alt_t = int const&;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_TEST_TRUE( std::is_swappable_v< discriminated_union_t > );
    ARGOT_TEST_TRUE( std::is_nothrow_swappable_v< discriminated_union_t > );

    {
      int zero = 0;
      int other_zero = 0;

      discriminated_union_t un_lhs( std::in_place_index< 0 >, zero );

      discriminated_union_t un_rhs( std::in_place_index< 0 >, other_zero );

      swap( un_lhs, un_rhs );

      ARGOT_TEST_EQ( variant_traits::index_of( un_lhs ), 0 );
      ARGOT_TEST_EQ( variant_traits::index_of( un_rhs ), 0 );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un_lhs ), &other_zero );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un_rhs ), &zero );
    }
  }

  {
    using alt_t = int&&;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_TEST_TRUE( std::is_swappable_v< discriminated_union_t > );
    ARGOT_TEST_TRUE( std::is_nothrow_swappable_v< discriminated_union_t > );

    {
      int zero = 0;
      int other_zero = 0;

      discriminated_union_t un_lhs
      ( std::in_place_index< 0 >, std::move( zero ) );

      discriminated_union_t un_rhs
      ( std::in_place_index< 0 >, std::move( other_zero ) );

      swap( un_lhs, un_rhs );

      ARGOT_TEST_EQ( variant_traits::index_of( un_lhs ), 0 );
      ARGOT_TEST_EQ( variant_traits::index_of( un_rhs ), 0 );

      ARGOT_TEST_EQ( &union_traits::get< 0 >( un_lhs ), &other_zero );
      ARGOT_TEST_EQ( &union_traits::get< 0 >( un_rhs ), &zero );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_discriminated_union_unary_swap_void )
{
  {
    using alt_t = void_;

    using discriminated_union_t = discriminated_union< alt_t >;

    ARGOT_TEST_TRUE( std::is_swappable_v< discriminated_union_t > );
    ARGOT_TEST_TRUE( std::is_nothrow_swappable_v< discriminated_union_t > );
    ARGOT_TEST_TRUE( std::is_nothrow_swappable_v< void_ > );

    {
      discriminated_union_t un_lhs( std::in_place_index< 0 >, void_() );

      discriminated_union_t un_rhs( std::in_place_index< 0 >, void_() );

      swap( un_lhs, un_rhs );

      ARGOT_TEST_EQ( variant_traits::index_of( un_lhs ), 0 );
      ARGOT_TEST_EQ( variant_traits::index_of( un_rhs ), 0 );
    }
  }

  return 0;
}

template< class AlternativeProfile, class ExpectedUnionProfile >
constexpr ::argot::call_detail::constexpr_block_result_t
test_discriminated_union_of_archetype_regularity()
{
  using arch = argot_test::regularity_archetype< AlternativeProfile >;

  using un = discriminated_union< arch >;

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

ARGOT_REGISTER_TEST( test_discriminated_union_regularity )
{
  using argot_test::combine_regularity_profiles_t;

  ARGOT_TEST_SUCCESS
  ( test_discriminated_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::exceptional_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::exceptional_destructor_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_discriminated_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::trivial_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_move_constructor_profile
      , argot_test::trivial_copy_constructor_profile
      , argot_test::nothrow_move_assign_profile
      , argot_test::nothrow_copy_assign_profile
      , argot_test::trivial_destructor_profile
      , argot_test::nothrow_swap_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_discriminated_union_of_archetype_regularity
    < combine_regularity_profiles_t
      < argot_test::no_default_constructor_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::exceptional_destructor_profile
      >
    , combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::trivial_move_assign_profile
      , argot_test::trivial_copy_assign_profile
      , argot_test::exceptional_destructor_profile
      >
    >()
  );

  ARGOT_TEST_SUCCESS
  ( test_discriminated_union_of_archetype_regularity
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
  ( test_discriminated_union_of_archetype_regularity
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
  ( test_discriminated_union_of_archetype_regularity
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
  ( test_discriminated_union_of_archetype_regularity
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

// TODO(mattcalabrese) Test assign and hash

// TODO(mattcalabrese) Exception-test

ARGOT_EXECUTE_TESTS();

}  // namespace
