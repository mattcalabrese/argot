/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PART_AFTER_PARENTHESES_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PART_AFTER_PARENTHESES_HPP_

#include <argot/gen/concept_body/detail/split_after_parentheses.hpp>

#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>

#define ARGOT_GEN_DETAIL_PART_AFTER_PARENTHESES( ... )                         \
BOOST_PP_TUPLE_ENUM                                                            \
( BOOST_PP_TUPLE_POP_FRONT                                                     \
 ( ( ARGOT_GEN_DETAIL_SPLIT_AFTER_PARENTHESES( __VA_ARGS__ ) ) )               \
)

#endif // ARGOT_GEN_CONCEPT_BODY_DETAIL_PART_AFTER_PARENTHESES_HPP_
