/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_ALTERNATIVE_TYPE_HPP_
#define ARGOT_VARIANT_TRAITS_ALTERNATIVE_TYPE_HPP_

#include <argot/concepts/variant_index.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/alternative_type.hpp>

namespace argot::variant_traits {

template< class Variant, auto Index >
using alternative_type_t
  = ARGOT_REQUIRES( VariantLike< Variant > )
                  ( VariantIndex< Variant, Index > )
    < typename union_traits::alternative_type_t< Variant, Index > >;

template< class Variant, auto Index >
using alternative_type
  = call_detail::lazy_expand_access< alternative_type_t, Variant, Index >;

}  // namespace (argot::variant_traits)

#endif  // ARGOT_VARIANT_TRAITS_ALTERNATIVE_TYPE_HPP_
