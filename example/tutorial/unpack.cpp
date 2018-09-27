/*==============================================================================
  Copyright (c) 2016 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[unpack
/*`
[heading Description]

This tutorial introduces an __ArgumentProvider__ that expands out a tuple's
elements as separate arguments to a function. This allows for tuple expansion in
a way that is similar to the C++17 function template `std::apply`, but while
`std::apply` can only expand a tuple in a way that forms the complete argument
list of the =Callable=, `boost_ext::call` is capable of expanding out the
tuple's elements as just a portion of a larger argument list.

[heading Prereq Tutorials]

This tutorial should be able to be understood without reading any other
tutorials in this documentation.

[heading Introduction]

*/
#include <boost_ext/call/call.hpp>
#include <boost_ext/call/prov/unpack.hpp>

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

  decltype( auto ) result
    = boost_ext::call( output, std::cout
                             , prov::unpack( std::make_tuple( 5, 2.4 ) )
                     );
//<-
  (void)result;
  //return result != 5;
//->
}
/*`
[heading Related References]

* __Primary_call_overload__
* __prov_unpack__
*/
//]
