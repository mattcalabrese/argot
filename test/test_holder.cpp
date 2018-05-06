/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/holder.hpp>
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

using argot::call_detail::holder;
using argot::call_detail::access_holder;
using argot::call_detail::holder_state;
using argot::call_detail::make_holder_type_tag;
using argot::call_detail::make_holder;

ARGOT_REGISTER_CONSTEXPR_TEST( test_holder_unqualified )
{
  using holder_type = holder< dummy >;

  dummy source( 5 );

  // Test construct by copy.
  holder_type object = make_holder< dummy >( source );
  ARGOT_TEST_EQ( source.state, dummy_state::valid );
  ARGOT_TEST_EQ( source.value, 5 );

  // Test construct by move.
  {
    holder_type object = make_holder< dummy >( std::move( source ) );
    (void)object;
    ARGOT_TEST_EQ( source.state, dummy_state::moved_from );
    ARGOT_TEST_EQ( source.value, 0 );
  }

  // lvalue
  {
    holder_type& self = object;
    decltype( auto ) accessed_value = ( access_holder )( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // const lvalue
  {
    holder_type const& self = object;
    decltype( auto ) accessed_value = ( access_holder )( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, const dummy& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // rvalue
  {
    holder_type&& self = std::move( object );
    decltype( auto ) accessed_value = ( access_holder )( std::move( self ) );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy&& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // copy
  {
    holder_type copied_object = object;
    dummy& source_value = ( access_holder )( object );
    dummy& copied_value = ( access_holder )( copied_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( copied_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( copied_value.value, 5 );
  }

  // move
  {
    holder_type moved_object = std::move( object );
    dummy& source_value = ( access_holder )( object );
    dummy& moved_value = ( access_holder )( moved_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::moved_from );
    ARGOT_TEST_EQ( source_value.value, 0 );
    ARGOT_TEST_EQ( moved_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( moved_value.value, 5 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_holder_const )
{
  using holder_type = holder< dummy const >;

  dummy source( 5 );

  // Test construct by copy.
  holder_type object( make_holder_type_tag(), source );
  ARGOT_TEST_EQ( source.state, dummy_state::valid );
  ARGOT_TEST_EQ( source.value, 5 );

  // Test construct by move.
  {
    holder_type moved_in_object( make_holder_type_tag(), std::move( source ) );
    ARGOT_TEST_EQ( source.state, dummy_state::moved_from );
    ARGOT_TEST_EQ( source.value, 0 );
  }

  // lvalue
  {
    holder_type& self = object;
    decltype( auto ) accessed_value = ( access_holder )( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, const dummy& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // const lvalue
  {
    holder_type const& self = object;
    decltype( auto ) accessed_value = ( access_holder )( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, const dummy& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // rvalue
  {
    holder_type&& self = std::move( object );
    decltype( auto ) accessed_value = ( access_holder )( std::move( self ) );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy&& > );

    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // copy
  {
    holder_type copied_object = object;
    dummy const& source_value = ( access_holder )( object );
    dummy const& copied_value = ( access_holder )( copied_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( copied_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( copied_value.value, 5 );
  }

  // move
  {
    holder_type moved_object = std::move( object );
    dummy const& source_value = ( access_holder )( object );
    dummy const& moved_value = ( access_holder )( moved_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::moved_from );
    ARGOT_TEST_EQ( source_value.value, 0 );
    ARGOT_TEST_EQ( moved_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( moved_value.value, 5 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_holder_lvalue_reference )
{
  using holder_type = holder< dummy& >;

  dummy source( 5 );

  // Test construct.
  holder_type object( make_holder_type_tag(), source );
  ARGOT_TEST_EQ( source.state, dummy_state::valid );
  ARGOT_TEST_EQ( source.value, 5 );

  // lvalue
  {
    holder_type& self = object;
    decltype( auto ) accessed_value = ( access_holder )( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // const lvalue
  {
    holder_type const& self = object;
    decltype( auto ) accessed_value = ( access_holder )( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // rvalue
  {
    holder_type&& self = std::move( object );
    decltype( auto ) accessed_value = ( access_holder )( std::move( self ) );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // copy
  {
    holder_type copied_object = object;
    dummy& source_value = ( access_holder )( object );
    dummy& copied_value = ( access_holder )( copied_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( copied_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( copied_value.value, 5 );
  }

  // move
  {
    holder_type moved_object = std::move( object );
    dummy& source_value = ( access_holder )( object );
    dummy& moved_value = ( access_holder )( moved_object );
    ARGOT_TEST_EQ( source_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( source_value.value, 5 );
    ARGOT_TEST_EQ( moved_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( moved_value.value, 5 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_holder_rvalue_reference )
{
  using holder_type = holder< dummy&& >;

  dummy source( 5 );

  // Test construct.
  holder_type object( make_holder_type_tag(), std::move( source ) );
  ARGOT_TEST_EQ( source.state, dummy_state::valid );
  ARGOT_TEST_EQ( source.value, 5 );

  static_assert
  ( !std::is_constructible< holder_type, make_holder_type_tag, dummy& >::value );

  // lvalue
  {
    holder_type& self = object;
    decltype( auto ) accessed_value = ( access_holder )( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // const lvalue
  {
    holder_type const& self = object;
    decltype( auto ) accessed_value = ( access_holder )( self );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // rvalue
  {
    holder_type&& self = std::move( object );
    decltype( auto ) accessed_value = ( access_holder )( std::move( self ) );

    using accessed_type = decltype( accessed_value );
    ARGOT_CONCEPT_ENSURE( SameType< accessed_type, dummy&& > );

    ARGOT_TEST_EQ( &accessed_value, &source );
    ARGOT_TEST_EQ( accessed_value.state, dummy_state::valid );
    ARGOT_TEST_EQ( accessed_value.value, 5 );
  }

  // copy
  static_assert( !std::is_copy_constructible< holder_type >::value );

  // move
  {
    holder_type moved_object = std::move( object );
    dummy& source_value = ( access_holder )( object );
    dummy& moved_value = ( access_holder )( moved_object );
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
