/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_INDEX_TYPE_HPP_
#define ARGOT_VARIANT_TRAITS_INDEX_TYPE_HPP_

#include <argot/concepts/variant_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/index_type.hpp>

namespace argot {
namespace variant_traits {

template< class Variant >
using index_type_t
  = ARGOT_REQUIRES( VariantLike< Variant > )
    < typename union_traits::index_type_t< Variant > >;

template< class Variant >
using index_type = call_detail::lazy_inherit< index_type_t, Variant >;

}  // namespace argot::variant_traits
}  // namespace argot

#endif  // ARGOT_VARIANT_TRAITS_INDEX_TYPE_HPP_
