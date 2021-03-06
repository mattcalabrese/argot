/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EXECUTOR_HPP_
#define ARGOT_CONCEPTS_EXECUTOR_HPP_

//[description
/*`
Executor is an [argot_gen_concept] for types that support an `execute`
operation, which is a higher-order function that executes a nullary Invocable on
some thread of execution.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/gen/explicit_concept.hpp>

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/executor.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Don't require move constructible
template< class Exec >
ARGOT_EXPLICIT_CONCEPT( Executor )
( UnqualifiedObject< Exec >
, CopyConstructible< Exec >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_EXECUTOR_HPP_
