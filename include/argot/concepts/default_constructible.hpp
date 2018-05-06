/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_DEFAULT_CONSTRUCTIBLE_HPP_
#define ARGOT_CONCEPTS_DEFAULT_CONSTRUCTIBLE_HPP_

#include <argot/concepts/constructible.hpp>

namespace argot {

template< class T >
using DefaultConstructible = Constructible< T >;

}  // namespace argot

#endif  // ARGOT_CONCEPTS_DEFAULT_CONSTRUCTIBLE_HPP_
