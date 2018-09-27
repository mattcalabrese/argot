/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_NOT_HPP_
#define ARGOT_GEN_NOT_HPP_

#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

template< class ConceptSpec >
ARGOT_EXPLICIT_CONCEPT( Not )
(
);

template< class ConceptSpec >
struct make_concept_map
< Not< ConceptSpec >
, call_detail::fast_enable_if_t< !is_modeled_v< ConceptSpec > >
>{};

} // namespace argot

#endif  // ARGOT_GEN_NOT_HPP_
