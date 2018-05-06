/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIREMENT_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIREMENT_HPP_

#include <argot/gen/concept_body/detail/parse_parenthesized_type_like.hpp>

// TODO(mattcalabrese) Support negative requirements.
// TODO(mattcalabrese) Support concept-instance-alias-def.
#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( ... )                              \
ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE( requirement, __VA_ARGS__ )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIREMENT_HPP_
