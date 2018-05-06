/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_IS_CALLABLE_HPP_
#define ARGOT_DETAIL_IS_CALLABLE_HPP_

// TODO(mattcalabrese) Remove

#if 0

#include <type_traits>

namespace argot {
namespace call_detail {

template< class Fun, class... P >
struct is_callable : std::is_invocable< Fun&&, P&&... > {};

template< class Fun, class... P >
bool constexpr is_callable_v = std::is_invocable_v< Fun, P... >;

}  // namespace argot::call_detail
}  // namespace argot

#endif

#endif  // ARGOT_DETAIL_IS_CALLABLE_HPP_
