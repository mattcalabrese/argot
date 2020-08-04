/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_RETHROW_HPP_
#define ARGOT_DETAIL_RETHROW_HPP_

namespace argot::detail_argot {

[[noreturn]] inline void rethrow() { throw; }

} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_RETHROW_HPP_
