/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TAG_HPP_
#define ARGOT_TAG_HPP_

//[description
/*`
argot::tag is a facility for communicating a type via a function parameter.
*/
//]

#include <argot/detail/regular_monostate_base.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

template< class T >
struct tag
//<-
  : private argot_detail::regular_monostate_base< tag< T > > //->
{
  using type = T;
};

} // namespace argot

//]

namespace std {

template< class T >
struct hash;

template< class T >
ARGOT_DETAIL_MONOSTATE_HASH_DEFINITION( ::argot::tag< T > );

} // namespace std

#endif  // ARGOT_TAG_HPP_
