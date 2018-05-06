/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_KEYWORD_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_KEYWORD_HPP_

#include <argot/gen/concept_body/detail/is_type_like.hpp>
#include <argot/gen/concept_body/detail/variadic_cat.hpp>
#include <argot/gen/concept_body/detail/variadic_tail.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/vmd/is_empty.hpp>

#define ARGOT_GEN_DETAIL_PARSE_KEYWORD( macro_base, node_kind, ... )           \
BOOST_PP_IIF                                                                   \
( ARGOT_GEN_DETAIL_IS_TYPE_LIKE( __VA_ARGS__ )                                 \
, ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL                                          \
, ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL_EARLY_FAILURE                            \
)( macro_base, node_kind, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL_EARLY_FAILURE( macro_base          \
                                                         , node_kind, ...      \
                                                         )                     \
unexpected( soft(), (node_kind), ( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL( macro_base, node_kind, ... )      \
ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL_                                           \
( macro_base, node_kind                                                        \
, ( ARGOT_GEN_DETAIL_VARIADIC_CAT( macro_base, __VA_ARGS__ ) )                 \
, __VA_ARGS__                                                                  \
)

#define ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL_( macro_base, node_kind, cat_res   \
                                            , ...                              \
                                            )                                  \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_PP_VARIADIC_SIZE( __VA_ARGS__ )                                      \
  , BOOST_PP_TUPLE_SIZE( cat_res )                                             \
  )                                                                            \
, ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL_FAILURE                                  \
, ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL_SUCCESS                                  \
)( macro_base, node_kind, cat_res, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL_FAILURE( macro_base, node_kind     \
                                                   , cat_res, ...              \
                                                   )                           \
unexpected( soft(), (node_kind), ( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_KEYWORD_IMPL_SUCCESS( macro_base, node_kind     \
                                                   , cat_res, ...              \
                                                   )                           \
value                                                                          \
( node_kind                                                                    \
, ( ARGOT_GEN_DETAIL_VARIADIC_TAIL cat_res )                                   \
)

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_KEYWORD_HPP_
