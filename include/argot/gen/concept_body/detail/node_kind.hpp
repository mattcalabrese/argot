/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_NODE_KIND_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_NODE_KIND_HPP_

#include <argot/gen/concept_body/detail/result_of_parse.hpp>
#include <argot/gen/concept_body/detail/variadic_identity.hpp>
#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>

#define ARGOT_GEN_DETAIL_NODE_KIND_IDand( ... )                                0
#define ARGOT_GEN_DETAIL_NODE_KIND_IDassociated_requirements( ... )            1
#define ARGOT_GEN_DETAIL_NODE_KIND_IDauto( ... )                               2
#define ARGOT_GEN_DETAIL_NODE_KIND_IDclass( ... )                              3
#define ARGOT_GEN_DETAIL_NODE_KIND_IDcomma( ... )                              4
#define ARGOT_GEN_DETAIL_NODE_KIND_IDconcept( ... )                            5
#define ARGOT_GEN_DETAIL_NODE_KIND_IDconcept_member_specification( ... )       6
#define ARGOT_GEN_DETAIL_NODE_KIND_IDconcept_member_specifier( ... )           7
#define ARGOT_GEN_DETAIL_NODE_KIND_IDconstrained_parameter_kind( ... )         8
#define ARGOT_GEN_DETAIL_NODE_KIND_IDname( ... )                               9
#define ARGOT_GEN_DETAIL_NODE_KIND_IDnot( ... )                               10
#define ARGOT_GEN_DETAIL_NODE_KIND_IDor( ... )                                11
#define ARGOT_GEN_DETAIL_NODE_KIND_IDrequires( ... )                          12
#define ARGOT_GEN_DETAIL_NODE_KIND_IDreturn( ... )                            13
#define ARGOT_GEN_DETAIL_NODE_KIND_IDrequirement( ... )                       14
#define ARGOT_GEN_DETAIL_NODE_KIND_IDrequirement_list( ... )                  15
#define ARGOT_GEN_DETAIL_NODE_KIND_IDrequires_clause( ... )                   16
#define ARGOT_GEN_DETAIL_NODE_KIND_IDtemplate( ... )                          17
#define ARGOT_GEN_DETAIL_NODE_KIND_IDtemplate_parameter( ... )                18
#define ARGOT_GEN_DETAIL_NODE_KIND_IDtemplate_parameter_list( ... )           19
#define ARGOT_GEN_DETAIL_NODE_KIND_IDtriple_comma( ... )                      20
#define ARGOT_GEN_DETAIL_NODE_KIND_IDtype_parameter_key( ... )                21
#define ARGOT_GEN_DETAIL_NODE_KIND_IDtypename( ... )                          22

#define ARGOT_GEN_DETAIL_NODE_KIND_DATAand( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAassociated_requirements( ... )          \
( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAauto( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAclass( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAcomma( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAconcept( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAconcept_member_specification( ... )     \
( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAconcept_member_specifier( ... )         \
( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAconstrained_parameter_kind( ... )       \
( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAname( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAnot( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAor( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATArequires( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAreturn( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATArequirement( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATArequirement_list( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATArequires_clause( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAtemplate_parameter( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAtemplate_parameter_list( ... )          \
( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAtemplate( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAtriple_comma( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAtype_parameter_key( ... ) ( __VA_ARGS__ )
#define ARGOT_GEN_DETAIL_NODE_KIND_DATAtypename( ... ) ( __VA_ARGS__ )

// TODO(mattcalabrese) Remove
#if 0

#define ARGOT_GEN_DETAIL_NODE_KIND_PARENTHESIZED_DATA( node_data )             \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_NODE_KIND_DATA, node_data )

#else

#define ARGOT_GEN_DETAIL_NODE_KIND_PARENTHESIZED_DATA( node )                  \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , BOOST_PP_TUPLE_POP_FRONT                                         \
            , ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS                            \
            )( node )

#endif

#define ARGOT_GEN_DETAIL_NODE_KIND_IS( expected_kind, valid_result )           \
BOOST_PP_EQUAL                                                                 \
( BOOST_PP_CAT                                                                 \
  ( ARGOT_GEN_DETAIL_NODE_KIND_ID                                              \
  , ARGOT_GEN_DETAIL_GET_NODE( valid_result )                                  \
  )                                                                            \
, BOOST_PP_CAT( ARGOT_GEN_DETAIL_NODE_KIND_ID, expected_kind )()               \
)

#define ARGOT_GEN_DETAIL_NODE_KIND_IS_NOT( expected_kind, valid_result )       \
BOOST_PP_NOT_EQUAL                                                             \
( BOOST_PP_CAT                                                                 \
  ( ARGOT_GEN_DETAIL_NODE_KIND_ID                                              \
  , ARGOT_GEN_DETAIL_GET_NODE( valid_result )                                  \
  )                                                                            \
, BOOST_PP_CAT( ARGOT_GEN_DETAIL_NODE_KIND_ID, expected_kind )()               \
)

#define ARGOT_GEN_DETAIL_UNEXPECTED_OR_NODE_KIND_IS( expected_kind, result )   \
BOOST_PP_IIF( ARGOT_GEN_DETAIL_EXPECTED_IS_UNEXPECTED( result )                \
            , ARGOT_GEN_DETAIL_VARIADIC_IDENTITY( 1 )                          \
            , ARGOT_GEN_DETAIL_NODE_KIND_IS                                    \
            )( expected_kind, result )

#define ARGOT_GEN_DETAIL_UNEXPECTED_OR_NODE_KIND_IS_NOT( expected_kind         \
                                                       , result                \
                                                       )                       \
BOOST_PP_IIF( ARGOT_GEN_DETAIL_EXPECTED_IS_UNEXPECTED( result )                \
            , ARGOT_GEN_DETAIL_VARIADIC_IDENTITY( 1 )                          \
            , ARGOT_GEN_DETAIL_NODE_KIND_IS_NOT                                \
            )( expected_kind, result )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_NODE_KIND_HPP_
