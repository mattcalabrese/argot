/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_INVOCABLE_OBJECT_WITH_PROVISION_HPP_
#define ARGOT_CONCEPTS_INVOCABLE_OBJECT_WITH_PROVISION_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/invocable_object_with_kinds.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov/group.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace detail_invocable_object_with_provision {

template< class Invocable, class... Providers >
struct invocable_object_with_provision_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < InvocableObjectWithKinds
        < Invocable
        , prov_traits::argument_list_kinds_of_destructive_t
          < prov::result_of_group_t< Providers&&... > >
        >
      >;
};

} // namespace argot(::detail_invocable_object_with_provision)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/invocable_object_with_provision.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... Providers >
ARGOT_AUTO_CONCEPT( InvocableObjectWithProvision )
(
  PotentiallyInvocableObject< Invocable >
, ArgumentProvider< Providers >...
, TransparentRequirement
  < detail_invocable_object_with_provision
    ::invocable_object_with_provision_requirements
    < Invocable, Providers... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_INVOCABLE_OBJECT_WITH_PROVISION_HPP_
