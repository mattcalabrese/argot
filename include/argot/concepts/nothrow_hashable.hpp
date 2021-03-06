/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_NOTHROW_HASHABLE_HPP_
#define ARGOT_CONCEPTS_NOTHROW_HASHABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/hashable.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#include <cstddef>
#include <functional>
#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/nothrow_hashable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( NothrowHashable )
(
  Hashable< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< NothrowHashable< T >
, typename call_detail::detached_fast_enable_if
  < std::is_object_v< T > >::_::template and_
  < std::is_same_v
    < decltype( std::hash< T >()( ARGOT_DECLVAL( T const& ) ) ), std::size_t >
  >::_::template and_
  < noexcept( std::hash< T >()( ARGOT_DECLVAL( T const& ) ) ) >::void_
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_NOTHROW_HASHABLE_HPP_
