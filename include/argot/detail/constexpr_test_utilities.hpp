/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONSTEXPR_TEST_UTILITIES_HPP_
#define ARGOT_DETAIL_CONSTEXPR_TEST_UTILITIES_HPP_

#include <cstddef>
#include <stdexcept>

#include <boost/preprocessor/stringize.hpp>

namespace argot {
namespace call_detail {

// TODO(mattcalabrese) Verify that the test sare added all in the same
// namespace, otherwise tests can be silently ignored!

inline constexpr unsigned max_tests = 254;

template< std::size_t V = max_tests + 1 >
struct test_id : test_id< V - 1 > { static constexpr std::size_t value = V; };

template<>
struct test_id< 0 > { static constexpr std::size_t value = 0; };

template<>
struct test_id< max_tests >
  : test_id< max_tests - 1 >
{
 private:
  // NOTE: This is intentionally private. If this value is accessed then it
  //       means the maximum amount of tests was exceeded.
  static constexpr std::size_t value = max_tests - 1;
};

template< class... T >
struct test_list
{
  static constexpr std::size_t size = sizeof...( T );

  template< class U >
  using append_test = test_list< T..., U >;

  static_assert
  ( sizeof...( T ) <= max_tests
  , "Attempted to register a test after exceeding the maximum amount of tests."
  );
};

template< class T >
struct always_false : std::false_type {};

template< class T = void >
struct post_execution_test_list;

template< class T >
struct assert_late_registration
{
  using type = post_execution_test_list<>;

  // TODO(mattcalabrese) Make this work even when max tests is exceeded.
  static_assert
  ( always_false< T >::value
  , "Attempted to register a test after invoking ARGOT_EXECUTE_TESTS()."
  );
};

template< class >
struct post_execution_test_list
{
  static constexpr std::size_t size = 0;

  template< class U >
  using append_test = typename assert_late_registration< U >::type;

  static constexpr bool true_ = true;
};

#define ARGOT_DETAIL_DECLARE_CONSTEXPR_TESTS()                                 \
::argot::call_detail::test_list<>                                              \
get_tests( ::argot::call_detail::test_id< 0 > )

#define ARGOT_DETAIL_GET_CONSTEXPR_TESTS()                                     \
decltype( ( get_tests )( ::argot::call_detail::test_id<>{} ) )

#define ARGOT_DETAIL_ADD_TEST_TO_LIST( name )                                  \
template< class = name<> >                                                     \
ARGOT_DETAIL_GET_CONSTEXPR_TESTS()::append_test< name<> > get_tests            \
( ::argot::call_detail::test_id                                                \
  < ARGOT_DETAIL_GET_CONSTEXPR_TESTS()::size + 1 >                             \
)

struct constexpr_block_result_t
{
  constexpr constexpr_block_result_t( int error_code ) noexcept
    : error( error_code ? "Test returned failure." : nullptr ) {}
  explicit constexpr constexpr_block_result_t( char const* const e ) noexcept
    : error( e ) {}

  constexpr explicit operator bool() const noexcept { return error == nullptr; }

  char const* error = nullptr;
};

class incorrect_constexpr_test_result
  : public std::exception
{
 public:
  explicit incorrect_constexpr_test_result( char const* error ) noexcept
    : error( error ) {}
  char const* what() const noexcept { return error; }
 private:
  char const* error;
};

class cannot_be_executed_at_compile_time
  : public std::exception
{
 public:
  explicit cannot_be_executed_at_compile_time( char const* error ) noexcept
    : error( error ) {}
  char const* what() const noexcept { return error; }
 private:
  char const* error;
};

template< bool >
using bool_ = bool;

template< class TestHolder >
constexpr bool_<((void)TestHolder::argot_test(), true)>
test_can_run_at_compile_time( int ) { return true; }

template< class TestHolder >
constexpr bool test_can_run_at_compile_time( ... ) { return false; }

template< class TestList >
struct execute_all_constexpr_tests_impl;

template< class... TestHolders >
struct execute_all_constexpr_tests_impl< test_list< TestHolders... > >
{
  static void run()
  {
    (TestHolders::run(), ...);
  }
};

}  // namespace argot::call_detail
}  // namespace argot

