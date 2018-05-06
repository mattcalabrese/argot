/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_GROUP_PARSE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_GROUP_PARSE_HPP_

// TODO(mattcalabrese) Make this re-entrant
#define ARGOT_GEN_DETAIL_GROUP_PARSE( parser_macro_tuple, ... )                \
( BOOST_PP_VARIADIC_ELEM( 0, __VA_ARGS__ )  )

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_EXPAND( ... ) __VA_ARGS__

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_1( parser_macro_tuple, ... )         \
BOOST_PP_TUPLE_ELEM( 0, parser_macro_tuple )( __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_2_( parser_macro_tuple, value )      \

#define ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_2( parser_macro_tuple, ... )         \
ARGOT_GEN_DETAIL_EXPECTED_BIND                                                 \
( ARGOT_GEN_DETAIL_GROUP_PARSE_IMPL_1                                          \
  ( BOOST_PP_TUPLE_POP_BACK( parser_macro_tuple ) )                            \
BOOST_PP_TUPLE_ELEM( 1, parser_macro_tuple )( __VA_ARGS__ )


#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_GROUP_PARSE_HPP_
