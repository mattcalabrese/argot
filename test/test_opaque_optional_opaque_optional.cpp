/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/opaque_optional/opaque_optional.hpp>

#include <argot/concepts/optional_like.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/constexpr_test_utilities.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/opt_traits/get.hpp>
#include <argot/opt_traits/has_value.hpp>

#include "regularity_facilities.hpp"
#include "regularity_testing.hpp"

#include <type_traits>
#include <utility>

namespace {

using argot::opaque_optional;

#if defined( __cpp_constinit )
#define REQUIRE_CONSTANT_INITIALIZATION constinit
#elif __has_cpp_attribute( require_constant_initialization )
#define REQUIRE_CONSTANT_INITIALIZATION [[require_constant_initialization]]
#else
#define REQUIRE_CONSTANT_INITIALIZATION
#endif

REQUIRE_CONSTANT_INITIALIZATION [[maybe_unused]]
opaque_optional< int > constexpr_nullptr;

// Using this prevents warnings about moving temporaries with std::move.
template< class T >
constexpr std::remove_reference_t< T >&&
silenced_warning_move( T&& arg )
{
  return std::move( arg );
}

REQUIRE_CONSTANT_INITIALIZATION [[maybe_unused]]
opaque_optional< int > constexpr_nullptr_move_target
  = ( silenced_warning_move )( opaque_optional< int >() );

struct array4_and_int
{
  explicit array4_and_int( std::initializer_list< int > ilist, int mem )
    noexcept
    : additional_member( mem )
  {
    std::copy( ilist.begin(), ilist.end(), std::begin( array_data ) );
  }

  array4_and_int() = delete;
  array4_and_int( array4_and_int const& ) = delete;
  array4_and_int& operator =( array4_and_int const& ) = delete;

  int array_data[4];
  int additional_member;
};

bool operator ==( array4_and_int const& lhs, array4_and_int const& rhs )
{
  return    std::equal( std::begin( lhs.array_data ), std::end( lhs.array_data )
                      , std::begin( rhs.array_data )
                      )
         && lhs.additional_member == rhs.additional_member;
}

struct delayed_complete_type;
using force_instantiation [[maybe_unused]]
  = std::integral_constant
    < std::size_t
    , sizeof( opaque_optional< delayed_complete_type > )
    >;

struct delayed_complete_type
{
  delayed_complete_type() = default;
  explicit delayed_complete_type( int const value ) : value( value ) {}
  int value;
};

struct dubious_bool
{
  operator bool() const { return value; }
  bool value;
};

dubious_bool operator ==(delayed_complete_type lhs, delayed_complete_type rhs)
noexcept
{
  return { lhs.value == rhs.value };
}

dubious_bool operator <(delayed_complete_type lhs, delayed_complete_type rhs)
noexcept
{
  return { lhs.value < rhs.value };
}

void function_to_decay() {}

ARGOT_REGISTER_TEST( test_opaque_optional_complete )
{
  using opt = opaque_optional< int >;

  using prof
    = argot_test::combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::nothrow_move_constructor_profile
      , argot_test::nothrow_move_assign_profile
      , argot_test::nothrow_destructor_profile
      , argot_test::nothrow_equality_profile
      , argot_test::nothrow_inequality_profile
      , argot_test::nothrow_less_than_profile
      , argot_test::nothrow_less_equal_profile
      , argot_test::nothrow_greater_equal_profile
      , argot_test::nothrow_greater_than_profile
      , argot_test::nothrow_swap_profile
      , argot_test::nothrow_hash_profile
      >;

  ARGOT_TEST_SUCCESS
  ( argot_test::test_regularity< opt, prof >
    ( []{ return opt(); }
    , []{ return opt( std::in_place, 0 ); }
    , []{ return opt( std::in_place, 1 ); }
    )
  );

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_default_constructor )
{
  opaque_optional< int > const empty;
  ARGOT_TEST_FALSE( empty.has_value() );

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_in_place_constructor_no_ilist )
{
  {
    opaque_optional< int > const obj( std::in_place );
    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, 0 );
  }

