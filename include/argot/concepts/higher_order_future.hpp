/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_HIGHER_ORDER_FUTURE_HPP_
#define ARGOT_CONCEPTS_HIGHER_ORDER_FUTURE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/future.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/fut_traits/value_type.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace higher_order_future_detail {

template< class Fut >
struct higher_order_future_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs< Future< fut_traits::value_type_t< Fut > > >;
};

} // namespace argot(::higher_order_future_detail)

// TODO(mattcalabrese) Implement this purely via the concepts

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/higher_order_future.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Fut >
ARGOT_AUTO_CONCEPT( HigherOrderFuture )
(
  Future< Fut >
, TransparentRequirement
  < higher_order_future_detail::higher_order_future_requirements< Fut > >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_HIGHER_ORDER_FUTURE_HPP_
