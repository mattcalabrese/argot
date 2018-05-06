/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_IS_VALID_INDEX_HPP_
#define ARGOT_UNION_TRAITS_IS_VALID_INDEX_HPP_

#include <argot/union_traits/index_type.hpp>
#include <argot/union_traits/num_alternatives.hpp>

#include <type_traits>

namespace argot {
namespace union_traits {

// TODO(mattcalabrese) Make this a concept instead.
template< class Union, index_type_t< Union > Index >
struct is_valid_index
  : std::integral_constant
    < bool, ( Index >= 0 && Index < num_alternatives_v< Union > ) >{};

template< class Union, index_type_t< Union > Index >
bool constexpr is_valid_index_v = is_valid_index< Union, Index >::value;

}  // namespace argot::union_traits
}  // namespace argot

#endif  // ARGOT_UNION_TRAITS_IS_VALID_INDEX_HPP_
