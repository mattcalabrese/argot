/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TYPE_PARAMETER_KEY_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TYPE_PARAMETER_KEY_HPP_

#include <argot/gen/concept_body/detail/parse_keyword.hpp>

#define ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( ... )                       \
ARGOT_GEN_DETAIL_PARSE_KEYWORD                                                 \
( ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY_IMPL                               \
, type_parameter_key, __VA_ARGS__                                              \
)

#define ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY_IMPLclass class,
#define ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY_IMPLtypename typename,

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TYPE_PARAMETER_KEY_HPP_
