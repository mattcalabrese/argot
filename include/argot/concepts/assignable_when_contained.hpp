/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ASSIGNABLE_WHEN_CONTAINED_HPP_
#define ARGOT_CONCEPTS_ASSIGNABLE_WHEN_CONTAINED_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/contained.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/assignable_when_contained.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T, class P >
ARGOT_EXPLICIT_CONCEPT( AssignableWhenContained )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T, class P >
struct make_concept_map
< AssignableWhenContained< T, P >
, std::void_t
  < decltype( ARGOT_DECLVAL( assign_contained_fn< T > const& )
              ( ARGOT_DECLVAL( contained< T >& ), 
                ARGOT_DECLVAL( P ) )
            )
  >
> {};


}  // namespace argot

#endif  // ARGOT_CONCEPTS_ASSIGNABLE_WHEN_CONTAINED_HPP_
