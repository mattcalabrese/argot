/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_STREAM_INSERTABLE_HPP_
#define ARGOT_CONCEPTS_STREAM_INSERTABLE_HPP_

//[description
/*`
StreamInsertable is an [argot_gen_concept] that is satisfied if a left-shift
operation is supported for an UnqualifiedObject type "Stream", as an lvalue for
the left-hand operand, and an object of type `P` for the right-hand operand.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/concepts/valid.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/requires.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/declval.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace detail_stream_insertable {

template< class Stream, class P >
using insertion_expression
  = decltype( ARGOT_DECLVAL( Stream& ) << ARGOT_DECLVAL( P ) );

} // namespace argot(::detail_stream_insertable)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/stream_insertable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Stream, class P >
ARGOT_EXPLICIT_CONCEPT( StreamInsertable )
(
  UnqualifiedObject< Stream >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class Stream, class P >
struct make_concept_map
< StreamInsertable< Stream, P >
, ARGOT_REQUIRES
  ( UnqualifiedObject< Stream > )
  ( Valid< detail_stream_insertable::insertion_expression, Stream, P > )
  <>
> {};


} // namespace argot

#endif // ARGOT_CONCEPTS_STREAM_INSERTABLE_HPP_
