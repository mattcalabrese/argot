/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_ACCESS_RAW_CONCEPT_MAP_HPP_
#define ARGOT_GEN_ACCESS_RAW_CONCEPT_MAP_HPP_

#include <argot/gen/make_concept_map.hpp>

namespace argot {

// TODO(mattcalabrese)
//   static_assert that the concept map is valid whenever it is specialized.
//   Do this via a template alias?
template< class ConceptForm >
struct access_raw_concept_map : make_concept_map< ConceptForm >{};

} // namespace argot

#endif  // ARGOT_GEN_ACCESS_RAW_CONCEPT_MAP_HPP_
