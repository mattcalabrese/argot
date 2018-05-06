/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGOT_INVOCABLE_HPP_
#define ARGOT_CONCEPTS_ARGOT_INVOCABLE_HPP_

#include <argot/concepts/argot_invocable_before_reduction.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

namespace argot {
namespace argot_invocable_detail {

template< class Invocable, class... P >
struct all_return_types_are_the_same_requirement
{
  template< template< class... > class Reqs >
  using expand_requirements
    = SameType< /*invocation results*/ >;
};

}  // namespace argot(::argot_invocable_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME() s/argot_invocable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... P >
ARGOT_AUTO_CONCEPT( ArgotInvocable )
(
  ArgotInvocableBeforeReduction< Invocable, P... >
/*, check that all return types are the same*/
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_ARGOT_INVOCABLE_HPP_
