/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_HPP_
#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parenthesized_part.hpp>
#include <argot/gen/concept_body/detail/parse_template_parameter_list.hpp>
#include <argot/gen/concept_body/detail/part_in_parentheses.hpp>
#include <argot/gen/concept_body/detail/part_after_parentheses.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/vmd/is_empty.hpp>

// TODO(mattcalabrese) Better failure reporting (i.e. trailing text at end).
// TODO(mattcalabrese) Make version that disallows empty lists.

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST( ... )    \
BOOST_PP_IIF                                                                   \
( BOOST_PP_IS_BEGIN_PARENS( __VA_ARGS__ )                                      \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_IMPL            \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_FAILURE         \
)( __VA_ARGS__ )

// TODO(mattcalabrese) split at parentheses
#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_IMPL(     \
                                                                           ... \
                                                                         )     \
ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_IMPL_             \
( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST                               \
  ( ARGOT_GEN_DETAIL_PART_IN_PARENTHESES( __VA_ARGS__ ) )                      \
, ( ARGOT_GEN_DETAIL_PART_AFTER_PARENTHESES( __VA_ARGS__ ) )                   \
)

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_IMPL_(    \
                                                                  params_parse \
                                                                , remaining    \
                                                                )              \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_                \
, params_parse                                                                 \
)( params_parse, remaining )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_value(    \
                                                                  params_parse \
                                                                , remaining    \
                                                                )              \
BOOST_PP_IIF                                                                   \
( BOOST_VMD_IS_EMPTY( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( params_parse ) )    \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_SUCCESS         \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_TRAILING        \
)( params_parse, remaining )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_SUCCESS(  \
                                                                  params_parse \
                                                                , remaining    \
                                                                )              \
value( ()                                                                      \
     , parenthesized_template_parameter_list                                   \
       ( ARGOT_GEN_DETAIL_GET_NODE_DATA( params_parse ) )                      \
     , remaining                                                               \
     )

#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_FAILURE(  \
                                                                           ... \
                                                                         )     \
unexpected( soft(), parenthesized_template_parameter_list, ( __VA_ARGS__ ) )

// TODO(mattcalabrese) Make this a hard error
#define ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_TRAILING( \
                                                                  params_parse \
                                                                , remaining    \
                                                                )              \
unexpected                                                                     \
( soft(), parenthesized_template_parameter_list                                \
, ( ( ARGOT_GEN_DETAIL_GET_PARSED_INPUT( params_parse )                        \
      ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( params_parse )                      \
    ) BOOST_PP_TUPLE_ENUM( remaining )                                         \
  )                                                                            \
)

#endif  // ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST_HPP_
