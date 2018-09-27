/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_GREATER_EQUAL_HPP_
#define ARGOT_CONCEPTS_GREATER_EQUAL_HPP_

//[description
/*`
Less is an [argot_gen_concept] that is satisfied for arguments `V` and `W`
where `V >= W` is `true`.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/true.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/requires.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/greater_equal.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< auto V, auto W >
ARGOT_EXPLICIT_CONCEPT( GreaterEqual )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< auto V, auto W >
struct make_concept_map
< GreaterEqual< V, W >
, ARGOT_REQUIRES( True< ( V >= W ) > )<>
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_GREATER_EQUAL_HPP_
