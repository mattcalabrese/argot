/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_IN_PLACE_INDEX_WITH_RESULT_HPP_
#define ARGOT_IN_PLACE_INDEX_WITH_RESULT_HPP_

#include <cstddef>

namespace argot {

template< std::size_t I >
struct in_place_index_with_result_t
{
  explicit in_place_index_with_result_t() = default;
};

template< std::size_t I >
constexpr in_place_index_with_result_t< I > in_place_index_with_result{};

} // namespace argot

#endif  // ARGOT_IN_PLACE_INDEX_WITH_RESULT_HPP_
