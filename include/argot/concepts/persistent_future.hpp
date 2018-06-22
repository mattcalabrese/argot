/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_FUTURE_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_FUTURE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/concept_assert.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/fut_traits/config.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_future.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( PersistentFuture )
(
  Future< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

// This preprocessor block includes concept maps for all detected future-likes.
#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#ifdef ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION
#include <argot/concepts/persistent_future/detail/boost_shared_future.hpp>
#endif

#ifdef ARGOT_HAS_STLAB_FUTURE
#include <argot/concepts/persistent_future/detail/stlab_future.hpp>
#endif

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#endif  // ARGOT_CONCEPTS_PERSISTENT_FUTURE_HPP_
