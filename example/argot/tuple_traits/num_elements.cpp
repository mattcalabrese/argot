/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[example
#include <argot/tuple_traits/num_elements.hpp>

#include <iostream>
#include <tuple>

int main()
{
  using argot::tuple_traits;

  using tuple_type = std::tuple< int, float, char >;

  // Output the number of elements of the tuple.
  std::cout << tuple_traits::num_elements_v< tuple_type >;
}
//]
