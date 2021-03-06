/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_COMPOSABLE_HPP_
#define ARGOT_CONCEPTS_COMPOSABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/sink.hpp>
#include <argot/void_.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace composable_concept_detail {

template< class P, class... Transformations >
struct composable_requirements;

template< class P >
struct composable_requirements< P >
{
  template< template< class... > class Reqs >
  using expand_requirements = Reqs<>;  // TODO(mattcalabrese) Constrain not void if no regular void support?
};

template< class P, class HeadTransformation, class... TailTransformations >
struct next_composable_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < TransparentRequirement
        < composable_requirements
          < argot_detail::result_of_constexpr_invoke_t
            < HeadTransformation&&, P >
          , TailTransformations...
          >
        >
      >;
};

template< class P, class HeadTransformation, class... TailTransformations >
struct composable_requirements< P, HeadTransformation, TailTransformations... >
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs< InvocableWith< HeadTransformation&&, void_to_regular_void_t< P > >
          , TransparentRequirement
            < next_composable_requirements
              < void_to_regular_void_t< P >
              , HeadTransformation, TailTransformations...
              >
            >
          >;
};

} // namespace argot(::composable_concept_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/composable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class P, class... Transformations >
ARGOT_AUTO_CONCEPT( Composable )
(
  PotentiallyInvocableObject< Transformations >...
, TransparentRequirement
  < composable_concept_detail::composable_requirements
    < P, Transformations... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_COMPOSABLE_HPP_
