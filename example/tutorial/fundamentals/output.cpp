/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[access_tuple
/*`
[heading Description]

This tutorial is the "Hello, World" of =Argot=, exploring a facility for
outputting data to a stream while taking advantage of basic /argument provision/
functionality.

[heading Prereq Tutorials]

This tutorial should be able to be understood without reading any other
tutorials in this documentation.

[heading Introduction]

*/
#include <argot/output.hpp>

#include <iostream>
#include <tuple>

int main()
{
  argot::output( std::cout, "Hello, World!");
}
/*`
[heading Related References]

* __Primary_call_overload__
* __prov_access_tuple__
*/
//]
