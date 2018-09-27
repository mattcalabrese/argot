/*==============================================================================
  Copyright (c) 2016, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[access_tuple
/*`
[heading Description]

This tutorial introduces an __ArgumentProvider__ that expands out a tuple
element with a runtim index.

[heading Prereq Tutorials]

This tutorial should be able to be understood without reading any other
tutorials in this documentation.

[heading Introduction]

*/
#include <boost_ext/call/call.hpp>
#include <boost_ext/call/prov/access_tuple.hpp>

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
  namespace prov = argot::prov;

  decltype( auto ) result
    = argot::call
      ( output, std::cout
              , prov::access_tuple( std::make_tuple( 5, 2.4 ), 0 )
      );
//<-
  (void)result;
  //return result != 5;
//->
}
/*`
[heading Related References]

* __Primary_call_overload__
* __prov_access_tuple__
*/
//]
