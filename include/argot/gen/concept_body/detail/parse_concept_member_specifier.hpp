/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_associated_requirements.hpp>
#include <argot/gen/concept_body/detail/parse_associated_type_or_template.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER( ... )                 \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER_                               \
( ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER_( reqs )               \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER_, reqs )                     \
( reqs )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER_value( reqs ) reqs

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER_unexpected( reqs )     \
ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE                             \
( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( reqs ) )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER_HPP_
