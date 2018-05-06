/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONSTANT_HPP_
#define ARGOT_DETAIL_CONSTANT_HPP_

#include <type_traits>

namespace argot {
namespace call_detail {

template< auto Value >
using constant = std::integral_constant< decltype( Value ), Value >;

}  // namespace call_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_CONSTANT_HPP_
