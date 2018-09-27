/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_TUPLE_INDEX_HPP_
#define ARGOT_CONCEPTS_TUPLE_INDEX_HPP_

//[description
/*`
TupleIndex is an [argot_gen_concept] for determining if a value is a valid
index for the given TupleLike type.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>
#include <argot/tuple_traits/index_type.hpp>
#include <argot/tuple_traits/num_elements.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/tuple_index.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Tup, tuple_traits::index_type_t< Tup > Index >
ARGOT_EXPLICIT_CONCEPT( TupleIndex )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class Tup, auto Index >
struct make_concept_map
< TupleIndex< Tup, Index >
, typename call_detail::detached_fast_enable_if
  < (    Index >= tuple_traits::index_type_t< Tup >{ 0 }
      && Index < tuple_traits::num_elements_v< Tup >
    )
  >::_::template apply<>
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_TUPLE_INDEX_HPP_