  {
    opaque_optional< int > const obj( std::in_place, 5 );
    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, 5 );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_in_place_constructor_ilist )
{
  opaque_optional< array4_and_int > const obj
  ( std::in_place, { 1, 2, 3, 4 }, 5 );

  ARGOT_TEST_TRUE( obj.has_value() );
  ARGOT_TEST_EQ( *obj, array4_and_int( { 1, 2, 3, 4 }, 5 ) );

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_in_place_with_result_constructor )
{
  opaque_optional< int > const
    obj( argot::in_place_with_result, []{ return 5; } );

  ARGOT_TEST_TRUE( obj.has_value() );
  ARGOT_TEST_EQ( *obj, 5 );

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_in_place_default_init_constructor )
{
  opaque_optional< int > const obj( argot::in_place_default_init );
  ARGOT_TEST_TRUE( obj.has_value() );

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_dereference )
{
  {
    opaque_optional< int > obj( std::in_place, 5 );
    decltype( auto ) res = *obj;
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int& > );

    res = 10;
    ARGOT_TEST_EQ( &*obj, &res );
    ARGOT_TEST_EQ( *obj, 10 );
  }

  {
    opaque_optional< int > const obj( std::in_place, 5 );
    decltype( auto ) res = *obj;
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int const& > );

    ARGOT_TEST_EQ( &*obj, &res );
  }

  {
    opaque_optional< int > obj( std::in_place, 5 );
    decltype( auto ) res = *std::move( obj );
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int&& > );

    res = 10;
    ARGOT_TEST_EQ( &*obj, &res );
    ARGOT_TEST_EQ( *obj, 10 );
  }

  {
    opaque_optional< int > const obj( std::in_place, 5 );
    decltype( auto ) res = *std::move( obj );
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int const&& > );

    ARGOT_TEST_EQ( &*obj, &res );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_arrow )
{
  {
    opaque_optional< int > obj( std::in_place, 5 );
    decltype( auto ) res = obj.operator->();
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int* > );

    *res = 10;
    ARGOT_TEST_EQ( &*obj, res );
    ARGOT_TEST_EQ( *obj, 10 );
  }

  {
    opaque_optional< int > const obj( std::in_place, 5 );
    decltype( auto ) res = obj.operator->();
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int const* > );

    ARGOT_TEST_EQ( &*obj, res );
  }

  {
    opaque_optional< int > obj( std::in_place, 5 );
    decltype( auto ) res = std::move( obj ).operator->();
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int* > );

    *res = 10;
    ARGOT_TEST_EQ( &*obj, res );
    ARGOT_TEST_EQ( *obj, 10 );
  }

  {
    opaque_optional< int > const obj( std::in_place, 5 );
    decltype( auto ) res = std::move( obj ).operator->();
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int const* > );

    ARGOT_TEST_EQ( &*obj, res );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_member_swap )
{
  struct immovable
  {
    explicit immovable( int value ) : value( value ) {}

    immovable( immovable&& other ) = delete;
    immovable& operator=( immovable&& other ) = delete;

    int value;
  };

  {
    opaque_optional< immovable > lhs;
    opaque_optional< immovable > rhs;

    lhs.swap( rhs );

    ARGOT_TEST_FALSE( lhs.has_value() );
    ARGOT_TEST_FALSE( rhs.has_value() );
    ARGOT_TEST_TRUE( noexcept( lhs.swap( rhs ) ) );
  }

  {
    opaque_optional< immovable > lhs( std::in_place, 5 );
    opaque_optional< immovable > rhs;

    lhs.swap( rhs );

    ARGOT_TEST_FALSE( lhs.has_value() );
    ARGOT_TEST_TRUE( rhs.has_value() );
    ARGOT_TEST_EQ( rhs->value, 5 );
  }

  {
    opaque_optional< immovable > lhs;
    opaque_optional< immovable > rhs( std::in_place, 5 );

    lhs.swap( rhs );

    ARGOT_TEST_TRUE( lhs.has_value() );
    ARGOT_TEST_EQ( lhs->value, 5 );
    ARGOT_TEST_FALSE( rhs.has_value() );
  }

  {
    opaque_optional< immovable > lhs( std::in_place, 5 );
    opaque_optional< immovable > rhs( std::in_place, 10 );

    lhs.swap( rhs );

    ARGOT_TEST_TRUE( lhs.has_value() );
    ARGOT_TEST_EQ( lhs->value, 10 );
    ARGOT_TEST_TRUE( rhs.has_value() );
    ARGOT_TEST_EQ( rhs->value, 5 );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_delayed_completeness )
{
  using opt = opaque_optional< delayed_complete_type >;

  using prof
    = argot_test::combine_regularity_profiles_t
      < argot_test::nothrow_default_constructor_profile
      , argot_test::nothrow_move_constructor_profile
      , argot_test::nothrow_move_assign_profile
      , argot_test::nothrow_destructor_profile
      , argot_test::exceptional_equality_profile
      , argot_test::exceptional_inequality_profile
      , argot_test::exceptional_less_than_profile
      , argot_test::exceptional_less_equal_profile
      , argot_test::exceptional_greater_equal_profile
      , argot_test::exceptional_greater_than_profile
      , argot_test::nothrow_swap_profile
      >;

  ARGOT_TEST_SUCCESS
  ( argot_test::test_regularity< opt, prof >
    ( []{ return opt(); }
    , []{ return opt( std::in_place, 0 ); }
    , []{ return opt( std::in_place, 1 ); }
    )
  );

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_has_value )
{
  opaque_optional< int > const empty;
  opaque_optional< int > const not_empty( std::in_place );

  ARGOT_TEST_FALSE( empty.has_value() );
  ARGOT_TEST_TRUE( not_empty.has_value() );

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_reset )
{
  opaque_optional< int > initially_not_empty( std::in_place );
  initially_not_empty.reset();

  ARGOT_TEST_FALSE( initially_not_empty.has_value() );

  return 0;
}

struct move_only_no_assign
{
  explicit move_only_no_assign( int value ) : value( value ) {}
  move_only_no_assign( move_only_no_assign&& ) = default;
  move_only_no_assign& operator=( move_only_no_assign const& ) = delete;
  int value;
};

bool
operator ==( move_only_no_assign const& lhs, move_only_no_assign const& rhs )
{
  return lhs.value == rhs.value;
}

struct copyable_no_assign
{
  explicit copyable_no_assign( int value ) : value( value ) {}
  copyable_no_assign( const copyable_no_assign& ) = default;
  copyable_no_assign& operator=( copyable_no_assign const& ) = delete;
  int value;
};

bool operator ==( copyable_no_assign const& lhs, copyable_no_assign const& rhs )
{
  return lhs.value == rhs.value;
}

ARGOT_REGISTER_TEST( test_opaque_optional_emplace_no_ilist )
{
  {
    opaque_optional< move_only_no_assign >
      initially_not_empty( std::in_place, 0 );

    initially_not_empty.emplace( 5 );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< move_only_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< move_only_no_assign >
      initially_not_empty( std::in_place, 0 );

    initially_not_empty.emplace
    ( move_only_no_assign( 5 ) );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< move_only_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< move_only_no_assign > initially_empty;
    initially_empty.emplace( 5 );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< move_only_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< move_only_no_assign > initially_empty;
    initially_empty.emplace
    ( move_only_no_assign( 5 ) );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< move_only_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< copyable_no_assign >
      initially_not_empty( std::in_place, 0 );

    copyable_no_assign source( 5 );
    initially_not_empty.emplace( source );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< copyable_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< copyable_no_assign > initially_empty;

    copyable_no_assign source( 5 );
    initially_empty.emplace( source );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< copyable_no_assign >( std::in_place, 5 )
    );
  }
  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_emplace_ilist )
{
  {
    opaque_optional< array4_and_int >
      initially_not_empty( std::in_place, { 6, 7, 8, 9, 10 }, 11 );
    initially_not_empty.emplace( { 1, 2, 3, 4 }, 5 );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< array4_and_int >( std::in_place, { 1, 2, 3, 4 }, 5 )
    );
  }

  {
    opaque_optional< array4_and_int > initially_empty;
    initially_empty.emplace( { 1, 2, 3, 4 }, 5 );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< array4_and_int >( std::in_place, { 1, 2, 3, 4 }, 5 )
    );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_emplace_with_result )
{
  {
    opaque_optional< int >
      initially_not_empty( std::in_place, 0 );

    initially_not_empty.emplace_with_result( []{ return 5; } );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< int >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< int > initially_empty;
    initially_empty.emplace_with_result( []{ return 5; } );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< int >( std::in_place, 5 )
    );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_emplace_default_init )
{
  {
    opaque_optional< int >
      initially_not_empty( std::in_place, 0 );

    initially_not_empty.emplace_default_init();
    ARGOT_TEST_TRUE( initially_not_empty.has_value() );
  }

  {
    opaque_optional< int > initially_empty;
    initially_empty.emplace_default_init();

    ARGOT_TEST_TRUE( initially_empty.has_value() );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_assign_rvalue )
{
  {
    opaque_optional< int >
      initially_not_empty( std::in_place, 0 );

    initially_not_empty.assign( 5 );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< int >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< int > initially_empty;
    initially_empty.assign( 5 );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< int >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< move_only_no_assign >
      initially_not_empty( std::in_place, 0 );

    initially_not_empty.assign
    ( move_only_no_assign( 5 ) );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< move_only_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< move_only_no_assign > initially_empty;
    initially_empty.assign
    ( move_only_no_assign( 5 ) );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< move_only_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< copyable_no_assign >
      initially_not_empty( std::in_place, 0 );

    initially_not_empty.assign
    ( copyable_no_assign( 5 ) );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< copyable_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< copyable_no_assign > initially_empty;
    initially_empty.assign
    ( copyable_no_assign( 5 ) );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< copyable_no_assign >( std::in_place, 5 )
    );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_assign_lvalue )
{
  {
    opaque_optional< int >
      initially_not_empty( std::in_place, 0 );

    int const source = 5;
    initially_not_empty.assign( source );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< int >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< int > initially_empty;

    int const source = 5;
    initially_empty.assign( source );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< int >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< copyable_no_assign >
      initially_not_empty( std::in_place, 0 );

    copyable_no_assign const source( 5 );
    initially_not_empty.assign( source );

    ARGOT_TEST_EQ
    ( initially_not_empty
    , opaque_optional< copyable_no_assign >( std::in_place, 5 )
    );
  }

  {
    opaque_optional< copyable_no_assign > initially_empty;

    copyable_no_assign const source( 5 );
    initially_empty.assign( source );

    ARGOT_TEST_EQ
    ( initially_empty
    , opaque_optional< copyable_no_assign >( std::in_place, 5 )
    );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_make_opaque_optional_in_place_default_init )
{
  decltype( auto ) obj = argot::make_opaque_optional_default_init< int >();
  ARGOT_CONCEPT_ENSURE
  ( argot::SameType< decltype( obj )
                   , opaque_optional< int >
                   >
  );

  ARGOT_TEST_TRUE( obj.has_value() );

  return 0;
}

ARGOT_REGISTER_TEST( test_make_opaque_optional_deduced )
{
  {
    decltype( auto ) obj = argot::make_opaque_optional( 5 );
    ARGOT_CONCEPT_ENSURE
    ( argot::SameType< decltype( obj )
                     , opaque_optional< int >
                     >
    );

    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, 5 );
  }

  {
    int const array[5] = { 1, 2, 3, 4, 5 };
    decltype( auto ) obj = argot::make_opaque_optional( array );
    ARGOT_CONCEPT_ENSURE
    ( argot::SameType< decltype( obj )
                     , opaque_optional< int const* >
                     >
    );

    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, &array[0] );
  }

  {
    decltype( auto ) obj = argot::make_opaque_optional( function_to_decay );
    ARGOT_CONCEPT_ENSURE
    ( argot::SameType< decltype( obj )
                     , opaque_optional< void (*)() >
                     >
    );

    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, &function_to_decay );
  }

  {
    struct move_only
    {
      explicit move_only( int v ) : value( v ) {}
      move_only( move_only&& ) = default;
      move_only( move_only const& ) = delete;
      move_only& operator=( move_only&& ) = default;
      move_only& operator=( move_only const& ) = delete;
      int value;
    };

    decltype( auto ) obj = argot::make_opaque_optional( move_only( 5 ) );
    ARGOT_CONCEPT_ENSURE
    ( argot::SameType< decltype( obj )
                     , opaque_optional< move_only >
                     >
    );

    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( obj->value, 5 );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_make_opaque_optional_no_ilist )
{
  {
    decltype( auto ) obj = argot::make_opaque_optional< int >();
    ARGOT_CONCEPT_ENSURE
    ( argot::SameType< decltype( obj )
                     , opaque_optional< int >
                     >
    );

    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, 0 );
  }

  {
    decltype( auto ) obj = argot::make_opaque_optional< int >( 5 );
    ARGOT_CONCEPT_ENSURE
    ( argot::SameType< decltype( obj )
                     , opaque_optional< int >
                     >
    );

    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, 5 );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_make_opaque_optional_ilist )
{
  decltype( auto ) obj
    = argot::make_opaque_optional< array4_and_int >( { 1, 2, 3, 4 }, 5 );
  ARGOT_CONCEPT_ENSURE
  ( argot::SameType< decltype( obj )
                   , opaque_optional< array4_and_int >
                   >
  );

  ARGOT_TEST_TRUE( obj.has_value() );
  ARGOT_TEST_EQ( *obj, array4_and_int( { 1, 2, 3, 4 }, 5 ) );

  return 0;
}

