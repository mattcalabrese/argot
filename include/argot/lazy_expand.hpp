/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_LAZY_EXPAND_HPP_
#define ARGOT_LAZY_EXPAND_HPP_

namespace argot {

template< template< class... /*P*/ > class Temp, class... P >
struct lazy_expand
{
  using type = Temp< P... >;
};

}  // namespace argot

#endif  // ARGOT_LAZY_EXPAND_HPP_
