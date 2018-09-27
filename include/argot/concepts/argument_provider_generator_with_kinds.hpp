/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_PROVIDER_GENERATOR_WITH_KINDS_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_PROVIDER_GENERATOR_WITH_KINDS_HPP_

#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/argument_provider_generator_with_each.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace argument_provider_generator_with_kinds_detail {

// TODO(mattcalabrese) Inline in the auto concept once properly lazy.
template< class Invocable, class Kinds >
struct invocations_return_an_argument_provider {};

template< class Invocable, class... Kinds >
struct invocations_return_an_argument_provider
< Invocable
, receiver_traits::argument_list_kinds_t< Kinds... >
>
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< ArgumentProviderGeneratorWithEach< Invocable, Kinds... > >;
};


} // namespace argot(::argument_provider_generator_with_kinds_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/argument_provider_generator_with_kinds.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class ArgListKinds >
ARGOT_AUTO_CONCEPT( ArgumentProviderGeneratorWithKinds )
( ArgumentListKinds< ArgListKinds >
, TransparentRequirement
  < argument_provider_generator_with_kinds_detail
    ::invocations_return_an_argument_provider< Invocable, ArgListKinds >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_ARGUMENT_PROVIDER_GENERATOR_WITH_KINDS_HPP_
