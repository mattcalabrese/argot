/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DECLVAL_HPP_
#define ARGOT_DECLVAL_HPP_

namespace argot::declval_detail {

template< class T >
using add_rvalue_reference_t = T&&;

extern char dummy[];

}  // namespace (argot::declval_detail)

#define ARGOT_DECLVAL( ... )                                                   \
reinterpret_cast                                                               \
< ::argot::declval_detail::add_rvalue_reference_t< __VA_ARGS__ > >             \
( ::argot::declval_detail::dummy )

#endif  // ARGOT_DECLVAL_HPP_
