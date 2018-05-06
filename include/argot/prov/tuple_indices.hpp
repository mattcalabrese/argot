/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TUPLE_INDICES_HPP_
#define ARGOT_PROV_TUPLE_INDICES_HPP_

#include <argot/concepts/tuple_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/integer_sequence.hpp>
#include <argot/tuple_traits/num_elements.hpp>

namespace argot::prov {

// TODO(mattcalabrese) Constrain

template< class Tuple >
using tuple_indices_t
  = ARGOT_REQUIRES( TupleLike< Tuple > )
    < integer_sequence_t< tuple_traits::num_elements_v< Tuple > > >;

template< class Tuple >
ARGOT_REQUIRES( TupleLike< Tuple > )
< tuple_indices_t< Tuple > > constexpr tuple_indices{};

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_TUPLE_INDICES_HPP_
