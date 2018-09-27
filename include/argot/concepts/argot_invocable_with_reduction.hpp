/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGOT_INVOCABLE_WITH_REDUCTION_HPP_
#define ARGOT_CONCEPTS_ARGOT_INVOCABLE_WITH_REDUCTION_HPP_

#include <argot/concepts/argot_invocable_before_reduction.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/return_value_reducer_of.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

namespace argument_invocable_with_reduction_detail {

template< class Invocable, class Args >
struct return_type_of_call {};

template< class Invocable, class... Args >
struct return_type_of_call
< Invocable, receiver_traits::argument_types_t< Args... > >
{
  using type = std::invoke_result_t< Invocable&&, Args&&... >;
};

template< class Reducer, class Invocable, class Kinds >
struct argument_invocable_with_reduction_impl {};

template< class Reducer, class Invocable, class... Kinds >
struct argument_invocable_with_reduction_impl
< Reducer, Invocable, receiver_traits::argument_list_kinds_t< Kinds... > >
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < ReturnValueReducerOf
        < Reducer
        , typename return_type_of_call< Invocable, Kinds >::type...
        >
      >;
};

template< class Reducer, class Invocable, class... P >
struct argument_invocable_with_reduction
  : argument_invocable_with_reduction_impl
    < Reducer, Invocable
    , prov_traits::argument_list_kinds_of_destructive_t
      < prov::result_of_default_to_reference_to_t< P... > >
    > {};

} // namespace argot(::argument_invocable_with_reduction_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/argot_invocable_with_reduction.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Reducer, class Invocable, class... P >
ARGOT_AUTO_CONCEPT( ArgotInvocableWithReduction )
(
  ArgotInvocableBeforeReduction< Invocable, P... >
, TransparentRequirement
  < argument_invocable_with_reduction_detail
    ::argument_invocable_with_reduction< Reducer, Invocable, P... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_ARGOT_INVOCABLE_WITH_REDUCTION_HPP_
