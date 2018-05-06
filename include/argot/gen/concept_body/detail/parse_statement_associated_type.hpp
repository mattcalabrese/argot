/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_STATEMENT_ASSOCIATED_TYPE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_STATEMENT_ASSOCIATED_TYPE_HPP_

#define ARGOT_GEN_DETAIL_PARSE_STATEMENT_ASSOCIATED_TYPE( ... )                \
ARGOT_GEN_DETAIL_GROUP_PARSE                                                   \
( ARGOT_GEN_DETAIL_DISJUNCTION_PARSE                                           \
  ( ( typename, ARGOT_GEN_DETAIL_PARSE_TYPENAME )                              \
  , ( constrained_typename, ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_TYPENAME )      \
  )                                                                            \
, ARGOT_GEN_DETAIL_OPTIONAL_PARSE                                              \
  ( ARGOT_GEN_DETAIL_ASSERT_GROUP_PARSE                                        \
    ( ARGOT_GEN_DETAIL_PARSE_DEFAULT                                           \
    , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE                           \
    )                                                                          \
  )                                                                            \
, ARGOT_GEN_DETAIL_PARSE_COMMA                                                 \
)

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_STATEMENT_ASSOCIATED_TYPE_HPP_
