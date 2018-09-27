/*==============================================================================
  Copyright (c) 2016 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[comose
/*`
[heading Description]

This tutorial introduces an __ArgumentProvider__ that...

[heading Prereq Tutorials]

This tutorial should be able to be understood without reading any other
tutorials in this documentation.

[heading Introduction]

*/
#include <boost_ext/call/call.hpp>
#include <boost_ext/call/prov/compose.hpp>

#include <iostream>
#include <tuple>

const auto output
  = []( auto& os, auto const&... args )
      -> decltype( auto )
    {
      return ( os << ... << args );
    };

int main()
{
  namespace prov = boost_ext::prov;
/*
  decltype( auto ) result
    = boost_ext::call( output, std::cout
                             , prov::unpack( std::make_tuple( 5, 2.4 ) )
                     );*/
//<-
//  (void)result;
  //return result != 5;
//->
}
/*`
[heading Related References]

* __Primary_call_overload__
* __prov_compose__
*/
//]
