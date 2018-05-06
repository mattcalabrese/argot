/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_ALTERNATIVE_TYPE_HPP_
#define ARGOT_UNION_TRAITS_ALTERNATIVE_TYPE_HPP_

#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/index_type.hpp>

namespace argot::union_traits {

template< class Union, auto Index >
using alternative_type_t
  = ARGOT_REQUIRES( UnionLike< Union > )
                  ( UnionIndex< Union, Index > )
    < typename access_raw_concept_map< UnionLike< T > >
      ::template alternative_type_t< Index >
    >;

template< class Union, auto Index >
using alternative_type
  = call_detail::lazy_expand_access< alternative_type_t, Union, Index >;

}  // namespace (argot::union_traits)

#endif  // ARGOT_UNION_TRAITS_ALTERNATIVE_TYPE_HPP_
