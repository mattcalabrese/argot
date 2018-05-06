/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PROVISIONAL_DEFAULT_FOR_TYPE_TO_HPP_
#define ARGOT_CONCEPTS_PROVISIONAL_DEFAULT_FOR_TYPE_TO_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/provisional_default_for_type.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/switch_traits/argument_list_kinds_of.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

namespace provisional_default_for_type_to_detail {

template< class Def, class ValueType, class Receiver >
struct provisional_default_for_type_to_requirements
{
  // TODO(mattcalabrese) Get the
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < ArgumentReceiverOfKinds
        < Receiver
        , switch_traits::argument_list_kinds_of_t< Def, ValueType >
        >
      >;
};

}  // namespace argot(::provisional_default_for_type_to_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/provisional_default_for_type_to.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Def, class ValueType, class Receiver >
ARGOT_AUTO_CONCEPT( ProvisionalDefaultForTypeTo )
(
  ProvisionalDefaultForType< Def, ValueType >
, TransparentRequirement
  < provisional_default_for_type_to_detail
    ::provisional_default_for_type_to_requirements< Def, ValueType, Receiver >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PROVISIONAL_DEFAULT_FOR_TYPE_TO_HPP_
