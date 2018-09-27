/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_IS_AUTO_CONCEPT_HPP_
#define ARGOT_GEN_IS_AUTO_CONCEPT_HPP_

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

// TODO(mattcalabrese) SFINAE or static_assert existence of value
template< class T >
bool constexpr is_auto_concept_v = T::argot_gen_detail_is_auto_concept_v;

// TODO(mattcalabrese) SFINAE or static_assert existence of value
template< class T >
using is_auto_concept
  = std::bool_constant< T::argot_gen_detail_is_auto_concept_v >;

} // namespace argot

#endif  // ARGOT_GEN_IS_AUTO_CONCEPT_HPP_
