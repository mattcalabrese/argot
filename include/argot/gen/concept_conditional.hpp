/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_CONDITIONAL_HPP_
#define ARGOT_GEN_CONCEPT_CONDITIONAL_HPP_

#include <argot/gen/is_modeled.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/conditional.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

// TODO(mattcalabrese) Constrain to ConceptInstance being a concept instance.
template< class ConceptInstance >
using concept_conditional
  = argot_detail::conditional< is_modeled_v< ConceptInstance > >;

}  // namespace argot

#endif  // ARGOT_GEN_CONCEPT_CONDITIONAL_HPP_
