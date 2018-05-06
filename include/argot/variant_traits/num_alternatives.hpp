/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_NUM_ALTERNATIVES_HPP_
#define ARGOT_VARIANT_TRAITS_NUM_ALTERNATIVES_HPP_

#include <argot/concepts/variant_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/num_alternatives.hpp>
#include <argot/variant_traits/index_type.hpp>

namespace argot {
namespace variant_traits {

template< class Variant >
using num_alternatives_t
  = ARGOT_REQUIRES( VariantLike< Variant > )
    < union_traits::num_alternatives_t< Variant > >;

template< class Variant >
using num_alternatives
  = call_detail::lazy_inherit< num_alternatives_t, Variant >;

template< class Variant >
ARGOT_REQUIRES( VariantLike< Variant > )
< index_type_t< Variant > > constexpr num_alternatives_v
  = num_alternatives_t< Variant >::value;

}  // namespace argot::variant_traits
}  // namespace argot

#endif  // ARGOT_VARIANT_TRAITS_NUM_ALTERNATIVES_HPP_
