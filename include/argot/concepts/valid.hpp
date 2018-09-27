/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_VALID_HPP_
#define ARGOT_CONCEPTS_VALID_HPP_

//[description
/*`
Valid is an [argot_gen_concept] that is satisfied when a given template and its
corresponding arguments would fail substitution if substitution were to take
place with the template and those parameters as dependent types.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <utility>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/valid.h

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

template< template< class... > class Template, class... P >
ARGOT_EXPLICIT_CONCEPT( Valid )
(
);

} // namespace argot
//]

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

namespace argot {

template< template< class... > class Template, class... P >
struct make_concept_map
< Valid< Template, P... >
, std::void_t< Template< P... > >
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_VALID_HPP_
