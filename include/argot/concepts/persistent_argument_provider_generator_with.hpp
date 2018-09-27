/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_GENERATOR_WITH_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_GENERATOR_WITH_HPP_

//[description
/*`
PersistentArgumentProviderGeneratorWith is an [argot_gen_concept] that is
satisfied if the specified PersistentInvocableObject returns an ArgumentProvider
when const-lvalue-invoked with the specified argument types.
*/
//]

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_provider_generator_with.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace persistent_argument_provider_generator_with_detail {

// TODO(mattcalabrese) Inline in the auto concept once properly lazy.
template< class Invocable, class... P >
struct invocation_returns_an_argument_provider
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < ArgumentProvider< std::invoke_result_t< Invocable const&, P&&... > > >;
};


} // namespace argot(::persistent_argument_provider_generator_with_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_argument_provider_generator_with.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... P >
ARGOT_AUTO_CONCEPT( PersistentArgumentProviderGeneratorWith )
( ArgumentProviderGeneratorWith< Invocable, P... >
, TransparentRequirement
  < persistent_argument_provider_generator_with_detail
    ::invocation_returns_an_argument_provider< Invocable, P... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_GENERATOR_WITH_HPP_
