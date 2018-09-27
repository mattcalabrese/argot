/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_UNION_INDEX_HPP_
#define ARGOT_CONCEPTS_UNION_INDEX_HPP_

//[description
/*`
UnionIndex is an [argot_gen_concept] for determining if a value is a valid
index for the given UnionLike type.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>
#include <argot/union_traits/index_type.hpp>
#include <argot/union_traits/num_alternatives.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/union_index.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Union, union_traits::index_type_t< Union > Index >
ARGOT_EXPLICIT_CONCEPT( UnionIndex )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class Union, auto Index >
struct make_concept_map
< UnionIndex< Union, Index >
, typename call_detail::detached_fast_enable_if
  < (    Index >= union_traits::index_type_t< Union >{ 0 }
      && Index < union_traits::num_alternatives_v< Union >
    )
  >::_::template apply<>
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_UNION_INDEX_HPP_
