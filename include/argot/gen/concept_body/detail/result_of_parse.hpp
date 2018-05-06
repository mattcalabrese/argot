/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_RESULT_OF_PARSE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_RESULT_OF_PARSE_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/unparse_node.hpp>

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Structure of result:                                                       //
//                                                                            //
// value( parsed_text_in_paren, ast, remaining_text_in_paren )                //
//                                                                            //
// -or-                                                                       //
//                                                                            //
// unexpected( soft() | hard("message"), expected_node, full_raw_text )       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// TODO(mattcalabrese) Add convenience macro for reporting a full parse.

#define ARGOT_GEN_DETAIL_GET_PARENTHESIZED_PARSED_INPUT( valid_result )        \
( ARGOT_GEN_DETAIL_GET_PARSED_INPUT( valid_result ) )

#define ARGOT_GEN_DETAIL_GET_PARSED_INPUT( valid_result )                      \
ARGOT_GEN_DETAIL_UNPARSE_NODE                                                  \
( BOOST_PP_TUPLE_ELEM                                                          \
  ( 0, ARGOT_GEN_DETAIL_GET_EXPECTED_VALUE( valid_result ) )                   \
)

#define ARGOT_GEN_DETAIL_GET_NODE( valid_result )                              \
BOOST_PP_TUPLE_ELEM( 0, ARGOT_GEN_DETAIL_GET_EXPECTED_VALUE( valid_result ) )

#define ARGOT_GEN_DETAIL_GET_NODE_DATA( valid_result )                         \
BOOST_PP_TUPLE_ENUM                                                            \
( ARGOT_GEN_DETAIL_GET_NODE_PARENTHESIZED_DATA( valid_result ) )

#define ARGOT_GEN_DETAIL_GET_NODE_PARENTHESIZED_DATA( valid_result )           \
ARGOT_GEN_DETAIL_NODE_KIND_PARENTHESIZED_DATA                                  \
( BOOST_PP_TUPLE_ELEM                                                          \
  ( 0, ARGOT_GEN_DETAIL_GET_EXPECTED_VALUE( valid_result ) )                   \
)

#define ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( parse_result )      \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT_, parse_result )           \
( parse_result )

#define ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT_value( parse_result )\
BOOST_PP_TUPLE_ELEM                                                            \
( 1, ARGOT_GEN_DETAIL_GET_EXPECTED_VALUE( parse_result ) )

#define ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT_unexpected(          \
                                                                 parse_result )\
BOOST_PP_TUPLE_ELEM                                                            \
( 2, ARGOT_GEN_DETAIL_GET_EXPECTED_UNEXPECTED( parse_result ) )

// TODO(mattcalabrese) Make this work for unexpected as well
#define ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( valid_result )                    \
BOOST_PP_TUPLE_ENUM                                                            \
( ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( valid_result ) )

#define ARGOT_GEN_DETAIL_GET_FAILURE_KIND( unexpected_result )                 \
BOOST_PP_TUPLE_ELEM                                                            \
( 0, ARGOT_GEN_DETAIL_GET_EXPECTED_UNEXPECTED( unexpected_result ) )

// Severity levels: soft, fatal

#define ARGOT_GEN_DETAIL_GET_FAILURE_EXPECTATION( unexpected_result )          \
BOOST_PP_TUPLE_ELEM                                                            \
( 1, ARGOT_GEN_DETAIL_GET_EXPECTED_UNEXPECTED( unexpected_result ) )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_RESULT_OF_PARSE_HPP_
