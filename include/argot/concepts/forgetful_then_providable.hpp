/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_FORGETFUL_THEN_PROVIDABLE_HPP_
#define ARGOT_CONCEPTS_FORGETFUL_THEN_PROVIDABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/forgetful_thenable.hpp>
#include <argot/concepts/intrinsic_thenable.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/forgetful_thenable.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/requires.hpp>
#include <argot/gen/not.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/conc_traits/as_future.hpp>
#include <argot/detail/sink.hpp>
#include <argot/fut_traits/config.hpp>
#include <argot/fut_traits/forgetful_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/packager_traits/package.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/forgetful_then_providable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class ConcProv, class Exec >
ARGOT_EXPLICIT_CONCEPT( ForgetfulThenProvidable )
(
  ConcurrentArgumentProvider< ConcProv >
//, Thenable< conc_traits::result_of_as_future_t< >
);

// TODO(mattcalabrese) Fix constraints
template< class ConcProv, class Exec >
struct make_concept_map
< ForgetfulThenProvidable< ConcProv, Exec >
, ARGOT_REQUIRES
  ( ConcurrentArgumentProvider< ConcProv > )
  ( ForgetfulThenable  // TODO(mattcalabrese) Account for as_future returning a reference
    < conc_traits::result_of_as_future_t< ConcProv&& >, Exec >
  )
  <>
>
{
  template< class ExecP, class Fun >
  static constexpr void
  forgetful_then_provide( ConcProv&& self, ExecP&& exec, Fun&& fun )
  {
    fut_traits::forgetful_then
    ( conc_traits::as_future( ARGOT_MOVE( self ) )
    , ARGOT_FORWARD( ExecP )( exec )
    , ARGOT_FORWARD( Fun )( fun )  // TODO(mattcalabrese) Make fun from rec
    );
  }
};

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_FORGETFUL_THEN_PROVIDABLE_HPP_
