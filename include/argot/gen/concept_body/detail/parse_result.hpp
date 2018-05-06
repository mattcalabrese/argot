/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_RESULT_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_RESULT_HPP_

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>

#define ARGOT_GEN_DETAIL_MAKE_PARSE_RESULT( dummy1, dummy2, remaining_text )   \
( dummy1, dummy2, remaining_text )

#define ARGOT_GEN_DETAIL_GET_PARSE_RESULT_REMAINING_TEXT( parse_result )       \
BOOST_PP_TUPLE_ENUM( BOOST_PP_TUPLE_ELEM( 2, remaining_text ) )

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_RESULT_HPP_
