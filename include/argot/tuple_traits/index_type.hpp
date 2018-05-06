/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_INDEX_TYPE_HPP_
#define ARGOT_TUPLE_TRAITS_INDEX_TYPE_HPP_

#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot::tuple_traits {

template< class Tup >
using index_type_t
  = ARGOT_REQUIRES( TupleLike< Tup > )
    < typename access_raw_concept_map< TupleLike< Tup > >::index_type >;

template< class Tup >
using index_type = call_detail::lazy_expand< index_type_t, Tup >;

}  // namespace (argot::tuple_traits)

#endif  // ARGOT_TUPLE_TRAITS_INDEX_TYPE_HPP_
