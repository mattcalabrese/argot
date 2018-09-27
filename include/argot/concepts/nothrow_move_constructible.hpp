/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_
#define ARGOT_CONCEPTS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_

//[description
/*`
NothrowMoveConstructible is an [argot_gen_concept] that is satisfied by Object
types that have a move constructor that is `noexcept`.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/gen/explicit_concept.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/make_concept_map.hpp>

#include <new>
#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/nothrow_move_constructible.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( NothrowMoveConstructible )
(
  MoveConstructible< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< NothrowMoveConstructible< T >
, call_detail::fast_enable_if_t
  < noexcept( ::new( std::nothrow ) T( ARGOT_DECLVAL( T&& ) ) ) >
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_
