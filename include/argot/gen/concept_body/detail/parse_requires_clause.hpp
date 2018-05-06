/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIRES_CLAUSE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIRES_CLAUSE_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_requirement_list.hpp>
#include <argot/gen/concept_body/detail/parse_requires.hpp>

#define ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE( ... )                          \
ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_                                        \
( ARGOT_GEN_DETAIL_PARSE_REQUIRES( __VA_ARGS__ ), ( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_( requires_parse, full_text )   \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_IMPL                                  \
, requires_parse                                                               \
)( requires_parse, full_text )

#define ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_IMPL( requires_parse            \
                                                   , full_text                 \
                                                   )                           \
ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_IMPL_                                   \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST                                      \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( requires_parse ) )                    \
, full_text                                                                    \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_IMPL_( requirement_list_parse   \
                                                    , full_text                \
                                                    )                          \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_IMPL_, requirement_list_parse )       \
( requirement_list_parse, full_text )

// TODO(mattcalabrese) fatal error
#define ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_IMPL_unexpected(                \
                                                      requirement_list_parse   \
                                                    , full_text                \
                                                    )                          \
unexpected( , requires_clause, full_text )

#define ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE_IMPL_value(                     \
                                                      requirement_list_parse   \
                                                    , full_text                \
                                                    )                          \
value                                                                          \
( (requires ARGOT_GEN_DETAIL_GET_PARSED_INPUT(requirement_list_parse))         \
, requires_clause                                                              \
  ARGOT_GEN_DETAIL_GET_NODE_PARENTHESIZED_DATA( requirement_list_parse )       \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( requirement_list_parse )  \
)

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIRES_CLAUSE_HPP_
