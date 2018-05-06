/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/call.hpp>
#include <argot/prov/transform/transform.hpp>
#include <argot/prov/reference_to.hpp>

#include <string>
#include <type_traits>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

int& foo( int& arg0, char arg1 )
{
  arg0 += arg1;
  return arg0;

  return 0;
}

namespace prov = argot::prov;
/*
template< class > struct error;

error
< argot::receiver::possible_parameter_type_lists_of
  < decltype
    ( prov::transform( prov::reference_to( 4. ), prov::reference_to ) )
  >
> asg;
*/
BOOST_AUTO_TEST_CASE( test_basic )
{
  using argot::call;
  namespace prov = argot::prov;
  call( []( double a ) { return a; }
      , prov::transform( prov::reference_to( 4. )
                       , prov::reference_to
                       )
      );
  //BOOST_TEST( a == 11 );

  return 0;
}
