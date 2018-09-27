/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_STLAB_EXECUTOR_HPP_
#define ARGOT_CONCEPTS_STLAB_EXECUTOR_HPP_

//[description
/*`
StlabExecutor is an [argot_gen_concept] that is satisfied by types that model
the [stlab_executor_concept].
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/gen/auto_concept.hpp>

namespace argot {
namespace detail_stlab_executor_concept {

struct function_archetype { void operator()() const; };

} // namespace argot(::detail_stlab_executor_concept)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/stlab_executor.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Require that it is callable with a nullary function
template< class StlabExec >
ARGOT_AUTO_CONCEPT( StlabExecutor )
( UnqualifiedObject< StlabExec >
, CopyConstructible< StlabExec >
, BasicCallableWith
  < StlabExec&, detail_stlab_executor_concept::function_archetype const& >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_STLAB_EXECUTOR_HPP_
