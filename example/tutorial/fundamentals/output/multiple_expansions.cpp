/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[example
#include <argot/prov/expand/expansion_operator.hpp>
#include <argot/output.hpp>

#include <iostream>
#include <tuple>

int main()
{
  using namespace argot::expansion_operator;

  auto const hello_tup = std::make_tuple( "Hello", ", ", "World!" );
  auto const goodbye_tup = std::make_tuple( "Goodbye", ", ", "World!" );

  // Outputs:
  //   Hello, World!
  //   Goodbye, World!
  argot::output( std::cout, +hello_tup, "\n", +goodbye_tup );
}
//]
