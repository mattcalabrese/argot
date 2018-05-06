/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_AND_HPP_
#define ARGOT_GEN_AND_HPP_

#include <argot/gen/auto_concept.hpp>

namespace argot {

// TODO(mattcalabrese) Make this a transparent requirement.
template< class... ConceptSpecs >
ARGOT_AUTO_CONCEPT( And )
(
  ConceptSpecs...
);

}  // namespace argot

#endif  // ARGOT_GEN_AND_HPP_
