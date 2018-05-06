/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_FOR_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_FOR_HPP_

#include <boost/preprocessor/detail/auto_rec.hpp>

// NOTE: The method of recursion with which this file is used is based on the
//       method of recursion using in the Chaos preprocessor library.

// TODO(mattcalabrese) Finish implementing this.

#define ARGOT_GEN_DETAIL_FOR_S(s, m, n, ...) \
BOOST_PP_IF(n, ARGOT_GEN_DETAIL_FOR_I, EAT)( \
BOOST_PP_INC(s), m, BOOST_PP_DEC(n), __VA_ARGS__ \
) \
/**/
#define ARGOT_GEN_DETAIL_FOR_ID() ARGOT_GEN_DETAIL_FOR_S

#define ARGOT_GEN_DETAIL_FOR_I(s, m, n, ...) \
DEFER(SCAN)(s)( \
DEFER(ARGOT_GEN_DETAIL_FOR_ID)()( \
s, m, n, __VA_ARGS__ \
) \
) \
DEFER(m)(s, n, __VA_ARGS__) \
/**/

// ^^^ that's it, the whole REPEAT algorithm

// (recursive) usage

#define A(s, n, ...) \
( SCAN(s)(ARGOT_GEN_DETAIL_FOR_S(s, B, BOOST_PP_INC(n), __VA_ARGS__)) ) \
/**/
#define B(s, n, ...) __VA_ARGS__


#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_FOR_HPP_
