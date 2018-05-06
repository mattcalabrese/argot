/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_SWITCH_BODY_FOR_TYPE_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_SWITCH_BODY_FOR_TYPE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/conditional.hpp>
#include <argot/switch_traits/case_values.hpp>
#include <argot/value_list.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace persistent_switch_body_for_type_detail {

template< class ValueType, class Body, class Values >
struct switch_body_for_type_case_requirements_impl;

template< class ValueType, class Body, auto... Values >
struct switch_body_for_type_case_requirements_impl
< ValueType, Body, value_list_t< Values... > >
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < PersistentSwitchBodyCase
        < Body, static_cast< ValueType >( Values ) >...
      >;
};

template< class Body, class ValueType >
struct switch_body_for_type_case_requirements
  : switch_body_for_type_case_requirements_impl
    < ValueType, Body, switch_traits::case_values_t< Body > > {};

struct switch_body_for_type_no_default
{
  template< template< class... > class Reqs >
  using expand_requirements = Reqs<>;
};

template< class Body, class ValueType >
struct switch_body_for_type_default_requirements_impl
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs< PersistentSwitchBodyDefaultForType< Body, ValueType > >;
};

template< class Body, class ValueType >
struct switch_body_for_type_default_requirements
  : argot_detail::conditional< is_modeled_v< SwitchBodyDefault< Body > > >
    ::template apply
    < switch_body_for_type_default_requirements_impl< Body, ValueType >
    , switch_body_for_type_no_default
    > {};

}  // namespace argot(::persistent_switch_body_for_type_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_switch_body_for_type.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Body, class ValueType >
ARGOT_AUTO_CONCEPT( PersistentSwitchBodyForType )
(
  SwitchBodyForType< Body, ValueType >
, TransparentRequirement
  < persistent_switch_body_for_type_detail
    ::switch_body_for_type_case_requirements< Body, ValueType >
  >
, TransparentRequirement
  < persistent_switch_body_for_type_detail
    ::switch_body_for_type_default_requirements< Body, ValueType >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_SWITCH_BODY_FOR_TYPE_HPP_
