/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGOT_INVOCABLE_BEFORE_REDUCTION_HPP_
#define ARGOT_CONCEPTS_ARGOT_INVOCABLE_BEFORE_REDUCTION_HPP_

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>

#endif

#include <argot/concepts/can_default_to_reference_to.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/invocable_with_kinds.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

namespace argot {
namespace argot_invocable_before_reduction_detail {

template< class Invocable, class... P >
struct invocable_with_possibilities
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < InvocableWithKinds
        < Invocable
        , prov_traits::argument_list_kinds_of_destructive_t
          < prov::result_of_default_to_reference_to_t< P&&... > >
        >
      >;
};

}  // namespace argot(::argot_invocable_before_reduction_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/argot_invocable_before_reduction.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... P >
ARGOT_AUTO_CONCEPT( ArgotInvocableBeforeReduction )
(
  CanDefaultToReferenceTo< P&& >...
, TransparentRequirement
  < argot_invocable_before_reduction_detail::invocable_with_possibilities
    < Invocable&&, P&&... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_ARGOT_INVOCABLE_BEFORE_REDUCTION_HPP_
