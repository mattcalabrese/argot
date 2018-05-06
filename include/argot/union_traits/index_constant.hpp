/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_INDEX_CONSTANT_HPP_
#define ARGOT_UNION_TRAITS_INDEX_CONSTANT_HPP_

#include <argot/union_traits/index_type.hpp>

#include <type_traits>

namespace argot {
namespace union_traits {

template< class Union, index_type_t< Union > Index >
using index_constant_t
  = std::integral_constant< index_type_t< Union >, Index >;

template< class Union, index_type_t< Union > Index >
inline index_constant_t< Union, Index > constexpr index_constant_v{};

}  // namespace argot::union_traits
}  // namespace argot

#endif  // ARGOT_UNION_TRAITS_INDEX_CONSTANT_HPP_
