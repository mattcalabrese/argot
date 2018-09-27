/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[example
#include <argot/output.hpp>
#include <argot/prov/access_tuple.hpp>

#include <iostream>
#include <tuple>

int main()
{
  namespace prov = argot::prov;

  // A tuple we want to index at runtime.
  auto const tup = std::make_tuple( ", ", "World!", "Hello" );

  // Output "Hello, World!" via runtime tuple access.
  argot::output( std::cout, prov::access_tuple( tup, 2 )
                          , prov::access_tuple( tup, 0 )
                          , prov::access_tuple( tup, 1 )
                          );
}
//]
