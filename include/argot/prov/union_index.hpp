/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TO_CONSTANT_UNION_INDEX_HPP_
#define ARGOT_PROV_TO_CONSTANT_UNION_INDEX_HPP_

#include <argot/default_.hpp>
#include <argot/prov/value_in_range.hpp>
#include <argot/union_traits/index_type.hpp>
#include <argot/union_traits/num_alternatives.hpp>

namespace argot::prov {

template< class Union >
using union_index_fn
  = value_in_range_fn
    < union_traits::index_type_t< Union >
    , 0, union_traits::num_alternatives_v< Union >
    >;

template< class Union >
inline union_index_fn< Union > constexpr union_index{};

template< class Union, class V, class Default = default_unreachable_t >
using result_of_union_index
  = result_of_value_in_range
    < union_traits::index_type_t< Union >
    , 0, union_traits::num_alternatives_v< Union >, V
    , Default
    >;

template< class Union, class V, class Default = default_unreachable_t >
using result_of_union_index_t
  = result_of_value_in_range_t
    < union_traits::index_type_t< Union >
    , 0, union_traits::num_alternatives_v< Union >, V
    , Default
    >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_TO_CONSTANT_UNION_INDEX_HPP_
