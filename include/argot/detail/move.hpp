/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_MOVE_HPP_
#define ARGOT_DETAIL_MOVE_HPP_

#include <type_traits>

#define ARGOT_MOVE( ... )                                                      \
static_cast< ::std::remove_reference_t< decltype( ( __VA_ARGS__ ) ) >&& >      \
( __VA_ARGS__ )

#endif  // ARGOT_DETAIL_MOVE_HPP_
