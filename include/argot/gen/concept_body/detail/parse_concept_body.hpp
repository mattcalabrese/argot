/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_BODY_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_BODY_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_concept_member_specification.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_type_like.hpp>
#include <argot/gen/concept_body/detail/parenthesized_part.hpp>
#include <argot/gen/concept_body/detail/part_after_parentheses.hpp>
#include <argot/gen/concept_body/detail/part_in_parentheses.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/vmd/is_empty.hpp>

// TODO(mattcalabrese) Better error reporting.

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY( ... )                             \
BOOST_PP_IIF                                                                   \
( BOOST_PP_IS_BEGIN_PARENS( __VA_ARGS__ )                                      \
, ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY_IMPL                                     \
, ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY_FAILURE                                  \
)( __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY_IMPL( ... )                        \
BOOST_PP_IIF                                                                   \
( BOOST_VMD_IS_EMPTY                                                           \
  ( ARGOT_GEN_DETAIL_PART_IN_PARENTHESES( __VA_ARGS__ ) )                      \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_EMPTY                    \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_NOT_EMPTY                \
)( __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_EMPTY( ... )       \
value( (), concept_body()                                                      \
     , ( ARGOT_GEN_DETAIL_PART_AFTER_PARENTHESES( __VA_ARGS__ ) )              \
     )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_NOT_EMPTY( ... )   \
ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_NOT_EMPTY_                 \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION                          \
  ( ARGOT_GEN_DETAIL_PART_IN_PARENTHESES( __VA_ARGS__ ) )                      \
, ARGOT_GEN_DETAIL_PART_AFTER_PARENTHESES( __VA_ARGS__ )                       \
)

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_NOT_EMPTY_( parse  \
                                                                      , ...    \
                                                                      )        \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_, parse )                \
( parse, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_value( parse, ... )\
BOOST_PP_IIF                                                                   \
( BOOST_VMD_IS_EMPTY                                                           \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( parse ) )                             \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_INTERNAL_SUCCESS         \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_FAIL_TRAILING            \
)( parse, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_INTERNAL_SUCCESS(  \
                                                                         parse \
                                                                       , ...   \
                                                                       )       \
value( ( ARGOT_GEN_DETAIL_GET_PARENTHESIZED_PARSED_INPUT( parse ) )            \
     , concept_body( ARGOT_GEN_DETAIL_GET_NODE( parse ) )                      \
     , ( __VA_ARGS__ )                                                         \
     )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_BODY_HPP_
