/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_IDENTIFIER_LIKE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_IDENTIFIER_LIKE_HPP_

#include <argot/gen/concept_body/detail/is_type_like.hpp>
#include <argot/gen/concept_body/detail/zero.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/variadic/size.hpp>

#define ARGOT_GEN_DETAIL_IS_IDENTIFIER_LIKE( ... )                             \
BOOST_PP_IF                                                                    \
( BOOST_PP_DEC( BOOST_PP_VARIADIC_SIZE( __VA_ARGS__ ) )                        \
, ARGOT_GEN_DETAIL_ZERO                                                        \
, ARGOT_GEN_DETAIL_IS_TYPE_LIKE                                                \
)( __VA_ARGS__ )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_IDENTIFIER_LIKE_HPP_
