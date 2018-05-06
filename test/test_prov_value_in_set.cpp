/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/call.hpp>
#include <argot/prov/value_in_set.hpp>

#include <cstddef>
#include <type_traits>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

struct integral_const_fun_t
{
  std::size_t operator()( std::integral_constant< int, 2 > ) const
  {
    return 2;
  }

  std::size_t operator()( std::integral_constant< int, 5 > ) const
  {
    return 5;
  }

  std::size_t operator()( std::integral_constant< int, 7 > ) const
  {
    return 7;
  }
} constexpr integral_const_fun{};

// TODO(mattcalabrese) Test conversion of value types

// TODO(mattcalabrese) Make sure this does not branch
/*
BOOST_AUTO_TEST_CASE( test_compile_time )
{
  using argot::call;
  namespace prov = argot::prov;

  BOOST_TEST
  ( call( integral_const_fun
        , prov::value_in_set< 2, 5, 7 >
          ( std::integral_constant< std::size_t, 2 >() )
        ) == 2u
  );

  BOOST_TEST
  ( call( integral_const_fun
        , prov::value_in_set< 2, 5, 7 >
          ( std::integral_constant< std::size_t, 5 >() )
        ) == 5u
  );

  BOOST_TEST
  ( call( integral_const_fun
        , prov::value_in_set< 2, 5, 7 >
          ( std::integral_constant< std::size_t, 7 >() )
        ) == 7u
  );

  return 0;
}
*/

BOOST_AUTO_TEST_CASE( test_run_time )
{
  using argot::call;
  namespace prov = argot::prov;
  BOOST_TEST
  ( call( integral_const_fun
        , prov::value_in_set< 2, 5, 7 >( std::size_t{ 2 } )
        ) == 2u
  );

  BOOST_TEST
  ( call( integral_const_fun
        , prov::value_in_set< 2, 5, 7 >( std::size_t{ 5 } )
        ) == 5u
  );

  BOOST_TEST
  ( call( integral_const_fun
        , prov::value_in_set< 2, 5, 7 >( std::size_t{ 7 } )
        ) == 7u
  );

  return 0;
}
