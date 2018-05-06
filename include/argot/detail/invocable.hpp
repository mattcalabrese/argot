/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_INVOCABLE_HPP_
#define ARGOT_DETAIL_INVOCABLE_HPP_

// TODO(mattcalabrese) Remove this once libc++ supports is_invocable_v

#include <argot/detail/detection.hpp>

#include <type_traits>

namespace argot::argot_detail {

template< class R, class... P >
bool constexpr is_invocable_v
  = call_detail::is_detected_v< std::result_of_t, R&&( P&&... ) >;

}  // namespace (argot::argot_detail)

#endif  // ARGOT_DETAIL_INVOCABLE_HPP_
