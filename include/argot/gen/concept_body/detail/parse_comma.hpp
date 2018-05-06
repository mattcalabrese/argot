/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_COMMA_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_COMMA_HPP_

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/vmd/is_empty.hpp>

#define ARGOT_GEN_DETAIL_PARSE_COMMA_IMPL_SUCCESS( ... )                       \
value( comma_token, BOOST_PP_TUPLE_POP_FRONT( ( __VA_ARGS__ ) ) )

#define ARGOT_GEN_DETAIL_PARSE_COMMA_IMPL_FAILURE( ... )                       \
unexpected( soft(), ( comma_token ), ( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_PARSE_COMMA_IMPL( ... )                               \
BOOST_PP_IIF( BOOST_VMD_IS_EMPTY( BOOST_PP_VARIADIC_ELEM( 0, __VA_ARGS__ ) )   \
            , ARGOT_GEN_DETAIL_PARSE_COMMA_IMPL_SUCCESS                        \
            , ARGOT_GEN_DETAIL_PARSE_COMMA_IMPL_FAILURE                        \
            )( __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_PARSE_COMMA( ... )                                    \
BOOST_PP_IF( BOOST_PP_DEC( BOOST_PP_VARIADIC_SIZE( __VA_ARGS__ ) )             \
           , ARGOT_GEN_DETAIL_PARSE_COMMA_IMPL                                 \
           , ARGOT_GEN_DETAIL_PARSE_COMMA_IMPL_FAILURE                         \
           )( __VA_ARGS__ )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_COMMA_HPP_
