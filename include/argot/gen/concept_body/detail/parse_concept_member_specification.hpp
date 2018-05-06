/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_concept_member_specifier.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/tuple/push_back.hpp>

// TODO(mattcalabrese) Avoid BOOST_PP_WHILE -- use BOOST_PP_IF style mechanisms.
// TODO(mattcalabrese) Better error reporting.
// TODO(mattcalabrese) Fix the unparsed text when encountering a middle failure.

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION( ... )             \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_                           \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_( spec_parse )     \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_IMPL, spec_parse )       \
( spec_parse )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_IMPL( spec_parse ) \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_COMPLETION                 \
( BOOST_PP_WHILE                                                               \
  ( ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_PRED                   \
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_OP                     \
  , ( 1, 1                                                                     \
    , ARGOT_GEN_DETAIL_GET_PARENTHESIZED_PARSED_INPUT( spec_parse )            \
    , ( ARGOT_GEN_DETAIL_GET_NODE( spec_parse ) )                              \
    , ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( spec_parse )          \
    )                                                                          \
  )                                                                            \
)

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_PRED( d, state )   \
BOOST_PP_TUPLE_ELEM( 0, state )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_OP( d, state )     \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_OP_                        \
( state                                                                        \
, ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER                              \
  BOOST_PP_TUPLE_ELEM( 4, state )                                              \
)

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_OP_( state, parse )\
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_OP_, parse )             \
( state, parse )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_OP_value( state    \
                                                                    , parse    \
                                                                    )          \
( 1                                                                            \
, 1                                                                            \
, ( BOOST_PP_TUPLE_ENUM( BOOST_PP_TUPLE_ELEM( 2, state ) )                     \
    ARGOT_GEN_DETAIL_GET_PARSED_INPUT( parse )                                 \
  )                                                                            \
, BOOST_PP_TUPLE_PUSH_BACK                                                     \
  ( BOOST_PP_TUPLE_ELEM( 3, state )                                            \
  , ARGOT_GEN_DETAIL_GET_NODE( parse )                                         \
  )                                                                            \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( parse )                   \
)

// TODO(mattcalabrese) Propagate hard errors.
#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_OP_unexpected(     \
                                                                         state \
                                                                       , parse \
                                                                       )       \
( 0                                                                            \
, 1                                                                            \
, BOOST_PP_TUPLE_ELEM( 2, state )                                              \
, BOOST_PP_TUPLE_ELEM( 3, state )                                              \
, BOOST_PP_TUPLE_ELEM( 4, state )                                              \
)

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_COMPLETION( state )\
BOOST_PP_IIF                                                                   \
( BOOST_PP_TUPLE_ELEM( 1, state )                                              \
, ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_COMPLETION_valid         \
, ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_COMPLETION_invalid       \
)( BOOST_PP_TUPLE_ELEM( 2, state )                                             \
 , BOOST_PP_TUPLE_ELEM( 3, state )                                             \
 , BOOST_PP_TUPLE_ELEM( 4, state )                                             \
 )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_COMPLETION_valid(  \
                                                                    input      \
                                                                  , nodes      \
                                                                  , remaining  \
                                                                  )            \
value( input, concept_member_specification nodes, remaining )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION_HPP_
