/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_NO_UNIQUE_ADDRESS_HPP_
#define ARGOT_NO_UNIQUE_ADDRESS_HPP_

#include <boost/predef.h>

#if __has_cpp_attribute( no_unique_address )
#define ARGOT_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define ARGOT_NO_UNIQUE_ADDRESS
#endif  // __has_cpp_attribute( no_unique_address )

// GCC screws up [[no_unique_address]] for unions in a way that ICEs
#if BOOST_COMP_GNUC
#define ARGOT_DETAIL_NO_UNIQUE_ADDRESS_FOR_UNION
#else
#define ARGOT_DETAIL_NO_UNIQUE_ADDRESS_FOR_UNION ARGOT_NO_UNIQUE_ADDRESS
#endif

#endif  // ARGOT_NO_UNIQUE_ADDRESS_HPP_
