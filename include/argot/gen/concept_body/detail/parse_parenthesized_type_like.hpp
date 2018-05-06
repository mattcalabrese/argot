/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_HPP_

#include <argot/gen/concept_body/detail/is_type_like.hpp>
#include <argot/gen/concept_body/detail/parenthesized_part.hpp>
#include <argot/gen/concept_body/detail/parse_type_like.hpp>
#include <argot/gen/concept_body/detail/part_after_parentheses.hpp>
#include <argot/gen/concept_body/detail/part_in_parentheses.hpp>

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE( node_kind, ... )       \
BOOST_PP_IIF                                                                   \
( BOOST_PP_IS_BEGIN_PARENS( __VA_ARGS__ )                                      \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL                          \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_NO_PAREN                  \
)( node_kind, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL( node_kind, ... )  \
BOOST_PP_IIF                                                                   \
( ARGOT_GEN_DETAIL_IS_TYPE_LIKE                                                \
  ( ARGOT_GEN_DETAIL_PART_IN_PARENTHESES( __VA_ARGS__ ) )                      \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_SUCCESS                  \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_FAILURE                  \
)( node_kind, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_SUCCESS( node_kind \
                                                                   , ...       \
                                                                   )           \
value( ( left_parenthesis_token                                                \
       , ((node_kind), ARGOT_GEN_DETAIL_PART_IN_PARENTHESES( __VA_ARGS__ ))    \
       , right_parenthesis_token                                               \
       )                                                                       \
     , ( ARGOT_GEN_DETAIL_PART_AFTER_PARENTHESES( __VA_ARGS__ ) )              \
     )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_NO_PAREN(          \
                                                                     node_kind \
                                                                   , ...       \
                                                                   )           \
unexpected( soft(), (left_parenthesis_token), ( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_IMPL_FAILURE( node_kind \
                                                                   , ...       \
                                                                   )           \
unexpected( soft(), (node_kind), ( __VA_ARGS__ ) )

#endif // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE_HPP_
