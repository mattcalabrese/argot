/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_SWITCH_CONDITION_OR_CONSTANT_HPP_
#define ARGOT_CONCEPTS_SWITCH_CONDITION_OR_CONSTANT_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/switch_condition.hpp>
#include <argot/gen/and.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/transparent_requirement.hpp>

namespace argot {
namespace switch_condition_or_constant_detail {

template< class Type >
struct switch_condition_or_constant_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs< SwitchCondition< typename Type::value_type > >;
};

} // namespace argot(::switch_condition_or_constant_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/switch_condition_or_constant.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Type >
ARGOT_AUTO_CONCEPT( SwitchConditionOrConstant )
(
  Or< SwitchCondition< Type >
    , And< StdIntegralConstant< Type >
         , TransparentRequirement
           < switch_condition_or_constant_detail
             ::switch_condition_or_constant_requirements< Type >
           >
         >
    >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_SWITCH_CONDITION_OR_CONSTANT_HPP_
