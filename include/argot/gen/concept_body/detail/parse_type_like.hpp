/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TYPE_LIKE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TYPE_LIKE_HPP_

#include <argot/gen/concept_body/detail/is_type_like.hpp>
#include <argot/gen/concept_body/detail/variadic_tail.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>

// TODO(mattcalabrese)
//   Possibly stop at first comma with emptiness after it.

#define ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE( node_kind, ... )                     \
BOOST_PP_IIF                                                                   \
( ARGOT_GEN_DETAIL_IS_TYPE_LIKE( __VA_ARGS__ )                                 \
, ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE_IMPL_SUCCESS_FULL                           \
, ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE_IMPL_FAILURE                                \
)( node_kind, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE_IMPL_SUCCESS_FULL( node_kind          \
                                                          , ...                \
                                                          )                    \
value( ((node_kind), __VA_ARGS__ ), () )

#define ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE_IMPL_FAILURE( node_kind, ... )        \
unexpected( soft(), (node_kind), ( __VA_ARGS__ ) )

#endif // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_TYPE_LIKE_HPP_
