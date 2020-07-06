/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_IS_RVALUE_REFERENCE_HPP_
#define ARGOT_DETAIL_IS_RVALUE_REFERENCE_HPP_

#include <type_traits>

#define ARGOT_IS_RVALUE_REFERENCE( ... )                                       \
  ( ::std::is_rvalue_reference_v< __VA_ARGS__ > )

#endif  // ARGOT_DETAIL_IS_RVALUE_REFERENCE_HPP_
