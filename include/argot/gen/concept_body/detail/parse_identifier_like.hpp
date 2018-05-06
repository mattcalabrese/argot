/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_IDENTIFIER_LIKE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_IDENTIFIER_LIKE_HPP_

#include <argot/gen/concept_body/detail/is_identifier_like.hpp>
#include <argot/gen/concept_body/detail/variadic_tail.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>

#define ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( node_kind, ... )               \
BOOST_PP_IIF                                                                   \
( ARGOT_GEN_DETAIL_IS_IDENTIFIER_LIKE                                          \
  ( BOOST_PP_VARIADIC_ELEM( 0, __VA_ARGS__ ) )                                 \
, BOOST_PP_IF( BOOST_PP_DEC( BOOST_PP_VARIADIC_SIZE( __VA_ARGS__ ) )           \
             , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE_IMPL_SUCCESS_PARTIAL     \
             , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE_IMPL_SUCCESS_FULL        \
             )                                                                 \
, ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE_IMPL_FAILURE                          \
)( node_kind, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE_IMPL_SUCCESS_FULL( node_kind    \
                                                                , identifier   \
                                                                )              \
value( ((node_kind), identifier ), () )

#define ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE_IMPL_SUCCESS_PARTIAL( node_kind \
                                                                   , ...       \
                                                                   )           \
value( ((node_kind), BOOST_PP_VARIADIC_ELEM( 0, __VA_ARGS__ ))                 \
     , (, ARGOT_GEN_DETAIL_VARIADIC_TAIL( __VA_ARGS__ ) )                      \
     )

#define ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE_IMPL_FAILURE( node_kind, ... )  \
unexpected( soft(), (node_kind), ( __VA_ARGS__ ) )

#endif // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_IDENTIFIER_LIKE_HPP_
