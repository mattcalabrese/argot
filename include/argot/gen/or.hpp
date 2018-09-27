/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_OR_HPP_
#define ARGOT_GEN_OR_HPP_

#include <argot/gen/explicit_concept.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

template< class... ConceptSpecs >
ARGOT_EXPLICIT_CONCEPT( Or )
(
);

template< class HeadConceptSpec, class... TailConceptSpecs >
struct make_concept_map
< Or< HeadConceptSpec, TailConceptSpecs... >
, typename call_detail::detached_fast_enable_if
  < HeadConceptSpec
    ::template argot_gen_detail_is_modeled_impl< HeadConceptSpec >
    ::template or_< TailConceptSpecs... >::value
  >::_::template apply<>
> {};

} // namespace argot

#endif  // ARGOT_GEN_OR_HPP_
