/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_GENERATOR_WITH_EACH_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_GENERATOR_WITH_EACH_HPP_

#include <argot/concepts/argument_types.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/persistent_argument_provider_generator_with.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_types.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace persistent_argument_provider_generator_with_each_detail {

// TODO(mattcalabrese) Inline in the auto concept once properly lazy.
template< class Invocable, class ArgTypes >
struct invocation_returns_an_argument_provider {};

template< class Invocable, class... P >
struct invocation_returns_an_argument_provider
< Invocable
, receiver_traits::argument_types_t< P... >
>
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< PersistentArgumentProviderGeneratorWith< Invocable, P... > >;
};

}  // namespace argot(::persistent_argument_provider_generator_with_each_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_argument_provider_generator_with_each.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... ArgTypes >
ARGOT_AUTO_CONCEPT( PersistentArgumentProviderGeneratorWithEach )
( ArgumentTypes< ArgTypes >...
, TransparentRequirement
  < persistent_argument_provider_generator_with_each_detail
    ::invocation_returns_an_argument_provider< Invocable, ArgTypes >
  >...
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_GENERATOR_WITH_EACH_HPP_
