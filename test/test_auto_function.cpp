/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/detail/auto_function.hpp>

#include <type_traits>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

constexpr
ARGOT_DETAIL_AUTO_FUNCTION( nondependent_noexcept( short a, short b ) )
{
  return a + b
)

BOOST_AUTO_TEST_CASE( test_nondependent_noexcept )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType<int, decltype( nondependent_noexcept( 1, 2 ) ) >
  , "Auto function failed return type deduction."
  );

  static_assert
  ( noexcept( nondependent_noexcept( 1, 2 ) )
  , "Auto function failed noexcept check."
  );

  static_assert
  ( nondependent_noexcept( 1, 2 ) == 3
  , "Auto function failed to return the correct result."
  );
}

int add( short a, short b )
{
  return a + b;
}

ARGOT_DETAIL_AUTO_FUNCTION( nondependent( short a, short b ) )
{
  return add( a, b )
)

BOOST_AUTO_TEST_CASE( test_nondependent )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType<int, decltype( nondependent( 1, 2 ) ) >
  , "Auto function failed return type deduction."
  );

  static_assert
  ( !noexcept( nondependent( 1, 2 ) )
  , "Auto function failed noexcept check."
  );

  BOOST_TEST( nondependent( 1, 2 ) == 3 );
}

constexpr
ARGOT_DETAIL_AUTO_FUNCTION_DECLARATION
( nondependent_noexcept_decl( short a, short b ) )
{
  return b - a
)
{
  return a + b;
}

BOOST_AUTO_TEST_CASE( test_nondependent_noexcept_decl )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType<int, decltype( nondependent_noexcept_decl( 1, 2 ) ) >
  , "Auto function failed return type deduction."
  );

  static_assert
  ( noexcept( nondependent_noexcept_decl( 1, 2 ) )
  , "Auto function failed noexcept check."
  );

  static_assert
  ( nondependent_noexcept_decl( 1, 2 ) == 3
  , "Auto function failed to return the correct result."
  );
}

int sub( short a, short b )
{
  return a - b;
}

ARGOT_DETAIL_AUTO_FUNCTION_DECLARATION
( nondependent_decl( short a, short b ) )
{
  return sub( a, b )
)
{
  return a + b;
}

BOOST_AUTO_TEST_CASE( test_nondependent_decl )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType<int, decltype( nondependent_decl( 1, 2 ) ) >
  , "Auto function failed return type deduction."
  );

  static_assert
  ( !noexcept( nondependent_decl( 1, 2 ) )
  , "Auto function failed noexcept check."
  );

  BOOST_TEST( nondependent_decl( 1, 2 ) == 3 );
}

// TODO(mattcalabrese) Test the void versions
