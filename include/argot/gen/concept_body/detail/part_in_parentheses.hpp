/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PART_IN_PARENTHESES_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PART_IN_PARENTHESES_HPP_

#include <argot/gen/concept_body/detail/parenthesized_part.hpp>

#include <boost/preprocessor/tuple/enum.hpp>

#define ARGOT_GEN_DETAIL_PART_IN_PARENTHESES( ... )                            \
BOOST_PP_TUPLE_ENUM                                                            \
( ARGOT_GEN_DETAIL_PARENTHESIZED_PART( __VA_ARGS__ ) )

#endif // ARGOT_GEN_CONCEPT_BODY_DETAIL_PART_IN_PARENTHESES_HPP_
