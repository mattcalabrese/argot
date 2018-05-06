/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_TO_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_TO_HPP_

#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>

#include <utility>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace persistent_argument_provider_to_detail {

template< class Provider, class Receiver >
struct argument_receiver_of
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < ArgumentReceiverOfKinds
        < Receiver
        , prov_traits::argument_list_kinds_of_persistent_t< Provider >
        >
      >;
};

}  // namespace argot(::persistent_argument_provider_to_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_argument_provider_to.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Provider, class Receiver >
ARGOT_AUTO_CONCEPT( PersistentArgumentProviderTo )
( PersistentArgumentProvider< Provider >
// TODO(mattcalabrese) First check that the provider can provide at all.
, TransparentRequirement
  < persistent_argument_provider_to_detail
    ::argument_receiver_of< Provider, Receiver >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_TO_HPP_
