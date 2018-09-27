/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_DECAYED_TYPE_HPP_
#define ARGOT_CONCEPTS_DECAYED_TYPE_HPP_

//[description
/*`
DecayedType is an [argot_gen_concept] that is satisfied by each type `T` for
which `std::decay_t< T >` is the same type as `T`.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/decayed_type.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( DecayedType )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< DecayedType< T >
, call_detail::fast_enable_if_t< std::is_same_v< T, std::decay_t< T > > >
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_DECAYED_TYPE_HPP_
