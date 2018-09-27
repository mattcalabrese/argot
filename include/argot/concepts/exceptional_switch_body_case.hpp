/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EXCEPTIONAL_SWITCH_BODY_CASE_HPP_
#define ARGOT_CONCEPTS_EXCEPTIONAL_SWITCH_BODY_CASE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/switch_traits/argument_list_kinds_of_case_destructive.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace exceptional_cases_detail {

template< class T, auto Value >
struct exceptional_cases_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < SameType
        < switch_traits::argument_list_kinds_of_case_destructive_t< T, Value >
        , receiver_traits::argument_list_kinds_t<>
        >
      >;
};

} // namespace argot(::exceptional_cases_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/exceptional_switch_body_case.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T, auto Value >
ARGOT_AUTO_CONCEPT( ExceptionalSwitchBodyCase )
(
  SwitchBodyCase< T, Value >
, TransparentRequirement
  < exceptional_cases_detail::exceptional_cases_requirements< T, Value > >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_EXCEPTIONAL_SWITCH_BODY_CASE_HPP_
