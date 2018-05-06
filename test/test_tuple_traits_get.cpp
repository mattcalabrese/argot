/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/detail/constexpr_test.hpp>
#include <argot/tuple_traits/natural_get.hpp>
#include <argot/tuple_traits/index_constant.hpp>

#include <tuple>
#include <type_traits>

namespace {

namespace tuple_traits = argot::tuple_traits;

struct a{}; struct b{}; struct c{};
using tuple_type = std::tuple< a, b, c >;

ARGOT_REGISTER_CONSTEXPR_TEST( test_get_lvalue )
{
  tuple_type tup = std::make_tuple( a(), b(), c() );

  ARGOT_TEST_EQ
  ( &std::get< 0 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 0 > )
  );

  ARGOT_TEST_EQ
  ( &std::get< 1 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 1 > )
  );

  ARGOT_TEST_EQ
  ( &std::get< 2 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 2 > )
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_get_lvalue_const )
{
  tuple_type const tup = std::make_tuple( a(), b(), c() );

  ARGOT_TEST_EQ
  ( &std::get< 0 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 0 > )
  );

  ARGOT_TEST_EQ
  ( &std::get< 1 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 1 > )
  );

  ARGOT_TEST_EQ
  ( &std::get< 2 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 2 > )
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_get_rvalue )
{
  tuple_type tup = std::make_tuple( a(), b(), c() );

  {
    a&& element_reference
      = tuple_traits::natural_get
        ( std::move( tup ), tuple_traits::index_constant_v< tuple_type, 0 > );

    ARGOT_TEST_EQ( &std::get< 0 >( tup ), &element_reference );
  }

  {
    b&& element_reference
      = tuple_traits::natural_get
        ( std::move( tup ), tuple_traits::index_constant_v< tuple_type, 1 > );

    ARGOT_TEST_EQ( &std::get< 1 >( tup ), &element_reference );
  }

  {
    c&& element_reference
      = tuple_traits::natural_get
        ( std::move( tup ), tuple_traits::index_constant_v< tuple_type, 2 > );

    ARGOT_TEST_EQ( &std::get< 2 >( tup ), &element_reference );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_get_compatible_index_type )
{
  tuple_type tup = std::make_tuple( a(), b(), c() );

  ARGOT_TEST_EQ
  ( &std::get< 0 >( tup )
  , &tuple_traits::natural_get( tup, std::integral_constant< char, 0 >() )
  );

  ARGOT_TEST_EQ
  ( &std::get< 1 >( tup )
  , &tuple_traits::natural_get( tup, std::integral_constant< char, 1 >() )
  );

  ARGOT_TEST_EQ
  ( &std::get< 2 >( tup )
  , &tuple_traits::natural_get( tup, std::integral_constant< char, 2 >() )
  );

  return 0;
}

ARGOT_EXECUTE_TESTS();

} // namespace
