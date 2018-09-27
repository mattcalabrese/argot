/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EXCEPTION_HPP_
#define ARGOT_CONCEPTS_EXCEPTION_HPP_

//[description
/*`
Exception is an [argot_gen_concept] that is satisfied by each type that can be
thrown as an exception.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/concepts/valid.hpp>
#include <argot/detail/exact_declval.hpp>
#include <argot/gen/auto_concept.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <utility>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace exception_concept_detail {

template< class T >
using can_throw_impl = decltype( throw argot_detail::exact_declval< T >() );

} // namespace argot(::exception_concept_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/exception.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_AUTO_CONCEPT( Exception )
(
  UnqualifiedObject< T >
, Valid< exception_concept_detail::can_throw_impl, T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_EXCEPTION_HPP_
