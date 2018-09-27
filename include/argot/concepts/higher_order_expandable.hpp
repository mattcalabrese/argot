/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_HIGHER_ORDER_EXPANDABLE_HPP_
#define ARGOT_CONCEPTS_HIGHER_ORDER_EXPANDABLE_HPP_

#include <argot/concepts/expandable.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>
#include <argot/concepts/higher_order_expandable/detail/is_higher_order_expandable.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace higher_order_expandable_detail {

template< class Exp >
struct all_provisions_are_expandable;

}

// TODO(mattcalabrese) Implement this purely via the concepts

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/higher_order_expandable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Exp >
ARGOT_EXPLICIT_CONCEPT( HigherOrderExpandable )
(
  Expandable< Exp >/*
, TransparentRequirement
  < higher_order_expandable_detail::all_provisions_are_expandable >*/
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

// TODO(mattcalabrese) Perform each Expandable check separately in SFINAE
template< class Exp >
struct make_concept_map
< HigherOrderExpandable< Exp >
, call_detail::fast_enable_if_t
  < higher_order_expandable_detail::is_higher_order_expandable_v< Exp > >
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_HIGHER_ORDER_EXPANDABLE_HPP_
