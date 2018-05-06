/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>
#include <argot/gen/concept_body/detail/parenthesized_part.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_identifier_like.hpp>
#include <argot/gen/concept_body/detail/part_after_parentheses.hpp>
#include <argot/gen/concept_body/detail/part_in_parentheses.hpp>

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>

// TODO(mattcalabrese) Better error reporting

#define ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND( ... )               \
BOOST_PP_IIF                                                                   \
( BOOST_PP_IS_BEGIN_PARENS( __VA_ARGS__ )                                      \
, ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_IMPL                       \
, ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_FAILURE                    \
)( __VA_ARGS__ )

// TODO(mattcalabrese) split at parentheses
#define ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_IMPL( ... )          \
ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_IMPL_                        \
( ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE                         \
  ( constrained_parameter_kind                                                 \
  , ARGOT_GEN_DETAIL_PART_IN_PARENTHESES( __VA_ARGS__ )                        \
  )                                                                            \
, __VA_ARGS__                                                                  \
)

#define ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_IMPL_( id_result     \
                                                               , ...           \
                                                               )               \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_IMPL_SUCCESS               \
, id_result                                                                    \
)( id_result, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_IMPL_SUCCESS(        \
                                                                     id_result \
                                                                   , ...       \
                                                                   )           \
value( (ARGOT_GEN_DETAIL_GET_PARENTHESIZED_PARSED_INPUT( id_result ))          \
     , constrained_parameter_kind                                              \
       ARGOT_GEN_DETAIL_GET_NODE_PARENTHESIZED_DATA( id_result )               \
     , ( ARGOT_GEN_DETAIL_PART_AFTER_PARENTHESES( __VA_ARGS__ ) )              \
     )

#define ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_IMPL_FAILURE( ... )  \
unexpected( soft(), constrained_parameter_kind, ( __VA_ARGS__ ) )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND_HPP_
