/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_PROVIDER_GENERATOR_WITH_PROVISION_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_PROVIDER_GENERATOR_WITH_PROVISION_HPP_

#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/argument_provider_generator_with_kinds.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/permute.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace detail_argument_provider_generator_with_provision {

// TODO(mattcalabrese) Inline in the auto concept once properly lazy.
template< class Invocable, class... Providers >
struct invocations_return_an_argument_provider
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< ArgumentProviderGeneratorWithKinds
           < Invocable
           , call_detail::permute_t
             < prov_traits::argument_list_kinds_of_destructive_t
               < Providers >...
             >
           >
         >;
};

} // namespace argot(::detail_argument_provider_generator_with_provision)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/argument_provider_generator_with_provision.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... Providers >
ARGOT_AUTO_CONCEPT( ArgumentProviderGeneratorWithProvision )
( ArgumentProvider< Providers >...
, TransparentRequirement
  < detail_argument_provider_generator_with_provision
    ::invocations_return_an_argument_provider< Invocable, Providers... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_ARGUMENT_PROVIDER_GENERATOR_WITH_PROVISION_HPP_
