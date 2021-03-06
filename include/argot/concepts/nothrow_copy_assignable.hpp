/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_NOTHROW_COPY_ASSIGNABLE_HPP_
#define ARGOT_CONCEPTS_NOTHROW_COPY_ASSIGNABLE_HPP_

//[description
/*`
NothrowCopyAssignable is an [argot_gen_concept] that is satisfied by Object
types that have a copy-assignment operator that is `noexcept`.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/copy_assignable.hpp>
#include <argot/gen/explicit_concept.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>
#include <argot/gen/make_concept_map.hpp>

#include <type_traits>

#endif // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/nothrow_copy_assignable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( NothrowCopyAssignable )
(
  CopyAssignable< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< NothrowCopyAssignable< T >
, typename call_detail::detached_fast_enable_if
  < std::is_nothrow_copy_assignable_v< T > >::_::template and_
  < std::is_object_v< T > >::void_
> {};


} // namespace argot

#endif  // ARGOT_CONCEPTS_NOTHROW_COPY_ASSIGNABLE_HPP_
