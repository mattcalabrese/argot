/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_NUM_ALTERNATIVES_HPP_
#define ARGOT_UNION_TRAITS_NUM_ALTERNATIVES_HPP_

#include <argot/concepts/union_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/index_type.hpp>

#include <type_traits>

namespace argot {
namespace union_traits {

template< class Union >
using num_alternatives_t
  = ARGOT_REQUIRES( UnionLike< Union > )
    < std::integral_constant
      < index_type_t< Union >
      , access_raw_concept_map< UnionLike< Union > >::num_alternatives
      >
    >;

template< class Union >
using num_alternatives
  = call_detail::lazy_inherit< num_alternatives_t, Union >;

template< class Union >
ARGOT_REQUIRES( UnionLike< Union > )
< index_type_t< Union > > constexpr num_alternatives_v
  = num_alternatives_t< Union >::value;

}  // namespace argot::union_traits
}  // namespace argot

#endif  // ARGOT_UNION_TRAITS_NUM_ALTERNATIVES_HPP_
