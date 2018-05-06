/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_ELEMENT_TYPE_HPP_
#define ARGOT_TUPLE_TRAITS_ELEMENT_TYPE_HPP_

#include <argot/concepts/tuple_index.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/tuple_traits/index_type.hpp>

namespace argot::tuple_traits {

template< class Tup, auto Index >
using element_type_t
  = ARGOT_REQUIRES( TupleLike< Tup > )
                  ( TupleIndex< Tup, Index > )
    < typename access_raw_concept_map< TupleLike< T > >
      ::template element_type_t< Index >
    >;

template< class Tup, auto Index >
using element_type
  = call_detail::lazy_expand_access< element_type_t, Tup, Index >;

}  // namespace (argot::tuple_traits)

#endif  // ARGOT_TUPLE_TRAITS_ELEMENT_TYPE_HPP_
