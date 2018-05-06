/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_IS_VALID_INDEX_HPP_
#define ARGOT_VARIANT_TRAITS_IS_VALID_INDEX_HPP_

#include <argot/variant_traits/index_type.hpp>
#include <argot/variant_traits/num_alternatives.hpp>

#include <type_traits>

namespace argot::variant_traits {

// TODO(mattcalabrese) Make this a concept instead.
template< class Variant, index_type_t< Variant > Index >
struct is_valid_index
  : std::integral_constant
    < bool, ( Index >= 0 && Index < num_alternatives_v< Variant > ) >{};

template< class Variant, index_type_t< Variant > Index >
bool constexpr is_valid_index_v = is_valid_index< Variant, Index >::value;

}  // namespace (argot::variant_traits)

#endif  // ARGOT_VARIANT_TRAITS_IS_VALID_INDEX_HPP_
