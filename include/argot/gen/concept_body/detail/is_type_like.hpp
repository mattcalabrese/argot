/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_TYPE_LIKE_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_TYPE_LIKE_HPP_

#include <argot/gen/concept_body/detail/zero.hpp>

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/vmd/is_empty.hpp>

// TODO(mattcalabrese)
//   Possibly search for no adjacent commas no empty after last comma.

#define ARGOT_GEN_DETAIL_IS_TYPE_LIKE_IMPL_NOT_EMPTY( ... )                    \
BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( __VA_ARGS__ ) )

#define ARGOT_GEN_DETAIL_IS_TYPE_LIKE( ... )                                   \
BOOST_PP_IIF( BOOST_VMD_IS_EMPTY( BOOST_PP_VARIADIC_ELEM( 0, __VA_ARGS__ ) )   \
            , ARGOT_GEN_DETAIL_ZERO                                            \
            , ARGOT_GEN_DETAIL_IS_TYPE_LIKE_IMPL_NOT_EMPTY                     \
            )( __VA_ARGS__ )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_IS_TYPE_LIKE_HPP_
