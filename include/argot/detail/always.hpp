/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_ALWAYS_HPP_
#define ARGOT_DETAIL_ALWAYS_HPP_

namespace argot {
namespace call_detail {

template< class T, class... /*Ignored*/ >
struct always { using type = T; };

// Note: Intentionally not a direct alias
template< class T, class... Ignored >
using always_t = typename always< T, Ignored... >::type;

}  // namespace argot::call_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_ALWAYS_HPP_
