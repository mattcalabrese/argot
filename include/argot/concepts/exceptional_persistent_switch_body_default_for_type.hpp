/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EXCEPTIONAL_PERSISTENT_SWITCH_BODY_DEFAULT_FOR_TYPE_HPP_
#define ARGOT_CONCEPTS_EXCEPTIONAL_PERSISTENT_SWITCH_BODY_DEFAULT_FOR_TYPE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/switch_traits/argument_list_kinds_of_default_persistent.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace exception_persistent_default_detail {

template< class T, class ValueType >
struct exception_persistent_default_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < SameType
        < switch_traits::argument_list_kinds_of_default_persistent_t
          < T, ValueType >
        , receiver_traits::argument_list_kinds_t<>
        >
      >;
};

} // namespace argot(::exception_persistent_default_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/exceptional_persistent_switch_body_default_for_type.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T, class ValueType >
ARGOT_AUTO_CONCEPT( ExceptionalPersistentSwitchBodyDefaultForType )
(
  PersistentSwitchBodyDefaultForType< T, ValueType >
, TransparentRequirement
  < exception_persistent_default_detail
    ::exception_persistent_default_requirements< T, ValueType >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif
// ARGOT_CONCEPTS_EXCEPTIONAL_PERSISTENT_SWITCH_BODY_DEFAULT_FOR_TYPE_HPP_
