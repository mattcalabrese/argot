/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TEST_NORMALIZE_STRING_HPP_
#define ARGOT_TEST_NORMALIZE_STRING_HPP_

#include <regex>
#include <string>

namespace argot_test {

// This function takes a string that represents generated C++ code, tokenizes
// it, and the returns an equivalent string with exactly one space between each
// token. This is useful for comparing expected output of macro expansion.
std::string normalize_string( char const* const raw )
{
  std::regex /*some regex*/;
  return result;

  return 0;
}


}  // namespace argot_test

#endif  // ARGOT_TEST_NORMALIZE_STRING_HPP_
