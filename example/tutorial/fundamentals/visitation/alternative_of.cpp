/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[example
#include <argot/prov/alternative_of.hpp>
#include <argot/output.hpp>

#include <iostream>
#include <string>
#include <variant>

int main()
{
  namespace prov = argot::prov;

  std::variant< std::string, double > var = std::string( "Hello, " );

  // Outputs:
  //   Hello, World!
  argot::output( std::cout, prov::alternative_of( var ), "World!" );
}
//]
