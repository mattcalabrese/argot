/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_GROUP_PARSE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_GROUP_PARSE_HPP_

#include <argot/gen/concept_body/detail/result_of_parse.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/tuple/pop_back.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/variadic/elem.hpp>

// TODO(mattcalabrese) Make this re-entrant

#define ARGOT_GEN_DETAIL_GROUP_PARSE( parser_macro_tuple, ... )                \
BOOST_PP_CAT                                                                   \
( ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_                                           \
, BOOST_PP_TUPLE_SIZE( parser_macro_tuple )                                    \
)( parser_macro_tuple, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_EXPAND( ... ) __VA_ARGS__

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_1( parser_macro_tuple, ... )         \
BOOST_PP_TUPLE_ELEM( 0, parser_macro_tuple )( __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_2_( macro, dummy1, dummy2, rest )    \
ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_EXPAND( macro rest )

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_2( parser_macro_tuple, ... )         \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_2_                                         \
, BOOST_PP_TUPLE_ELEM( 1, parser_macro_tuple )                                 \
, ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_1                                          \
  ( BOOST_PP_TUPLE_POP_BACK( parser_macro_tuple ), __VA_ARGS__ )               \
)

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_3_( macro, dummy1, dummy2, rest )    \
ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_EXPAND( macro rest )

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_3( parser_macro_tuple, ... )         \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_3_                                         \
, BOOST_PP_TUPLE_ELEM( 2, parser_macro_tuple )                                 \
, ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_2                                          \
  ( BOOST_PP_TUPLE_POP_BACK( parser_macro_tuple ), __VA_ARGS__ )               \
)

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_4_( macro, dummy1, dummy2, rest )    \
ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_EXPAND( macro rest )

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_4( parser_macro_tuple, ... )         \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_4_                                         \
, BOOST_PP_TUPLE_ELEM( 3, parser_macro_tuple )                                 \
, ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_3                                          \
  ( BOOST_PP_TUPLE_POP_BACK( parser_macro_tuple ), __VA_ARGS__ )               \
)

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_5_( macro, dummy1, dummy2, rest )    \
ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_EXPAND( macro rest )

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_5( parser_macro_tuple, ... )         \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_5_                                         \
, BOOST_PP_TUPLE_ELEM( 4, parser_macro_tuple )                                 \
, ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_4                                          \
  ( BOOST_PP_TUPLE_POP_BACK( parser_macro_tuple ), __VA_ARGS__ )               \
)

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_GROUP_PARSE_HPP_
