/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_STATEMENT_REQUIRES_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_STATEMENT_REQUIRES_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/node_kind.hpp>
#include <argot/gen/concept_body/detail/parse_and.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_type_like.hpp>
#include <argot/gen/concept_body/detail/parse_requires.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_PRED( d, parse_result )   \
BOOST_PP_TUPLE_ELEM( 0, parse_result )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP_unexpected(            \
                                                                  parse_result \
                                                                , and_result   \
                                                                )              \
( 0, parse_result )

// TODO(mattcalabrese) Lack of something proper after and is a fatal error.
#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP_MORE( parse_result     \
                                                            , next_result      \
                                                            )                  \
( ARGOT_GEN_DETAIL_EXPECTED_IS_VALUE( next_result )                            \
, parse_result /*TODO(mattcalabrese) form proper ast node*/                    \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP_value( parse_result    \
                                                             , and_result      \
                                                             )                 \
ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP_MORE                           \
( parse_result                                                                 \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE                               \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( and_result ) )                        \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP_( parse_result         \
                                                        , and_result           \
                                                        )                      \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP_                             \
, and_result                                                                   \
)( parse_result, and_result )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP( d, parse_result )     \
ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP_                               \
( BOOST_PP_TUPLE_ELEM( 1, parse_result )                                       \
, ARGOT_GEN_DETAIL_PARSE_AND                                                   \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT                                        \
    ( BOOST_PP_TUPLE_ELEM( 1, parse_result ) )                                 \
  )                                                                            \
)

#if 0

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST( data, d0, d1, remaining )\
ARGOT_GEN_DETAIL_PARSE_COMMA remaining

#else

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST( data, d0, node           \
                                                    , remaining                \
                                                    )                          \
BOOST_PP_WHILE                                                                 \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_PRED                            \
, ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST_OP                              \
, ( 1, value( d0, node, remaining ) )                                          \
)

#endif

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST( data, d0, node, remaining )   \
ARGOT_GEN_DETAIL_EXPECTED_BIND_0                                               \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_REST, "requirement list"             \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE                               \
  ( requirement, BOOST_PP_TUPLE_ENUM( remaining ) )                            \
)

#define ARGOT_GEN_DETAIL_PARSE_STATEMENT_REQUIRES( ... )                       \
ARGOT_GEN_DETAIL_EXPECTED_BIND_1                                               \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST, "requires statement"                \
, ARGOT_GEN_DETAIL_PARSE_REQUIRES( __VA_ARGS__ )                               \
)

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_STATEMENT_REQUIRES_HPP_
