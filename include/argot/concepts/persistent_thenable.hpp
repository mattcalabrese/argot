/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_THENABLE_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_THENABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/persistent_forgetful_thenable.hpp>
#include <argot/concepts/intrinsic_persistent_thenable.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/requires.hpp>
#include <argot/gen/not.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/sink.hpp>
#include <argot/fut_traits/config.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/packager_traits/package.hpp>
#include <argot/move.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_thenable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Fut, class FutPackager, class Exec >
ARGOT_EXPLICIT_CONCEPT( PersistentThenable )
(
  PersistentFuture< Fut >
, Thenable< Fut, FutPackager, Exec >
);

template< class Fut, class FutPackager, class Exec >
struct make_concept_map
< PersistentThenable< Fut, FutPackager, Exec >
, ARGOT_REQUIRES
  ( Thenable< Fut, FutPackager, Exec > )
  ( PersistentForgetfulThenable< Fut, Exec > )
  ( Not< IntrinsicPersistentThenable< Fut, FutPackager, Exec > > )
  <>
>
{
  // TODO(mattcalabrese) Create via the packager.
  template< class ExecP, class Fun >
  static constexpr auto
  then( Fut const& self, ExecP&& exec, Fun&& fun )
  {
    auto [ task, fut ]
      = packager_traits::package
        < FutPackager, fut_traits::value_type_t< Fut >&& > // TODO(mattcalabrese) Fix param type
        ( ARGOT_FORWARD( ExecP )( exec )
        , ARGOT_FORWARD( Fun )( fun )
        );

    // TODO(mattcalabrese) Use ForgetfulThenable concept
    access_raw_concept_map< PersistentForgetfulThenable< Fut, Exec > >
    ::forgetful_then
    ( self, ARGOT_FORWARD( ExecP )( exec ), ARGOT_MOVE( task ) );

    return ARGOT_MOVE( fut );
  }
};

template< class Fut, class FutPackager, class Exec >
struct make_concept_map
< PersistentThenable< Fut, FutPackager, Exec >
, ARGOT_REQUIRES
  ( IntrinsicPersistentThenable< Fut, FutPackager, Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class ExecP, class Fun >
  static constexpr auto
  then( Fut const& self, ExecP&& exec, Fun&& fun )
  {
    return access_raw_concept_map
    < IntrinsicPersistentThenable< Fut, FutPackager, Exec > >
    ::then( self
          , ARGOT_FORWARD( ExecP )( exec )
          , ARGOT_FORWARD( Fun )( fun )
          );
  }
};

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_THENABLE_HPP_
