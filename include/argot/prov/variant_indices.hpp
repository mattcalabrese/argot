/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_VARIANT_INDICES_HPP_
#define ARGOT_PROV_VARIANT_INDICES_HPP_

#include <argot/concepts/variant_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/integer_sequence.hpp>
#include <argot/variant_traits/num_alternatives.hpp>

namespace argot::prov {

template< class Variant >
using variant_indices_t
  = ARGOT_REQUIRES( VariantLike< Variant > )
    < integer_sequence_t< variant_traits::num_alternatives_v< Variant > > >;

template< class Variant >
ARGOT_REQUIRES( VariantLike< Variant > )
< variant_indices_t< Variant > > constexpr variant_indices{};

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_VARIANT_INDICES_HPP_
