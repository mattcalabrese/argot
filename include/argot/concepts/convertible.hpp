/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_CONVERTIBLE_HPP_
#define ARGOT_CONCEPTS_CONVERTIBLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/explicitly_convertible.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/convertible.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Maybe make this more like n2914.
template< class T, class U >
ARGOT_EXPLICIT_CONCEPT( Convertible )
(
  ExplicitlyConvertible< T, U >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T, class U >
struct make_concept_map
< Convertible< T, U >
, typename call_detail::detached_fast_enable_if
  < is_modeled_v< ExplicitlyConvertible< T, U > > >
  ::_::template and_< std::is_convertible_v< T, U > >
  ::_::template apply<>
>
{
};

} // namespace argot

#endif  // ARGOT_CONCEPTS_CONVERTIBLE_HPP_
