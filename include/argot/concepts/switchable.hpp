/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_SWITCHABLE_HPP_
#define ARGOT_CONCEPTS_SWITCHABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/concepts/switch_condition_or_constant.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

namespace argot {
namespace switchable_detail {

template< class T >
struct value_type_impl
{
  using type = T;
};

template< class ValueType, ValueType Value >
struct value_type_impl< std::integral_constant< ValueType, Value > >
{
  using type = ValueType;
};

template< class ValueType, class... Bodies >
struct switchable_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs< SwitchBodyForType
            < Bodies, typename value_type_impl< ValueType >::type >...
          >;
};

}  // namespace argot(::switchable_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/switchable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Make sure the bodies can be combined
// TODO(mattcalabrese) Check for no duplicates
template< class ValueType, class... Bodies >
ARGOT_AUTO_CONCEPT( Switchable )
(
  SwitchConditionOrConstant< ValueType >
, TransparentRequirement
  < switchable_detail::switchable_requirements< ValueType, Bodies... > >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_SWITCHABLE_HPP_
