/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_RETURN_VALUE_REDUCER_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_RETURN_VALUE_REDUCER_HPP_

//[description
/*`
PersistentReturnValueReducer is the [argot_gen_concept] for
[return_value_reducers] that support a form of reduction that is non-destructive
and therefore may be performed multiple times.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/gen/explicit_concept.hpp>

namespace argot {
#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_return_value_reducer.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( PersistentReturnValueReducer )
( ReturnValueReducer< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_RETURN_VALUE_REDUCER_HPP_
