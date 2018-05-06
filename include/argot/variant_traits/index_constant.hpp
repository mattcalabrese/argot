/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_INDEX_CONSTANT_HPP_
#define ARGOT_VARIANT_TRAITS_INDEX_CONSTANT_HPP_

#include <argot/union_traits/index_constant.hpp>
#include <argot/variant_traits/index_type.hpp>

namespace argot {
namespace variant_traits {

template< class Variant, index_type_t< Variant > Index >
using index_constant_t = union_traits::index_constant_t< Variant, Index >;

template< class Variant, index_type_t< Variant > Index >
inline index_constant_t< Variant, Index > constexpr index_constant_v{};

}  // namespace argot::variant_traits
}  // namespace argot

#endif  // ARGOT_VARIANT_TRAITS_INDEX_CONSTANT_HPP_
