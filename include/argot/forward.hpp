/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FORWARD_HPP_
#define ARGOT_FORWARD_HPP_

namespace argot::forward_detail {

template< class T >
using direct_identity_t = T;

}  // namespace (argot::forward_detail)

#define ARGOT_FORWARD( ... )                                                   \
static_cast< ::argot::forward_detail::direct_identity_t< __VA_ARGS__ >&& >

#endif  // ARGOT_FORWARD_HPP_
