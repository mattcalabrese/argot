/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[example
#include <argot/prov/unpack.hpp>
#include <argot/output.hpp>

#include <iostream>
#include <tuple>

int main()
{
  namespace prov = argot::prov;

  auto tup = std::make_tuple( "Hello", ", ", "World!" );

  // Outputs:
  //   Hello, World!
  argot::output( std::cout, prov::unpack( tup ) );
}
//]
