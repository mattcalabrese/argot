/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGOT_INVOCABLE_HPP_
#define ARGOT_CONCEPTS_ARGOT_INVOCABLE_HPP_

#include <argot/concepts/argot_invocable_before_reduction.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#if !defined( ARGOT_GENERATE_PREPROCESSED_CONCEPTS )

#include <argot/detail/call_with.hpp>
#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#endif // !defined( ARGOT_GENERATE_PREPROCESSED_CONCEPTS )

namespace argot {
namespace detail_argot_invocable {

template< class Invocable, class Kinds >
struct all_return_types_are_the_same_requirement_impl;

template< class Invocable, class... ArgLists >
struct all_return_types_are_the_same_requirement_impl
< Invocable, receiver_traits::argument_list_kinds_t< ArgLists... > >
{
  template< template< class... > class Reqs >
  using expand_requirements
    = SameType< call_detail::result_of_call_with_t< Invocable, ArgLists >... >;
};

template< class Invocable, class... P >
struct all_return_types_are_the_same_requirement
  : all_return_types_are_the_same_requirement_impl
    < Invocable
    , prov_traits::argument_list_kinds_of_destructive_t
      < prov::result_of_default_to_reference_to_t< P... > >
    > {};

}  // namespace argot(::detail_argot_invocable)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME() s/argot_invocable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... P >
ARGOT_AUTO_CONCEPT( ArgotInvocable )
(
  ArgotInvocableBeforeReduction< Invocable, P... >
, TransparentRequirement
  < detail_argot_invocable::all_return_types_are_the_same_requirement
    < Invocable, P... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_ARGOT_INVOCABLE_HPP_
