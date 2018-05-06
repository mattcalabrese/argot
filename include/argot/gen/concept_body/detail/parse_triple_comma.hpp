/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TRIPLE_COMMA_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TRIPLE_COMMA_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA( ... )                             \
ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_1                                          \
( ARGOT_GEN_DETAIL_PARSE_COMMA( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_1( comma_parse )                   \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_1_, comma_parse )                        \
( comma_parse )

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_1_unexpected( comma_parse )        \
unexpected( soft(triple_comma), comma_token                                    \
          , ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( comma_parse )   \
          )

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_1_value( comma_parse )             \
ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_2                                          \
( ARGOT_GEN_DETAIL_PARSE_COMMA                                                 \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( comma_parse ) )                       \
)

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_2( comma_parse )                   \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_2_, comma_parse )                        \
( comma_parse )

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_2_unexpected( comma_parse )        \
unexpected( soft((triple_comma, comma_token)), comma_token                     \
          , ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( comma_parse )   \
          )

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_2_value( comma_parse )             \
ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_3                                          \
( ARGOT_GEN_DETAIL_PARSE_COMMA                                                 \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( comma_parse ) )                       \
)

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_3( comma_parse )                   \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_3_, comma_parse )                        \
( comma_parse )

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_3_unexpected( comma_parse )        \
unexpected( soft((triple_comma, comma_token, comma_token)), comma_token        \
          , ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( comma_parse )   \
          )

#define ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA_3_value( comma_parse )             \
value( (triple_comma, comma_token, comma_token, comma_token)                   \
     , ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT(comma_parse)          \
     )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TRIPLE_COMMA_HPP_
