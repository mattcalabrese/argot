/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_MAKE_CONCEPT_MAP_HPP_
#define ARGOT_GEN_MAKE_CONCEPT_MAP_HPP_

namespace argot {

template< class ConceptForm, class /*Enabler*/ = void >
struct auto_concept_map_impl
{
  using argot_detail_concept_is_not_mapped = void;
};

template< class ConceptForm, class /*Enabler*/ = void >
struct make_concept_map
  : auto_concept_map_impl< ConceptForm >{};

}  // namespace argot

#endif  // ARGOT_GEN_MAKE_CONCEPT_MAP_HPP_
