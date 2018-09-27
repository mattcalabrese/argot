/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_DEFAULT_HPP_
#define ARGOT_CONCEPTS_DEFAULT_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/switch_traits/case_values.hpp>
#include <argot/value_list.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace default_concept_detail {

template< class Body >
struct no_case_values
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs< SameType< switch_traits::case_values_t< Body >, value_list_t<> > >;
};

} // namespace argot(::default_concept_detail)

// TODO(mattcalabrese) DefaultForType

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/default.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Body >
ARGOT_AUTO_CONCEPT( Default )
(
  SwitchBody< Body >
, TransparentRequirement< default_concept_detail::no_case_values< Body > >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_DEFAULT_HPP_
