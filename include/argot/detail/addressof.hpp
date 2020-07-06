/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_ADDRESSOF_HPP_
#define ARGOT_DETAIL_ADDRESSOF_HPP_

#include <memory>

// TODO(mattcalabrese) Detect and use the builtins directly
#define ARGOT_ADDRESSOF( ... ) ::std::addressof( __VA_ARGS__ )

#endif  // ARGOT_DETAIL_ADDRESSOF_HPP_