ARGOT_REGISTER_TEST( test_make_opaque_optional_with_result )
{
  {
    decltype( auto ) obj
      = argot::make_opaque_optional_with_result( []{ return 5; } );
    ARGOT_CONCEPT_ENSURE
    ( argot::SameType< decltype( obj )
                     , opaque_optional< int >
                     >
    );

    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, 5 );
  }

  {
    decltype( auto ) obj
      = argot::make_opaque_optional_with_result< int >( []{ return 5; } );
    ARGOT_CONCEPT_ENSURE
    ( argot::SameType< decltype( obj )
                     , opaque_optional< int >
                     >
    );

    ARGOT_TEST_TRUE( obj.has_value() );
    ARGOT_TEST_EQ( *obj, 5 );
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_opaque_optional_optional_like )
{
  ARGOT_TEST_TRUE
  ( ARGOT_IS_MODELED( argot::OptionalLike< opaque_optional< int > > ) );

  namespace opt_traits = argot::opt_traits;

  {
    opaque_optional< int > const obj;
    ARGOT_TEST_FALSE( opt_traits::has_value( obj ) );
  }

  {
    opaque_optional< int > const obj( std::in_place );
    ARGOT_TEST_TRUE( opt_traits::has_value( obj ) );
    ARGOT_TEST_TRUE( noexcept( opt_traits::has_value( obj ) ) );
  }

  {
    opaque_optional< int > obj( std::in_place, 5 );
    decltype( auto ) res = opt_traits::get( obj );
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int& > );

    res = 10;
    ARGOT_TEST_EQ( &*obj, &res );
    ARGOT_TEST_EQ( *obj, 10 );
    ARGOT_TEST_TRUE( noexcept( opt_traits::get( obj ) ) );
  }

  {
    opaque_optional< int > const obj( std::in_place, 5 );
    decltype( auto ) res = opt_traits::get( obj );
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int const& > );

    ARGOT_TEST_EQ( &*obj, &res );
    ARGOT_TEST_TRUE( noexcept( opt_traits::get( obj ) ) );
  }

  {
    opaque_optional< int > obj( std::in_place, 5 );
    decltype( auto ) res = opt_traits::get( std::move( obj ) );
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int&& > );

    res = 10;
    ARGOT_TEST_EQ( &*obj, &res );
    ARGOT_TEST_EQ( *obj, 10 );
    ARGOT_TEST_TRUE( noexcept( opt_traits::get( std::move( obj ) ) ) );
  }

  {
    opaque_optional< int > const obj( std::in_place, 5 );
    decltype( auto ) res = opt_traits::get( std::move( obj ) );
    ARGOT_CONCEPT_ENSURE( argot::SameType< decltype( res ), int const&& > );

    ARGOT_TEST_EQ( &*obj, &res );
    ARGOT_TEST_TRUE( noexcept( opt_traits::get( std::move( obj ) ) ) );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
