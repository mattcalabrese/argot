/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[example
#include <argot/call.hpp>
#include <argot/prov/expand/expansion_operator.hpp>

#include <iostream>
#include <string>
#include <variant>

int main()
{
  using namespace argot::expansion_operator;

  auto const stream_to_cout
    = []( auto const&... args )
      {
        ( std::cout << ... << args );
      };

  std::variant< std::string, double > var = std::string( "Hello, " );

  // Outputs:
  //   Hello, World!
  argot::call( stream_to_cout, +var, "World!" );
}
//]
