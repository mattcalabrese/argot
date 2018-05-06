/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARENTHESIZED_PART_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARENTHESIZED_PART_HPP_

#include <argot/gen/concept_body/detail/split_after_parentheses.hpp>

#include <boost/preprocessor/tuple/elem.hpp>

#define ARGOT_GEN_DETAIL_PARENTHESIZED_PART( ... )                             \
BOOST_PP_TUPLE_ELEM                                                            \
( 0, ( ARGOT_GEN_DETAIL_SPLIT_AFTER_PARENTHESES( __VA_ARGS__ ) ) )

#endif // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARENTHESIZED_PART_HPP_
