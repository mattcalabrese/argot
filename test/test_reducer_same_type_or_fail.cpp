/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/return_value_reducer_of.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>
#include <argot/reducer/same_type_or_fail.hpp>
#include <argot/reducer_traits/reduce.hpp>
#include <argot/reducer_traits/return_types.hpp>

namespace {

namespace reducer = argot::reducer;
namespace reducer_traits = argot::reducer_traits;

using reducer::same_type_or_fail;
using reducer::same_type_or_fail_t;
using reducer_traits::reduce;
using reducer_traits::return_types;
using argot::Not;
using argot::ReturnValueReducer;
using argot::ReturnValueReducerOf;
using argot::SameType;

struct udt {};

ARGOT_CONCEPT_ENSURE( ReturnValueReducer< same_type_or_fail_t > );

using reducer_type = decltype( same_type_or_fail );

ARGOT_CONCEPT_ENSURE( SameType< reducer_type, same_type_or_fail_t const > );

int const v = 42;

struct int_fun_t
{
  int_fun_t() = default;
  int_fun_t( int_fun_t const& ) = delete;
  int_fun_t& operator =( int_fun_t const& ) = delete;

  constexpr int const&& operator ()() && { return std::move( v ); }
};

struct void_fun_t
{
  void_fun_t() = default;
  void_fun_t( void_fun_t const& ) = delete;
  void_fun_t& operator =( void_fun_t const& ) = delete;

  constexpr void operator ()() && { value = 42; }

