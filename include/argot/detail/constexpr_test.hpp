/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONSTEXPR_TEST_HPP_
#define ARGOT_DETAIL_CONSTEXPR_TEST_HPP_

#include <argot/detail/constexpr_test_utilities.hpp>

#include <cstddef>
#include <stdexcept>

#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/stringize.hpp>

// TODO(mattcalabrese) Remove, require user to do this.
ARGOT_DETAIL_DECLARE_CONSTEXPR_TESTS();

namespace {

void argot_test_main();

}  // namespace

int main()
{
  argot_test_main();
}

// TODO(mattcalabrese) Do this with a lambda so that tests are still executed if
//                     not constexr, rather than being a build failure.
#define ARGOT_DETAIL_REGISTER_TEST_IMPL( name, constexpr_test )                \
template< class = void >                                                       \
struct name                                                                    \
{                                                                              \
  static BOOST_PP_EXPR_IIF( constexpr_test, constexpr ) void run()             \
  {                                                                            \
    ::argot::call_detail::constexpr_block_result_t const result = argot_test();\
                                                                               \
    if( result.error != nullptr )                                              \
      throw ::argot::call_detail::incorrect_constexpr_test_result              \
      ( result.error );                                                        \
                                                                               \
    BOOST_PP_EXPR_IIF                                                          \
    ( constexpr_test                                                           \
    , if constexpr                                                             \
      ( !::argot::call_detail::test_can_run_at_compile_time< name >( 0 ) )     \
        throw ::argot::call_detail::cannot_be_executed_at_compile_time         \
        ( BOOST_PP_STRINGIZE( __FILE__ ) ":"                                   \
          BOOST_PP_STRINGIZE( __LINE__ ) ": "                                  \
          "The test \"" #name "\" is not able to be constexpr."                \
        );                                                                     \
    )                                                                          \
  }                                                                            \
                                                                               \
  static BOOST_PP_EXPR_IIF( constexpr_test, constexpr )                        \
  ::argot::call_detail::constexpr_block_result_t argot_test();                 \
};                                                                             \
                                                                               \
ARGOT_DETAIL_ADD_TEST_TO_LIST( name );                                         \
                                                                               \
template< class ArgotDetailTestDummy >                                         \
BOOST_PP_EXPR_IIF( constexpr_test, constexpr )                                 \
::argot::call_detail::constexpr_block_result_t                                 \
name< ArgotDetailTestDummy >::argot_test()

#define ARGOT_REGISTER_TEST( name )                                            \
ARGOT_DETAIL_REGISTER_TEST_IMPL( name, 0 )

#define ARGOT_REGISTER_CONSTEXPR_TEST( name )                                  \
ARGOT_DETAIL_REGISTER_TEST_IMPL( name, 1 )

#define ARGOT_EXECUTE_TESTS()                                                  \
void argot_test_main()                                                         \
{                                                                              \
  using test_list = ARGOT_DETAIL_GET_CONSTEXPR_TESTS();                        \
  ::argot::call_detail::execute_all_constexpr_tests_impl< test_list >::run();  \
}                                                                              \
                                                                               \
constexpr ::argot::call_detail::post_execution_test_list<> get_tests           \
( ::argot::call_detail::test_id<> )                                            \
{                                                                              \
  return {};                                                                   \
}                                                                              \
                                                                               \
static_assert( ( get_tests )( ::argot::call_detail::test_id<>{} ).true_ )

#endif // ARGOT_DETAIL_CONSTEXPR_TEST_HPP_
