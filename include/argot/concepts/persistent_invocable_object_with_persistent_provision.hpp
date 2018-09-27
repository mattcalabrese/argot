/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_INVOCABLE_OBJECT_WITH_PERSISTENT_PROVISION_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_INVOCABLE_OBJECT_WITH_PERSISTENT_PROVISION_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/invocable_object_with_provision.hpp>
#include <argot/concepts/persistent_invocable_object_with_kinds.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov/group.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace detail_persistent_invocable_object_with_persistent_provision {

template< class Invocable, class... Providers >
struct requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < PersistentInvocableObjectWithKinds
        < Invocable
        , prov_traits::argument_list_kinds_of_persistent_t
          < prov::result_of_group_t< Providers&&... > >
        >
      >;
};

} // namespace argot(::detail_persistent_invocable_object_with_persistent_provision)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_invocable_object_with_persistent_provision.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... Providers >
ARGOT_AUTO_CONCEPT( PersistentInvocableObjectWithPersistentProvision )
(
  InvocableObjectWithProvision< Invocable, Providers... >
, TransparentRequirement
  < detail_persistent_invocable_object_with_persistent_provision::requirements
    < Invocable, Providers... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_INVOCABLE_OBJECT_WITH_PERSISTENT_PROVISION_HPP_
