/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_SAME_VALUE_HPP_
#define ARGOT_CONCEPTS_SAME_VALUE_HPP_

//[description
/*`
SameValue is an [argot_gen_concept] that is satisfied when all values that are
passed have the same type and value.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

// NOTE: Currently specialized to 16

// VODO(mattcalabrese) Specialize up to 32 or 64

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/same_value.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< auto V, auto... W >
ARGOT_EXPLICIT_CONCEPT( SameValue )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< auto V >
struct make_concept_map
< SameValue< V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V, V, V, V, V, V, V > > {};

template< auto V >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V > > {};

template< auto V, decltype( V ) W, decltype( V )... X >
struct make_concept_map
< SameValue< V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, W, X... >
, typename call_detail::detached_fast_enable_if< is_modeled_v< V, W, X... > >
  ::_::template apply<>
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_SAME_VALUE_HPP_
