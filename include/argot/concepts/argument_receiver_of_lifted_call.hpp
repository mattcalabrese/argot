/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_LIFTED_CALL_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_LIFTED_CALL_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/liftable_call.hpp>
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

namespace argument_receiver_of_lifted_call_detail {

template< class Receiver, class ReturnTypes >
struct argument_receiver_of_lifted_call_requirements_impl;

template< class Receiver, class... ReturnTypes >
struct argument_receiver_of_lifted_call_requirements_impl
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
struct argument_receiver_of_lifted_call_requirements
  : argument_receiver_of_lifted_call_requirements_impl
    < Receiver
    , reducer_traits::return_types_of_call_t< Invocable, Providers... >
    > {};

}  // namespace argot(::argument_receiver_of_lifted_call_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/argument_receiver_of_lifted_call.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Receiver, class Invocable, class... Providers >
ARGOT_AUTO_CONCEPT( ArgumentReceiverOfLiftedCall )
(
  ArgumentReceiver< Receiver >
, LiftableCall< Invocable, Providers... >
, TransparentRequirement
  < argument_receiver_of_lifted_call_detail
    ::argument_receiver_of_lifted_call_requirements
    < Receiver, Invocable, Providers... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_LIFTED_CALL_HPP_
