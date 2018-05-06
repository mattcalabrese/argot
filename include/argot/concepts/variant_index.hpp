/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_VARIANT_INDEX_HPP_
#define ARGOT_CONCEPTS_VARIANT_INDEX_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>
#include <argot/variant_traits/index_type.hpp>
#include <argot/variant_traits/num_alternatives.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/variant_index.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Variant, variant_traits::index_type_t< Variant > Index >
ARGOT_EXPLICIT_CONCEPT( VariantIndex )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class Variant, auto Index >
struct make_concept_map
< VariantIndex< Variant, Index >
, typename call_detail::detached_fast_enable_if
  < (    Index >= variant_traits::index_type_t< Variant >{ 0 }
      && Index < variant_traits::num_alternatives_v< Variant >
    )
  >::_::template apply<>
> {};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_VARIANT_INDEX_HPP_
