/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TEMPLATE_PARAMETER_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TEMPLATE_PARAMETER_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_identifier_like.hpp>
#include <argot/gen/concept_body/detail/parse_triple_comma.hpp>
#include <argot/gen/concept_body/detail/parse_type_parameter_key.hpp>

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

////////////////////////////////////////////////////////////////////////////////
// template-parameter:                                                        //
//   ((concept-id))?,,, ?identifier-like                                      //
//   ((concept-id)) ?identifier-like, default(type-like)                      //
//   type-parameter-key ?,,, ?identifier-like                                 //
//   type-parameter-key ?identifier-like, default(type-like)                  //
//   (~~token-soup~~)?,,, ?identifier-like                                    //
//   (~~token-soup~~) ?identifier-like, default(type-like)                    //
////////////////////////////////////////////////////////////////////////////////

// TODO(mattcalabrese) Handle parenthesized things and ((concept-id)).
// TODO(mattcalabrese) Parse default.
// TODO(mattcalabrese) Make parameter names optional.
#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( ... )                       \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_                                     \
( ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_( key_parse )                \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_, key_parse )                      \
( key_parse )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_value( key_parse )           \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_CHECK_VARIADIC                       \
( key_parse                                                                    \
, ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA                                          \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( key_parse ) )                         \
)

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_unexpected( key_parse )      \
unexpected                                                                     \
( soft(), template_parameter                                                   \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( key_parse )               \
)

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_CHECK_VARIADIC( lead_parse   \
                                                                , elips_parse  \
                                                                )              \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_ELIPSIS_, elips_parse )            \
( lead_parse, elips_parse )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_ELIPSIS_value( lead_parse    \
                                                               , elips_parse   \
                                                               )               \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_IMPL_NAME                            \
( lead_parse, 1                                                                \
, ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE                                       \
  ( name, ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( elips_parse ) )                 \
)

// TODO(mattcalabrese) Handle hard erros (i.e. 2 adjacent commas)
#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_ELIPSIS_unexpected(          \
                                                                 lead_parse    \
                                                               , elips_parse   \
                                                               )               \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_IMPL_NAME                            \
( lead_parse, 0                                                                \
, ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE                                       \
  ( name, ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( elips_parse ) )                 \
)

// TODO(mattcalabrese) Define what happens on unexpected
#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_IMPL_NAME( lead_parse        \
                                                           , is_variadic       \
                                                           , name_parse        \
                                                           )                   \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_IMPL_NAME_, name_parse )           \
( lead_parse, is_variadic, name_parse )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_IMPL_NAME_value( lead_parse  \
                                                                 , is_variadic \
                                                                 , name_parse  \
                                                                 )             \
value                                                                          \
( ()                                                                           \
, template_parameter                                                           \
  ( ARGOT_GEN_DETAIL_GET_NODE( lead_parse ), variadic( is_variadic )           \
  , ARGOT_GEN_DETAIL_GET_NODE( name_parse )                                    \
    /*default*/                                                                \
  )                                                                            \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( name_parse )              \
)

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_HPP_
