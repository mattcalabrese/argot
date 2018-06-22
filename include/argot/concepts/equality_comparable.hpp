/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EQUALITY_COMPARABLE_HPP_
#define ARGOT_CONCEPTS_EQUALITY_COMPARABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/declval.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace detail_equality_comparable {

// TODO(mattcalabrese) Make sure contextually convertible to bool

template< class T >
using equality_expression
  = decltype
    (   ( ARGOT_DECLVAL( T const& ) == ARGOT_DECLVAL( T const& ) )
      ? true : false
    );

template< class T >
using inequality_expression
  = decltype
    (   ( ARGOT_DECLVAL( T const& ) != ARGOT_DECLVAL( T const& ) )
      ? true : false
    );

} // namespace argot(::detail_equality_comparable)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/equality_comparable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( EqualityComparable )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

// TODO(mattcalabrese) Possibly also check !=
template< class T >
struct make_concept_map
< EqualityComparable< T >
, typename call_detail::detached_fast_enable_if
  < call_detail::is_detected_v
    < detail_equality_comparable::equality_expression< T > >
  >::_::template and_
  < call_detail::is_detected_v
    < detail_equality_comparable::inequality_expression< T > >
  >::_::template apply<>
> {};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_EQUALITY_COMPARABLE_HPP_
