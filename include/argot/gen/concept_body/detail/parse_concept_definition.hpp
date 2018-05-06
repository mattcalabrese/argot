/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_DEFINITION_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_DEFINITION_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_auto.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/parse_concept.hpp>
#include <argot/gen/concept_body/detail/parse_concept_body.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_identifier_like.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_template_parameter_list.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>
#include <argot/gen/concept_body/detail/variadic_empty.hpp>

#include <boost/preprocessor/control/iif.hpp>

#if 0
auto concept (Regular)( class T )
  (,) (SemiRegular)( T )
   ,  (Copyable)( T )
(
  requires foo<T>,
    requires (blah<T>) and (bloop<T>),
  requires ((blah<T>) and ,,,),

  typename result_type, default( int ),
)
#endif

// TODO(mattcalabrese) Better error reporting.
// TODO(mattcalabrese) Support declarations and share part of this parsing.
// TODO(mattcalabrese) Parse refinements clause.
#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION( ... )                       \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_                                     \
( ARGOT_GEN_DETAIL_PARSE_AUTO( __VA_ARGS__ )                                   \
)

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_( auto_parse )               \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_AUTO                           \
( auto( ARGOT_GEN_DETAIL_EXPECTED_IS_VALUE( auto_parse ) )                     \
, ARGOT_GEN_DETAIL_PARSE_CONCEPT                                               \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( auto_parse ) )                        \
)

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_AUTO( auto_node        \
                                                            , concept_parse    \
                                                            )                  \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_AUTO_, concept_parse )       \
( auto_node, concept_parse )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_AUTO_( auto_node       \
                                                             , concept_parse   \
                                                             )                 \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_NAME                           \
( auto_node                                                                    \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE                         \
  ( name, ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( concept_parse ) )               \
)

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_NAME( auto_node        \
                                                            , name_parse       \
                                                            )                  \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_NAME_, name_parse )          \
( auto_node, name_parse )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_NAME_( auto_node       \
                                                             , name_parse      \
                                                             )                 \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_PARAMS                         \
( auto_node, ARGOT_GEN_DETAIL_GET_NODE( name_parse )                           \
, ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST                 \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( name_parse ) )                        \
)

// TODO(mattcalabrese) Parse refinements here
#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_PARAMS( auto_node      \
                                                              , name_node      \
                                                              , params_parse   \
                                                              )                \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_PARAMS_, params_parse )      \
( auto_node, name_node, params_parse )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_PARAMS_( auto_node     \
                                                               , name_node     \
                                                               , params_parse  \
                                                               )               \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_BODY                           \
( auto_node, name_node, ARGOT_GEN_DETAIL_GET_NODE( params_parse )              \
, ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY                                          \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( params_parse ) )                      \
)

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_BODY( auto_node        \
                                                             , name_node       \
                                                             , params_node     \
                                                             , body_parse      \
                                                             )                 \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_BODY_, body_parse )          \
( auto_node, name_node, params_node, body_parse )

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_BODY_( auto_node       \
                                                             , name_node       \
                                                             , params_node     \
                                                             , body_parse      \
                                                             )                 \
ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_BODY_COMMA                     \
( auto_node, name_node, params_node, ARGOT_GEN_DETAIL_GET_NODE( body_parse )   \
, ARGOT_GEN_DETAIL_PARSE_COMMA                                                 \
  ( ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( body_parse ) )                        \
)

#define ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION_AFTER_BODY_COMMA(            \
                                                                  auto_node    \
                                                                , name_node    \
                                                                , params_node  \
                                                                , body_node    \
                                                                , comma_parse  \
                                                                )              \
value                                                                          \
( ()                                                                           \
, concept_definition                                                           \
  ( auto_node, name_node, params_node, body_node                               \
    BOOST_PP_IIF( ARGOT_GEN_DETAIL_EXPECTED_IS_VALUE( comma_parse )            \
                , ARGOT_GEN_DETAIL_TRAILING_COMMA_NODE                         \
                , ARGOT_GEN_DETAIL_VARIADIC_EMPTY                              \
                )()                                                            \
  )                                                                            \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( comma_parse )             \
)

#define ARGOT_GEN_DETAIL_TRAILING_COMMA_NODE() , comma()

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_CONCEPT_BODY_HPP_
