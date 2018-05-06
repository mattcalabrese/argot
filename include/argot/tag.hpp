/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TAG_HPP_
#define ARGOT_TAG_HPP_

namespace argot {

template< class T >
struct tag
{
  using type = T;
};

}  // namespace argot

#endif  // ARGOT_TAG_HPP_
