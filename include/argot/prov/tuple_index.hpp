/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TO_TUPLE_INDEX_HPP_
#define ARGOT_PROV_TO_TUPLE_INDEX_HPP_

#include <argot/default_.hpp>
#include <argot/prov/value_in_range.hpp>
#include <argot/tuple_traits/index_type.hpp>
#include <argot/tuple_traits/num_elements.hpp>

namespace argot::prov {

template< class Tuple >
using tuple_index_fn
  = value_in_range_fn
    < tuple_traits::index_type_t< Tuple >
    , 0, tuple_traits::num_elements_v< Tuple >
    >;

template< class Tuple >
inline tuple_index_fn< Tuple > constexpr tuple_index{};

template< class Tuple, class V, class Default = default_unreachable_t >
using result_of_tuple_index
  = result_of_value_in_range
    < tuple_traits::index_type_t< Tuple >
    , 0, tuple_traits::num_elements_v< Tuple >, V
    , Default
    >;

template< class Tuple, class V, class Default = default_unreachable_t >
using result_of_tuple_index_t
  = result_of_value_in_range_t
    < tuple_traits::index_type_t< Tuple >
    , 0, tuple_traits::num_elements_v< Tuple >, V
    , Default
    >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_TO_TUPLE_INDEX_HPP_
