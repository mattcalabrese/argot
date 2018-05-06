/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/parse_constrained_parameter_kind.hpp>
#include <argot/gen/concept_body/detail/parse_identifier_like.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_type_like.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/vmd/is_empty.hpp>

////////////////////////////////////////////////////////////////////////////////
// associated-type-or-template:                                               //
//   type-parameter-key identifier-like,                                      //
//   type-parameter-key identifier-like, default(type-like),                  //
//   template(~~token-soup~~) identifier-like,                                //
//   template(~~token-soup~~) identifier-like, default(type-like),            //
//   ((concept-id)) ?identifier-like,                                         //
//   ((concept-id)) identifier-like, default(type-like),                      //
////////////////////////////////////////////////////////////////////////////////

// NOTE: This doesn't handle the simple form of constrained associated types.
// NOTE: This doesn't handle associated templates.
// NOTE: This doesn't handle defaults.
// TODO(mattcalabrese): Better error reporting and hard errors.
#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE( ... )              \
ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_KEY                    \
( ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_KEY(           \
                                                                     key_parse \
                                                                   )           \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_KEY_                 \
, key_parse                                                                    \
)( key_parse )

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_KEY_(          \
                                                                     key_parse \
                                                                    )          \
ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_KEY_VALID              \
( key_parse                                                                    \
, ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE                                       \
  ( name, ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( key_parse ) )                   \
)

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_KEY_VALID(     \
                                                                    key_parse  \
                                                                  , id_parse   \
                                                                  )            \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_BEFORE_COMMA         \
, id_parse                                                                     \
)( key_parse, id_parse )

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_BEFORE_COMMA(  \
                                                                    key_parse  \
                                                                  , id_parse   \
                                                                  )            \
ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_BEFORE_COMMA_          \
( key_parse, id_parse                                                          \
, ARGOT_GEN_DETAIL_PARSE_COMMA                                                 \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( id_parse ) )                          \
)

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_BEFORE_COMMA_( \
                                                                   key_parse   \
                                                                 , id_parse    \
                                                                 , comma_parse \
                                                                 )             \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_SUCCESS              \
, comma_parse                                                                  \
)( key_parse, id_parse, comma_parse )

#define ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_IMPL_SUCCESS(       \
                                                                   key_parse   \
                                                                 , id_parse    \
                                                                 , comma_parse \
                                                                 )             \
value                                                                          \
( ( ARGOT_GEN_DETAIL_GET_PARSED_INPUT( key_parse )                             \
    ARGOT_GEN_DETAIL_GET_PARSED_INPUT( id_parse ),                             \
  )                                                                            \
, associated_type                                                              \
  ( ARGOT_GEN_DETAIL_GET_NODE( key_parse )                                     \
  , ARGOT_GEN_DETAIL_GET_NODE( id_parse )                                      \
  )                                                                            \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( comma_parse )             \
)

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE_HPP_
