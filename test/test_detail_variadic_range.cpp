/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/detail/variadic_range.hpp>

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>

#include <utility>
#include <variant>

namespace {

using argot::detail_argot::variadic_sized_range_run;
using argot::detail_argot::variadic_range_run;

using argot::SameType;

// TODO(mattcalabrese) Possibly test branching providers.


template< std::size_t I >
struct arg_n {
  arg_n( arg_n const& ) = delete;

  static constexpr arg_n make() { return arg_n(); }
 private:
  arg_n() = default;
};

template< std::size_t... I >
struct expect_args_fn {
  template< class... P >
  constexpr bool operator()( P&&... ) const
  {
    ARGOT_CONCEPT_ENSURE( SameType< P, arg_n< I > >... );
    return true;
  }
};

template< std::size_t... I >
struct expect_lvalue_args_fn {
  template< class... P >
  constexpr bool operator()( P&&... ) const
  {
    ARGOT_CONCEPT_ENSURE( SameType< P, arg_n< I >& >... );
    return true;
  }
};

template< std::size_t Offset, std::size_t... I >
constexpr expect_args_fn< ( I + Offset )... >
expect_args( std::index_sequence< I... > )
{
  return {};
}

template< std::size_t Offset, std::size_t... I >
constexpr expect_lvalue_args_fn< ( I + Offset )... >
expect_lvalue_args( std::index_sequence< I... > )
{
  return {};
}

template< class T >
constexpr T& as_lvalue( T&& arg )
{
  return arg;
}

template< std::size_t Size, std::size_t... AllI, std::size_t... InitialI >
constexpr decltype( auto )
check_variadic_sized_range_dense_impl
( std::index_sequence< AllI... > all
, std::index_sequence< InitialI... > initial
)
{
  return
  (    ( variadic_sized_range_run< InitialI, Size > )
       ( ( expect_args< InitialI > )( std::make_index_sequence< Size >() )
       , arg_n< AllI >::make()...
       )
    && ...
    && (    ( variadic_sized_range_run< InitialI, Size > )
            ( ( expect_lvalue_args< InitialI > )
              ( std::make_index_sequence< Size >() )
            , ( as_lvalue )( arg_n< AllI >::make() )...
            )
         && ...
       )
  );
}

template< std::size_t... AllI >
constexpr decltype( auto )
check_variadic_sized_range_dense( std::index_sequence< AllI... > all )
{
  return
  (    ( check_variadic_sized_range_dense_impl< AllI > )
       ( all
       , std::make_index_sequence< sizeof...( AllI ) - AllI >()
       )
    && ...
  );
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_range_dense )
{
  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 0 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 1 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 2 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 3 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 4 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 5 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 6 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 7 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 8 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 9 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 10 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 11 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 12 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 13 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 14 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 15 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 16 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 17 >() ) );

  ARGOT_TEST_TRUE
  ( ( check_variadic_sized_range_dense )( std::make_index_sequence< 18 >() ) );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
