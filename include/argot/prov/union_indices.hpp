/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_UNION_INDICES_HPP_
#define ARGOT_PROV_UNION_INDICES_HPP_

#include <argot/concepts/union_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/integer_sequence.hpp>
#include <argot/union_traits/num_alternatives.hpp>

namespace argot::prov {

template< class Union >
using union_indices_t
  = ARGOT_REQUIRES( UnionLike< Union > )
    < integer_sequence_t< union_traits::num_alternatives_v< Union > > >;

template< class Union >
ARGOT_REQUIRES( UnionLike< Union > )
< union_indices_t< Union > > constexpr union_indices{};

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_UNION_INDICES_HPP_
