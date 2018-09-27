/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_INVOCABLE_OBJECT_WITH_EACH_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_INVOCABLE_OBJECT_WITH_EACH_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/invocable_object_with_each.hpp>
#include <argot/concepts/invocable_with_each.hpp>
#include <argot/gen/auto_concept.hpp>

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_invocable_object_with_each.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Invocable, class... ArgumentListKinds >
ARGOT_AUTO_CONCEPT( PersistentInvocableObjectWithEach )
( InvocableObjectWithEach< Invocable, ArgumentListKinds... >
, InvocableWithEach< Invocable const&, ArgumentListKinds... >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_INVOCABLE_OBJECT_WITH_EACH_HPP_
