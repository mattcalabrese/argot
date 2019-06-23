/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_DECLVAL_HPP_
#define ARGOT_DETAIL_DECLVAL_HPP_

namespace argot::detail_declval {

template< class T >
using add_rvalue_reference_t = T&&;

extern char dummy[];

}  // namespace (argot::detail_declval)

#define ARGOT_DECLVAL( ... )                                                   \
reinterpret_cast                                                               \
< ::argot::detail_declval::add_rvalue_reference_t< __VA_ARGS__ > >             \
( ::argot::detail_declval::dummy )

#endif  // ARGOT_DETAIL_DECLVAL_HPP_
