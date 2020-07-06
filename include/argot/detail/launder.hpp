/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_LAUNDER_HPP_
#define ARGOT_DETAIL_LAUNDER_HPP_

#include <argot/detail/addressof.hpp>
#include <new>

// TODO(mattcalabrese) Detect and use the builtins directly
#define ARGOT_LAUNDER( ... ) ::std::launder( __VA_ARGS__ )

#define ARGOT_LAUNDER_DIRECT( ... )                                            \
  ( *ARGOT_LAUNDER( ARGOT_ADDRESSOF( __VA_ARGS__ ) ) )

#endif  // ARGOT_DETAIL_LAUNDER_HPP_
