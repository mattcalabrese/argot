/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_INVOCABLE_FROM_PROVISION_WITHOUT_REDUCTION_HPP_
#define ARGOT_CONCEPTS_INVOCABLE_FROM_PROVISION_WITHOUT_REDUCTION_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/invocable_with_kinds.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov_traits/argument_list_kinds_of.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace invocable_from_provision_without_reduction_detail {

template< class Invocable, class Provider >
struct invocable_with_possibilities
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < InvocableWithKinds
        < Invocable, prov_traits::argument_list_kinds_of_t< Provider > >
      >l
};

}  // namespace argot(::invocable_from_provision_without_reduction_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/invocable_from_provision_without_reduction.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Possibly don't require sinkability
// TODO(mattcalabrese) Fix the call to argument_list_kinds_of to not be ref
template< class Invocable, class Provider >
ARGOT_AUTO_CONCEPT( InvocableFromProvisionWithoutReduction )
(
  ArgumentProvider< remove_cvref_t< Provider > >
, Sinkable< Provider&& >
, TransparentRequirement
  < invocable_from_provision_without_reduction_detail
    ::invocable_with_possibilities< Invocable&&, Providers&& >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_INVOCABLE_FROM_PROVISION_WITHOUT_REDUCTION_HPP_
