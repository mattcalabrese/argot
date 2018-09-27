/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_LIFTED_PERSISTENT_CALL_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_LIFTED_PERSISTENT_CALL_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/persistent_invocable_object_with_persistent_provision.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov/group.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/reducer_traits/return_types_of_call.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

namespace argument_receiver_of_lifted_persistent_call_detail {

template< class Receiver, class ReturnTypes >
struct argument_receiver_of_lifted_persistent_call_requirements_impl;

template< class Receiver, class... ReturnTypes >
struct argument_receiver_of_lifted_persistent_call_requirements_impl
< Receiver, reducer_traits::return_types_t< ReturnTypes... > >
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < ArgumentReceiverOf
        < Receiver, receiver_traits::argument_types_t< ReturnTypes&& >... >
      >;
};

template< class Receiver, class Invocable, class... Providers >
struct argument_receiver_of_lifted_persistent_call_requirements
  : argument_receiver_of_lifted_persistent_call_requirements_impl
    < Receiver
    , reducer_traits::return_types_of_call_t
      < Invocable const&, Providers const&... >  // TODO(mattcalabrese) Fix this, it needs to check provision as const, not that the providers were initially const and copied in
    > {};

} // namespace argot(::argument_receiver_of_lifted_persistent_call_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/argument_receiver_of_lifted_persistent_call.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Receiver, class Invocable, class... Providers >
ARGOT_AUTO_CONCEPT( ArgumentReceiverOfLiftedPersistentCall )
(
  ArgumentReceiver< Receiver >
, PersistentInvocableObjectWithPersistentProvision< Invocable, Providers... >
, TransparentRequirement
  < argument_receiver_of_lifted_persistent_call_detail
    ::argument_receiver_of_lifted_persistent_call_requirements
    < Receiver, Invocable, Providers... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_LIFTED_PERSISTENT_CALL_HPP_
