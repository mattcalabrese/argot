/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_IN_PLACE_WITH_RESULT_HPP_
#define ARGOT_IN_PLACE_WITH_RESULT_HPP_

namespace argot {

struct in_place_with_result_t
{
  explicit in_place_with_result_t() = default;
} constexpr inline in_place_with_result{};

} // namespace argot

#endif  // ARGOT_IN_PLACE_WITH_RESULT_HPP_
