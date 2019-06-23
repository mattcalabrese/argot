/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_CAN_DEFAULT_TO_REFERENCE_TO_HPP_
#define ARGOT_CONCEPTS_CAN_DEFAULT_TO_REFERENCE_TO_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/gen/and.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/or.hpp>

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/can_default_to_reference_to.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class P >
ARGOT_AUTO_CONCEPT( CanDefaultToReferenceTo )
(
  // TODO(mattcalabrese) Possibly just make this a callability constraint
  //                     instead of having to use the logical operators.
  Or
  < And
    < ArgumentProvider< detail_argot::remove_cvref_t< P > >
    , Sinkable< P >
    >
  , Not< ArgumentProvider< detail_argot::remove_cvref_t< P > > >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_CAN_DEFAULT_TO_REFERENCE_TO_HPP_
