/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/call.hpp>
#include <argot/forward_arguments_as_tuple.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/if_.hpp>
#include <argot/prov/switch_.hpp>
#include <argot/prov/value_in_range.hpp>
#include <argot/receiver/graphviz_dot.hpp>

#include <iostream>
#include <fstream>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

namespace prov = argot::prov;

#if 0

BOOST_AUTO_TEST_CASE( test_basic )
{/*
  std::string const expected
    = "digraph a\n"
      "  \"b\" -> \"[0]( int{ 1 }, int{ 2 }, int{ 3 } )\"\n"
      "}";
*/
  std::string const result
    = argot::call[ argot::reducer::graphviz_dot( "a", "b" ) ]
      ( argot::forward_arguments_as_tuple
      , prov::if_( false, 0 )
      //, prov::value_of( 1, 2, 3 )
      );

  BOOST_TEST( result == "" );

  return 0;
}

#endif

#define ARGOT_DETAIL_EXAMINE_CALL( name, ... )                             \
::argot::call_                                                             \
[ ::argot::reducer::graphviz_dot( name, #__VA_ARGS__ ) ]                   \
( ::argot::forward_arguments_as_tuple                                      \
, __VA_ARGS__                                                                  \
)

#define ARGOT_DETAIL_EXAMINE_PROVIDER( name, ... )                         \
::argot::prov_traits::provide                                              \
( __VA_ARGS__                                                                  \
, ::argot::receiver::graphviz_dot                                          \
  < ::argot::receiver::ignore_internal_nodes::yes >( name, #__VA_ARGS__ )  \
)

BOOST_AUTO_TEST_CASE( test_branch )
{
  std::ofstream dot_file( "test.dot" );

#if 0

  std::string const result
    = ARGOT_DETAIL_EXAMINE_PROVIDER
      ( "complex_example"
      , prov::group( prov::if_
                     ( true
                     , prov::value_in_range< int, 5, 8 >( 6 )
                     )
                   , prov::value_in_range< int, 10, 13 >( 11 )
                   )
      );

#else

  std::string const result
    = ARGOT_DETAIL_EXAMINE_PROVIDER
      ( "complex_example"
      , prov::conditional( true
                         , prov::if_
                           ( true
                           , prov::if_( true, 3 )
                           )
                         , prov::conditional( true, 4, 5 )
                         )
      );
#endif

  dot_file << result;

  BOOST_TEST( result == "" );

  return 0;
}
