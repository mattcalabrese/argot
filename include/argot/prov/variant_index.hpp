/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TO_VARIANT_INDEX_HPP_
#define ARGOT_PROV_TO_VARIANT_INDEX_HPP_

#include <argot/default_.hpp>
#include <argot/prov/value_in_range.hpp>
#include <argot/variant_traits/index_type.hpp>
#include <argot/variant_traits/num_alternatives.hpp>

namespace argot::prov {

// TODO(mattcalabrese) Rewrite as enabled alias of union_index
template< class Variant >
using variant_index_fn
  = value_in_range_fn
    < variant_traits::index_type_t< Variant >
    , 0, variant_traits::num_alternatives_v< Variant >
    >;

template< class Variant >
inline variant_index_fn< Variant > constexpr variant_index{};

template< class Variant, class V, class Default = default_unreachable_t >
using result_of_variant_index
  = result_of_value_in_range
    < variant_traits::index_type_t< Variant >
    , 0, variant_traits::num_alternatives_v< Variant >, V
    , Default
    >;

template< class Variant, class V, class Default = default_unreachable_t >
using result_of_variant_index_t
  = result_of_value_in_range_t
    < variant_traits::index_type_t< Variant >
    , 0, variant_traits::num_alternatives_v< Variant >, V
    , Default
    >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_TO_CONSTANT_VARIANT_INDEX_HPP_
