/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_MAP_IS_VALID_HPP_
#define ARGOT_GEN_CONCEPT_MAP_IS_VALID_HPP_

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

// TODO(mattcalabrese)
//   Possibly change or eliminate the default definition.
//   Possibly static_assert if this isn't specialized and someone uses it.
template< class ConceptForm >
struct concept_map_is_valid : std::true_type{};

template< class ConceptForm >
bool constexpr concept_map_is_valid_v
  = concept_map_is_valid< ConceptForm >::value;

} // namespace argot

#endif  // ARGOT_GEN_CONCEPT_MAP_IS_VALID_HPP_
