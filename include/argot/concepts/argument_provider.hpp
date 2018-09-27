/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_PROVIDER_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_PROVIDER_HPP_

//[description
/*`
ArgumentProvider is the [argot_gen_concept] for [argument_providers].
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/object.hpp>
#include <argot/gen/explicit_concept.hpp>

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/argument_provider.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

//[docs
/*`
[gen_concept_designator]
[synopsis_heading]
*/
namespace argot {

template< class T >
ARGOT_EXPLICIT_CONCEPT( ArgumentProvider )
( Object< T >
, MoveConstructible< T >
);

} // namespace argot
//]

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

#endif  // ARGOT_CONCEPTS_ARGUMENT_PROVIDER_HPP_
