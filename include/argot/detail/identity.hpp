/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_IDENTITY_HPP_
#define ARGOT_DETAIL_IDENTITY_HPP_

namespace argot::argot_detail {

template< class T >
struct identity
{
  using _ = T;

  using type = T;

  template< class... >
  using apply = T;

  template< class... >
  using self_apply = identity;
};

template< class T >
using identity_t = typename identity< T >::type;

} // namespace (argot::argot_detail)

#endif  // ARGOT_DETAIL_IDENTITY_HPP_
