/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/parse_requires_clause.hpp>

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS( ... )                  \
ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_                                \
( ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE( __VA_ARGS__ )                        \
, ( __VA_ARGS__ )                                                              \
)

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_( clause_parse          \
                                                       , full_text             \
                                                       )                       \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_IMPL                          \
, clause_parse                                                                 \
)( clause_parse, full_text )

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_IMPL( clause_parse      \
                                                           , full_text         \
                                                           )                   \
ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_IMPL_COMMA                      \
( clause_parse                                                                 \
, ARGOT_GEN_DETAIL_PARSE_COMMA                                                 \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( clause_parse ) )                      \
, full_text                                                                    \
)

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_IMPL_COMMA(             \
                                                        clause_parse           \
                                                      , comma_parse, full_text \
                                                      )                        \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_IMPL_COMMA_, comma_parse )    \
( clause_parse, comma_parse, full_text )

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_IMPL_COMMA_value(       \
                                                        clause_parse           \
                                                      , comma_parse, full_text \
                                                      )                        \
value                                                                          \
( ( ARGOT_GEN_DETAIL_GET_PARSED_INPUT( clause_parse ), )                       \
, associated_requirements                                                      \
  ARGOT_GEN_DETAIL_GET_NODE_PARENTHESIZED_DATA( clause_parse )                 \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( comma_parse )             \
)

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_IMPL_COMMA_unexpected(  \
                                                        clause_parse           \
                                                      , comma_parse, full_text \
                                                      )                        \
unexpected                                                                     \
( hard                                                                         \
  ( "Expected a comma at the end of associated-requirements: "                 \
    /*TODO(mattcalabrese) Show clause exactly as user wrote it*/               \
  )                                                                            \
, associated_requirements, full_text                                           \
)

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS_HPP_
