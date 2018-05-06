/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_COMMA_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_COMMA_HPP_

#include <argot/gen/concept_body/detail/variadic_identity.hpp>

#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/variadic/size.hpp>

#include <boost/vmd/is_empty.hpp>

#define ARGOT_GEN_DETAIL_IS_COMMA( ... )                                       \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL( 2, BOOST_PP_VARIADIC_SIZE( __VA_ARGS__ ) )                   \
, ARGOT_GEN_DETAIL_IS_COMMA_MAYBE                                              \
, ARGOT_GEN_DETAIL_VARIADIC_IDENTITY( 0 )                                      \
)( __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_IS_COMMA_MAYBE( a, b )                                \
BOOST_PP_BITAND( BOOST_VMD_IS_EMPTY( a ), BOOST_VMD_IS_EMPTY( b ) )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_COMMA_HPP_