#define ARGOT_TEST_FAIL( message )                                             \
  return ::argot::call_detail::constexpr_block_result_t                        \
  ( BOOST_PP_STRINGIZE( __FILE__ ) ":"                                         \
    BOOST_PP_STRINGIZE( __LINE__ ) ": "                                        \
    message                                                                    \
  )

#define ARGOT_TEST_TRUE( expr )                                                \
  if( expr ) {} else {                                                         \
    ARGOT_TEST_FAIL                                                            \
    ( "Expected true but was false: "                                          \
      BOOST_PP_STRINGIZE( expr )                                               \
    );                                                                         \
  }

#define ARGOT_TEST_FALSE( expr )                                               \
  if( expr ) {                                                                 \
    ARGOT_TEST_FAIL                                                            \
    ( "expected false but was true: "                                          \
      BOOST_PP_STRINGIZE( expr )                                               \
    );                                                                         \
  } else {}

// TODO(mattcalabrese) When value can be output, include values here.
#define ARGOT_TEST_REL( rel, lhs, rhs )                                        \
  if( lhs rel rhs ) {} else {                                                  \
    ARGOT_TEST_FAIL                                                            \
    ( "check failed: "                                                         \
      BOOST_PP_STRINGIZE( lhs )                                                \
      " " BOOST_PP_STRINGIZE( rel ) " "                                        \
      BOOST_PP_STRINGIZE( rhs )                                                \
    );                                                                         \
  }

// TODO(mattcalabrese) When value can be output, include values here.
#define ARGOT_TEST_FAIL_REL( rel, lhs, rhs )                                   \
  if( lhs rel rhs ) {                                                          \
    ARGOT_TEST_FAIL                                                            \
    ( "check succeeded when failure was expected: "                            \
      BOOST_PP_STRINGIZE( lhs )                                                \
      " " BOOST_PP_STRINGIZE( rel ) " "                                        \
      BOOST_PP_STRINGIZE( rhs )                                                \
    );                                                                         \
  } else {}

#define ARGOT_TEST_EQ( lhs, rhs ) ARGOT_TEST_REL( ==, lhs, rhs )

#define ARGOT_TEST_NE( lhs, rhs ) ARGOT_TEST_REL( !=, lhs, rhs )

#define ARGOT_TEST_LT( lhs, rhs ) ARGOT_TEST_REL( <, lhs, rhs )

#define ARGOT_TEST_LE( lhs, rhs ) ARGOT_TEST_REL( <=, lhs, rhs )

#define ARGOT_TEST_GE( lhs, rhs ) ARGOT_TEST_REL( >=, lhs, rhs )

#define ARGOT_TEST_GT( lhs, rhs ) ARGOT_TEST_REL( >, lhs, rhs )

#define ARGOT_TEST_FAIL_EQ( lhs, rhs ) ARGOT_TEST_FAIL_REL( ==, lhs, rhs )

#define ARGOT_TEST_FAIL_NE( lhs, rhs ) ARGOT_TEST_FAIL_REL( !=, lhs, rhs )

#define ARGOT_TEST_FAIL_LT( lhs, rhs ) ARGOT_TEST_FAIL_REL( <, lhs, rhs )

#define ARGOT_TEST_FAIL_LE( lhs, rhs ) ARGOT_TEST_FAIL_REL( <=, lhs, rhs )

#define ARGOT_TEST_FAIL_GE( lhs, rhs ) ARGOT_TEST_FAIL_REL( >=, lhs, rhs )

#define ARGOT_TEST_FAIL_GT( lhs, rhs ) ARGOT_TEST_FAIL_REL( >, lhs, rhs )

#define ARGOT_TEST_SUCCESS( ... )                                              \
  if( ::argot::call_detail::constexpr_block_result_t cached_result             \
        = __VA_ARGS__                                                          \
    ) {} else { return cached_result; }

#endif // ARGOT_DETAIL_CONSTEXPR_TEST_HPP_
