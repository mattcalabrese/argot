/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_NOTHROW_DECAY_SINKABLE_HPP_
#define ARGOT_CONCEPTS_NOTHROW_DECAY_SINKABLE_HPP_

//[description
/*`
NothrowDecaySinkable is an [argot_gen_concept] that is statisfied by each type
`T` where the type `std::remove_cvref_t< T >` is implicitly constructible from a
`T` when only considering constructors that may be invoked with
an argument of type `std::remove_const_t< std::remove_reference_t< T > > &&` or
`std::remove_const_t< std::remove_reference_t< T > > const&`, and where the
expression is `noexcept`.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/nothrow_decay_sinkable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Possibly require reference type
// TODO(mattcalabrese) Possibly require destructibility
// TODO(mattcalabrese) Possibly handle volatile
template< class T >
ARGOT_EXPLICIT_CONCEPT( NothrowDecaySinkable )
(
  DecaySinkable< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< NothrowDecaySinkable< T >
, call_detail::fast_enable_if_t< call_detail::is_nothrow_decay_sinkable_v< T > >
>
{
  static constexpr decltype( auto ) sink( T&& source ) noexcept
  {
    return call_detail::decay_sink_impl< detail_argot::remove_cvref_t< T > >
    ::run( ARGOT_FORWARD( T )( source ) );
  }
};

} // namespace argot

#endif // ARGOT_CONCEPTS_NOTHROW_DECAY_SINKABLE_HPP_
