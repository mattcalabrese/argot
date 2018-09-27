/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_BASIC_TRANSFORMATION_WITH_HPP_
#define ARGOT_CONCEPTS_BASIC_TRANSFORMATION_WITH_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/parameter_type.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/requires.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

namespace transformation_with_detail {

template< class Invocable, class... P >
struct return_type_is_valid_parameter_type
{
  template< template< class... T > class Req >
  using expand_requirements
    = Req< ParameterType< std::invoke_result_t< Invocable&&, P&&... > > >;
};

} // namespace argot(::transformation_with_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/transformation_with.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... P >
ARGOT_AUTO_CONCEPT( TransformationWith )
(
  InvocableWith< Invocable, P... >
, TransparentRequirement
  < transformation_with_detail::return_type_is_valid_parameter_type
    < Invocable, P... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_BASIC_TRANSFORMATION_WITH_HPP_
