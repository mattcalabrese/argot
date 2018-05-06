/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/parse_template_parameter.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/tuple/push_back.hpp>

////////////////////////////////////////////////////////////////////////////////
// template-parameter-list:                                                   //
//   template-parameter                                                       //
//   template-parameter-list , template-parameter                             //
////////////////////////////////////////////////////////////////////////////////

// TODO(mattcalabrese) Better error handling.

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( ... )                  \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_                                \
( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( __VA_ARGS__ ), __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_( t_param, ... )        \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL, t_param )               \
( t_param, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_PRED( d, state )   \
BOOST_PP_TUPLE_ELEM( 0, state )

// TODO(mattcalabrese) Parse comma and another template parameter.
#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP( d, state )     \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_                        \
( state                                                                        \
, ARGOT_GEN_DETAIL_PARSE_COMMA                                                 \
  ( BOOST_PP_TUPLE_ENUM( BOOST_PP_TUPLE_ELEM( 3, state ) ) )                   \
)

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_( state         \
                                                               , comma_parse   \
                                                               )               \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_, comma_parse )       \
( state, comma_parse )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_value(          \
                                                                   state       \
                                                                 , comma_parse \
                                                                 )             \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_NEXT                    \
( state, ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( comma_parse ) )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_NEXT( state     \
                                                                   , ...       \
                                                                   )           \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_NEXT_                   \
( state, ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_NEXT_(          \
                                                                    state      \
                                                                  , next_parse \
                                                                  )            \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_NEXT_, next_parse )   \
( state, next_parse )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_NEXT_value(     \
                                                                    state      \
                                                                  , next_parse \
                                                                  )            \
( 1, 1                                                                         \
, BOOST_PP_TUPLE_PUSH_BACK                                                     \
  ( BOOST_PP_TUPLE_ELEM( 2, state ), ARGOT_GEN_DETAIL_GET_NODE( next_parse ) ) \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( next_parse )              \
)

// TODO(mattcalabrese) Elaborate on error. Maybe make this a hard error.
#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_NEXT_unexpected(\
                                                                    state      \
                                                                  , next_parse \
                                                                  )            \
( 0, 1, BOOST_PP_TUPLE_ELEM( 2, state )                                        \
, (, ARGOT_GEN_DETAIL_GET_REMAINING_TEXT( next_parse ) )                       \
)

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP_unexpected(     \
                                                                   state       \
                                                                 , comma_parse \
                                                                 )             \
( 0, 1, BOOST_PP_TUPLE_ELEM( 2, state )                                        \
, ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( comma_parse )             \
)

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL( t_param, ... )    \
ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_COMPLETE                        \
( BOOST_PP_WHILE                                                               \
  ( ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_PRED                   \
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_IMPL_OP                     \
  , ( 1, 1, ( ARGOT_GEN_DETAIL_GET_NODE( t_param ) )                           \
    , ARGOT_GEN_DETAIL_GET_PARENTHESIZED_REMAINING_TEXT( t_param )             \
    )                                                                          \
  )                                                                            \
, __VA_ARGS__                                                                  \
)

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_COMPLETE( state, ... )  \
BOOST_PP_IIF                                                                   \
( BOOST_PP_TUPLE_ELEM( 1, state )                                              \
, ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_COMPLETE_SUCCESS              \
, ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_COMPLETE_FAILURE              \
)( state, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_COMPLETE_SUCCESS( state \
                                                                       , ...   \
                                                                       )       \
value( (), template_parameter_list BOOST_PP_TUPLE_ELEM( 2, state )             \
     , BOOST_PP_TUPLE_ELEM( 3, state )                                         \
     )

// TODO(mattcalabrese) Propagate hard failures
#define ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_COMPLETE_FAILURE( state \
                                                                       , ...   \
                                                                       )       \
unexpected( soft(), template_parameter_list, ( __VA_ARGS__ ) )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST_HPP_