  int value = 0;
};

ARGOT_REGISTER_CONSTEXPR_TEST( test_same_type_or_fail_reduce_unary )
{
  ARGOT_CONCEPT_ENSURE( ReturnValueReducerOf< same_type_or_fail_t, void > );
  ARGOT_CONCEPT_ENSURE( ReturnValueReducerOf< same_type_or_fail_t, int > );
  ARGOT_CONCEPT_ENSURE( ReturnValueReducerOf< same_type_or_fail_t, int& > );
  ARGOT_CONCEPT_ENSURE( ReturnValueReducerOf< same_type_or_fail_t, udt > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int() > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int[3] > > );

  {
    decltype( auto ) result
      = reduce
        ( same_type_or_fail, return_types<>, return_types<>
        , int_fun_t()
        );

    ARGOT_CONCEPT_ENSURE( SameType< decltype( result ), int const&& > );
    ARGOT_TEST_EQ( &result, &v );
    ARGOT_TEST_EQ( result, 42 );
  }

  {
    void_fun_t fun;
    ARGOT_TEST_EQ( fun.value, 0 );

    using result_type
      = decltype
        ( reduce
          ( same_type_or_fail, return_types<>, return_types<>
          , std::move( fun )
          )
        );

    reduce
    ( same_type_or_fail, return_types<>, return_types<>
    , std::move( fun )
    );

    ARGOT_CONCEPT_ENSURE( SameType< result_type, void > );
    ARGOT_TEST_EQ( fun.value, 42 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_same_type_or_fail_reduce_binary )
{
  ARGOT_CONCEPT_ENSURE
  ( ReturnValueReducerOf< same_type_or_fail_t, void, void > );

  ARGOT_CONCEPT_ENSURE
  ( ReturnValueReducerOf< same_type_or_fail_t, int, int > );

  ARGOT_CONCEPT_ENSURE
  ( ReturnValueReducerOf< same_type_or_fail_t, int&, int& > );

  ARGOT_CONCEPT_ENSURE
  ( ReturnValueReducerOf< same_type_or_fail_t, udt, udt > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, void, int > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int&, int&& > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int, int&& > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, udt, udt const > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int(), int() > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int[3], int[3] > > );

  {
    decltype( auto ) result
      = reduce
        ( same_type_or_fail, return_types<>, return_types< int const&& >
        , int_fun_t()
        );

    ARGOT_CONCEPT_ENSURE( SameType< decltype( result ), int const&& > );
    ARGOT_TEST_EQ( &result, &v );
    ARGOT_TEST_EQ( result, 42 );
  }

  {
    decltype( auto ) result
      = reduce
        ( same_type_or_fail, return_types< int const&& >, return_types<>
        , int_fun_t()
        );

    ARGOT_CONCEPT_ENSURE( SameType< decltype( result ), int const&& > );
    ARGOT_TEST_EQ( &result, &v );
    ARGOT_TEST_EQ( result, 42 );
  }

  {
    void_fun_t fun;
    ARGOT_TEST_EQ( fun.value, 0 );

    using result_type
      = decltype
        ( reduce
          ( same_type_or_fail, return_types<>, return_types< void >
          , std::move( fun )
          )
        );

    reduce
    ( same_type_or_fail, return_types<>, return_types< void >
    , std::move( fun )
    );

    ARGOT_CONCEPT_ENSURE( SameType< result_type, void > );
    ARGOT_TEST_EQ( fun.value, 42 );
  }

  {
    void_fun_t fun;
    ARGOT_TEST_EQ( fun.value, 0 );

    using result_type
      = decltype
        ( reduce
          ( same_type_or_fail, return_types< void >, return_types<>
          , std::move( fun )
          )
        );

    reduce
    ( same_type_or_fail, return_types< void >, return_types<>
    , std::move( fun )
    );

    ARGOT_CONCEPT_ENSURE( SameType< result_type, void > );
    ARGOT_TEST_EQ( fun.value, 42 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_same_type_or_fail_reduce_ternary )
{
  ARGOT_CONCEPT_ENSURE
  ( ReturnValueReducerOf< same_type_or_fail_t, void, void, void > );

  ARGOT_CONCEPT_ENSURE
  ( ReturnValueReducerOf< same_type_or_fail_t, int, int, int > );

  ARGOT_CONCEPT_ENSURE
  ( ReturnValueReducerOf< same_type_or_fail_t, int&, int&, int& > );

  ARGOT_CONCEPT_ENSURE
  ( ReturnValueReducerOf< same_type_or_fail_t, udt, udt, udt > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, void, void, int > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, void, int, void > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int, void, void > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int&, int&&, int& > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int, int&&, int&& > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, udt, udt const, udt > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf< same_type_or_fail_t, int(), int(), int() > > );

  ARGOT_CONCEPT_ENSURE
  ( Not< ReturnValueReducerOf
    < same_type_or_fail_t, int[3], int[3], int[3] > >
  );

  {
    decltype( auto ) result
      = reduce
        ( same_type_or_fail
        , return_types<>, return_types< int const&&, int const&& >
        , int_fun_t()
        );

    ARGOT_CONCEPT_ENSURE( SameType< decltype( result ), int const&& > );
    ARGOT_TEST_EQ( &result, &v );
    ARGOT_TEST_EQ( result, 42 );
  }

  {
    decltype( auto ) result
      = reduce
        ( same_type_or_fail
        , return_types< int const&& >, return_types< int const&& >
        , int_fun_t()
        );

    ARGOT_CONCEPT_ENSURE( SameType< decltype( result ), int const&& > );
    ARGOT_TEST_EQ( &result, &v );
    ARGOT_TEST_EQ( result, 42 );
  }

  {
    decltype( auto ) result
      = reduce
        ( same_type_or_fail
        , return_types< int const&&, int const&& >, return_types<>
        , int_fun_t()
        );

    ARGOT_CONCEPT_ENSURE( SameType< decltype( result ), int const&& > );
    ARGOT_TEST_EQ( &result, &v );
    ARGOT_TEST_EQ( result, 42 );
  }

  {
    void_fun_t fun;
    ARGOT_TEST_EQ( fun.value, 0 );

    using result_type
      = decltype
        ( reduce
          ( same_type_or_fail, return_types<>, return_types< void, void >
          , std::move( fun )
          )
        );

    reduce
    ( same_type_or_fail, return_types<>, return_types< void, void >
    , std::move( fun )
    );

    ARGOT_CONCEPT_ENSURE( SameType< result_type, void > );
    ARGOT_TEST_EQ( fun.value, 42 );
  }

  {
    void_fun_t fun;
    ARGOT_TEST_EQ( fun.value, 0 );

    using result_type
      = decltype
        ( reduce
          ( same_type_or_fail, return_types< void >, return_types< void >
          , std::move( fun )
          )
        );

    reduce
    ( same_type_or_fail, return_types< void >, return_types< void >
    , std::move( fun )
    );

    ARGOT_CONCEPT_ENSURE( SameType< result_type, void > );
    ARGOT_TEST_EQ( fun.value, 42 );
  }

  {
    void_fun_t fun;
    ARGOT_TEST_EQ( fun.value, 0 );

    using result_type
      = decltype
        ( reduce
          ( same_type_or_fail, return_types< void, void >, return_types<>
          , std::move( fun )
          )
        );

    reduce
    ( same_type_or_fail, return_types< void, void >, return_types<>
    , std::move( fun )
    );

    ARGOT_CONCEPT_ENSURE( SameType< result_type, void > );
    ARGOT_TEST_EQ( fun.value, 42 );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
