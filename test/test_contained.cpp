/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/contained.hpp>

#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>

namespace {

// TODO(mattcalabrese) Test noexcept/constexpr

enum class dummy_state { valid, moved_from };

template< class Os >
constexpr Os& operator <<( Os& os, dummy_state val )
{
  switch( val )
  {
   case dummy_state::valid:
    os << "valid";
    break;
   case dummy_state::moved_from:
    os << "moved_from";
    break;
  }
  return os;
}

struct dummy
{
  constexpr dummy( int const value ) noexcept
    : value( value ), state( dummy_state::valid ){};

  constexpr dummy( dummy&& other ) noexcept
    : value( other.value ), state( other.state )
  {
    other.state = dummy_state::moved_from;
    other.value = 0;
  }

  constexpr dummy( const dummy& other ) noexcept
    : value( other.value ), state( other.state )
  {
  }

  int value;
  dummy_state state;
};

using argot::SameType;

using argot::contained;
using argot::make_contained;
using argot::access_contained;

ARGOT_REGISTER_CONSTEXPR_TEST( test_contained_unqualified )
{
  using contained_t = contained< dummy >;

  dummy source( 5 );

  // Test construct by copy.
  contained_t object = make_contained< dummy >( source );
  ARGOT_TEST_EQ( source.state, dummy_state::valid );
  ARGOT_TEST_EQ( source.value, 5 );

  // Test construct by move.
  {
    contained_t object = make_contained< dummy >( std::move( source ) );
    (void)object;
    ARGOT_TEST_EQ( source.state, dummy_state::moved_from );
    ARGOT_TEST_EQ( source.value, 0 );
  }

  // lvalue
  {
    contained_t& self = object;
    decltype( auto ) accessed_value = access_contained( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // const lvalue
  {
    contained_t const& self = object;
    decltype( auto ) accessed_value = access_contained( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, const dummy& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // rvalue
  {
    contained_t&& self = std::move( object );
    decltype( auto ) accessed_value = access_contained( std::move( self ) );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy&& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // copy
  {
    contained_t copied_object = object;
    dummy& source_value = access_contained( object );
    dummy& copied_value = access_contained( copied_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( copied_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( copied_value.value, 5 );
  }

  // move
  {
    contained_t moved_object = std::move( object );
    dummy& source_value = access_contained( object );
    dummy& moved_value = access_contained( moved_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::moved_from );
    ARGOT_TEST_EQ( source_value.value, 0 );
    ARGOT_TEST_EQ( moved_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( moved_value.value, 5 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_contained_const )
{
  using contained_t = contained< dummy const >;

  dummy source( 5 );

  // Test construct by copy.
  contained_t object = make_contained< dummy const >( source );
  ARGOT_TEST_EQ( source.state, dummy_state::valid );
  ARGOT_TEST_EQ( source.value, 5 );

  // Test construct by move.
  {
    contained_t moved_in_object
      = make_contained< dummy const >( std::move( source ) );
    (void)moved_in_object; // TODO(mattcalabrese) test new value.
    ARGOT_TEST_EQ( source.state, dummy_state::moved_from );
    ARGOT_TEST_EQ( source.value, 0 );
  }

  // lvalue
  {
    contained_t& self = object;
    decltype( auto ) accessed_value = access_contained( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, const dummy& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // const lvalue
  {
    contained_t const& self = object;
    decltype( auto ) accessed_value = access_contained( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, const dummy& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // rvalue
  {
    contained_t&& self = std::move( object );
    decltype( auto ) accessed_value = access_contained( std::move( self ) );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy&& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // copy
  {
    contained_t copied_object = object;
    dummy const& source_value = access_contained( object );
    dummy const& copied_value = access_contained( copied_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( copied_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( copied_value.value, 5 );
  }

  // move
  {
    contained_t moved_object = std::move( object );
    dummy const& source_value = access_contained( object );
    dummy const& moved_value = access_contained( moved_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::moved_from );
    ARGOT_TEST_EQ( source_value.value, 0 );
    ARGOT_TEST_EQ( moved_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( moved_value.value, 5 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_contained_lvalue_reference )
{
  using contained_t = contained< dummy& >;

  dummy source( 5 );

  // Test construct.
  contained_t object = make_contained< dummy& >( source );
  ARGOT_TEST_EQ( source.state, dummy_state::valid );
  ARGOT_TEST_EQ( source.value, 5 );

  // lvalue
  {
    contained_t& self = object;
    decltype( auto ) accessed_value = access_contained( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // const lvalue
  {
    contained_t const& self = object;
    decltype( auto ) accessed_value = access_contained( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // rvalue
  {
    contained_t&& self = std::move( object );
    decltype( auto ) accessed_value = access_contained( std::move( self ) );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // copy
  {
    contained_t copied_object = object;
    dummy& source_value = access_contained( object );
    dummy& copied_value = access_contained( copied_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( copied_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( copied_value.value, 5 );
  }

  // move
  {
    contained_t moved_object = std::move( object );
    dummy& source_value = access_contained( object );
    dummy& moved_value = access_contained( moved_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( moved_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( moved_value.value, 5 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_contained_rvalue_reference )
{
  using contained_t = contained< dummy&& >;

  dummy source( 5 );

  // Test construct.
  contained_t object = make_contained< dummy&& >( std::move( source ) );
  ARGOT_TEST_EQ( source.state, dummy_state::valid );
  ARGOT_TEST_EQ( source.value, 5 );

  // lvalue
  {
    contained_t& self = object;
    decltype( auto ) accessed_value = access_contained( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // const lvalue
  {
    contained_t const& self = object;
    decltype( auto ) accessed_value = access_contained( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // rvalue
  {
    contained_t&& self = std::move( object );
    decltype( auto ) accessed_value = access_contained( std::move( self ) );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy&& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // copy
  static_assert( !std::is_copy_constructible< contained_t >::value );

  // move
  {
    contained_t moved_object = std::move( object );
    dummy& source_value = access_contained( object );
    dummy& moved_value = access_contained( moved_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( moved_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( moved_value.value, 5 );
  }

  return 0;
}

// TODO(mattcalabrese) Test "volatile" and "volatile const"

ARGOT_EXECUTE_TESTS();

} // namespace
