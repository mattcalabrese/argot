/*==============================================================================
  Copyright (c) 2017, 2018, 2019, 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_FORWARD_HPP_
#define ARGOT_DETAIL_FORWARD_HPP_

namespace argot::detail_forward {

template< class T >
using direct_identity_t = T;

} // namespace (argot::detail_forward)

#define ARGOT_FORWARD( ... )                                                   \
  static_cast< ::argot::detail_forward::direct_identity_t< __VA_ARGS__ >&& >

#define ARGOT_SIMPLE_FORWARD( ... )                                            \
  static_cast< decltype( __VA_ARGS__ )&& >( __VA_ARGS__ )

#endif  // ARGOT_DETAIL_FORWARD_HPP_
