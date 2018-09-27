/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_SAME_TYPE_HPP_
#define ARGOT_CONCEPTS_SAME_TYPE_HPP_

//[description
/*`
SameType is an [argot_gen_concept] that is satisfied when all types that are
passed are the same type.
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

// TODO(mattcalabrese) Specialize up to 32 or 64

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/same_type.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T, class... U >
ARGOT_EXPLICIT_CONCEPT( SameType )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< SameType< T > > {};

template< class T >
struct make_concept_map
< SameType< T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T, T, T, T, T, T, T > > {};

template< class T >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T > > {};

template< class T, class U, class... V >
struct make_concept_map
< SameType< T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, U, V... >
, typename call_detail::detached_fast_enable_if< is_modeled_v< T, U, V... > >
  ::_::template apply<>
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_SAME_TYPE_HPP_
