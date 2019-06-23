/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_SINKABLE_HPP_
#define ARGOT_CONCEPTS_SINKABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/sinkable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Possibly require reference type
// TODO(mattcalabrese) Possibly require destructibility
// TODO(mattcalabrese) Possibly handle volatile
template< class T >
ARGOT_EXPLICIT_CONCEPT( Sinkable )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< Sinkable< T >
, call_detail::fast_enable_if_t< call_detail::is_sinkable_v< T > >
>
{
  static constexpr decltype( auto ) sink( T&& source ) noexcept
  {
    return call_detail::sink_impl< detail_argot::remove_cvref_t< T > >
    ::run( ARGOT_FORWARD( T )( source ) );
  }
};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_SINKABLE_HPP_
