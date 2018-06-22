/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_CONCURRENT_ARGUMENT_PROVIDER_TO_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_CONCURRENT_ARGUMENT_PROVIDER_TO_HPP_

#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/conc_traits/argument_list_kinds_of_persistent.hpp>

#include <utility>

#endif

namespace argot {
namespace detail_persistent_concurrent_argument_provider_to {

template< class ConcProv, class Receiver >
struct argument_receiver_of
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < ArgumentReceiverOfKinds
        < Receiver
        , conc_traits::argument_list_kinds_of_persistent_t< ConcProv >
        >
      >;
};

}  // namespace argot(::detail_persistent_concurrent_argument_provider_to)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_concurrent_argument_provider_to.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class ConcProv, class Receiver >
ARGOT_AUTO_CONCEPT( PersistentConcurrentArgumentProviderTo )
( PersistentConcurrentArgumentProvider< ConcProv >
// TODO(mattcalabrese) First check that the provider can provide at all.
, TransparentRequirement
  < detail_persistent_concurrent_argument_provider_to
    ::argument_receiver_of< ConcProv, Receiver >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_CONCURRENT_ARGUMENT_PROVIDER_TO_HPP_
