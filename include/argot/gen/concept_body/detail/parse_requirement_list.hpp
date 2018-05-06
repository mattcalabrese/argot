/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIREMENT_LIST_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIREMENT_LIST_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/node_kind.hpp>
#include <argot/gen/concept_body/detail/parse_and.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_type_like.hpp>
#include <argot/gen/concept_body/detail/parse_requirement.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>
#include <argot/gen/concept_body/detail/variadic_stringize.hpp>

#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/tuple/push_back.hpp>

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_PRED( d, state )          \
BOOST_PP_TUPLE_ELEM( 0, state )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_unexpected(            \
                                                            , curr_reqs        \
                                                            , and_result       \
                                                            )                  \
( 0, 1, ~, curr_reqs                                                           \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( and_result )              \
)

// TODO(mattcalabrese) Elaborate on the error.
#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_MORE_unexpected(       \
                                                                , curr_reqs    \
                                                                , next_result  \
                                                                )              \
( 0, 0, hard( "Expected requirement after \"and\" in requirement-list: " )     \
, curr_reqs                                                                    \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( next_result )             \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_MORE_value(            \
                                                                , curr_reqs    \
                                                                , next_result  \
                                                                )              \
( 1, 1, ~                                                                      \
, BOOST_PP_TUPLE_PUSH_BACK                                                     \
  ( curr_reqs, ARGOT_GEN_DETAIL_GET_NODE_PARENTHESIZED_DATA( next_result ) )   \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( next_result )             \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_MORE( curr_reqs        \
                                                            , next_result      \
                                                            )                  \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_MORE_, next_result )         \
( curr_reqs, next_result )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_value( curr_reqs       \
                                                             , and_result      \
                                                             )                 \
ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_MORE                           \
( curr_reqs                                                                    \
, ARGOT_GEN_DETAIL_PARSE_REQUIREMENT                                           \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( and_result ) )                        \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_( curr_reqs            \
                                                        , and_result           \
                                                        )                      \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_                             \
, and_result                                                                   \
)( curr_reqs, and_result )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP( d, state )            \
ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP_                               \
( BOOST_PP_TUPLE_ELEM( 3, state )                                              \
, ARGOT_GEN_DETAIL_PARSE_AND BOOST_PP_TUPLE_ELEM( 4, state )                   \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_COMPLETION_VALID(         \
                                                                  parsed_input \
                                                                , curr_reqs    \
                                                                , rest         \
                                                                , text         \
                                                                )              \
value( parsed_input, requirement_list curr_reqs, rest )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_COMPLETION_INVALID(       \
                                                                     error_kind\
                                                                   , curr_reqs \
                                                                   , rest      \
                                                                   , text      \
                                                                   )           \
unexpected( error_kind, requirement_list, text )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_COMPLETION( state, text ) \
BOOST_PP_IIF                                                                   \
( BOOST_PP_TUPLE_ELEM( 1, state )                                              \
, ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_COMPLETION_VALID                \
, ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_COMPLETION_INVALID              \
)( BOOST_PP_TUPLE_ELEM( 2, state ), BOOST_PP_TUPLE_ELEM( 3, state )            \
 , BOOST_PP_TUPLE_ELEM( 4, state ), text                                       \
 )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_unexpected( parse_result )\
unexpected                                                                     \
( , ( requirement_list )                                                       \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( parse_result )            \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_value( parse_result )     \
ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_COMPLETION                        \
( BOOST_PP_WHILE                                                               \
  ( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_PRED                          \
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_OP                            \
  , ( 1                                                                        \
    , 1                                                                        \
    , ~                                                                        \
    , ( ARGOT_GEN_DETAIL_GET_NODE_PARENTHESIZED_DATA( parse_result ) )         \
    , ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( parse_result )        \
    )                                                                          \
  )                                                                            \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( parse_result )            \
)

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_( parse_result )               \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_IMPL_, parse_result )( parse_result )

#define ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST( ... )                         \
ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST_                                       \
( ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( __VA_ARGS__ ) )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_REQUIREMENT_LIST_HPP_
