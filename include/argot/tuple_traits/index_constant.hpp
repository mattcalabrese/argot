/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_INDEX_CONSTANT_HPP_
#define ARGOT_TUPLE_TRAITS_INDEX_CONSTANT_HPP_

#include <argot/tuple_traits/index_type.hpp>

#include <type_traits>

namespace argot::tuple_traits {

template< class TupleLike, index_type_t< TupleLike > Index >
using index_constant_t
  = std::integral_constant< index_type_t< TupleLike >, Index >;

template< class TupleLike, index_type_t< TupleLike > Index >
inline index_constant_t< TupleLike, Index > constexpr index_constant_v{};

}  // namespace (argot::tuple_traits)

#endif  // ARGOT_TUPLE_TRAITS_INDEX_CONSTANT_HPP_
