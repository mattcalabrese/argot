/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/forgetful_thenable.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/concepts/true.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/concept_assert.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/fut_traits/config.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_forgetful_thenable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Fut, class Exec >
ARGOT_EXPLICIT_CONCEPT( PersistentForgetfulThenable )
(
  ForgetfulThenable< Fut, Exec >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

// This preprocessor block includes concept maps for all detected future-likes.
#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/forward.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/detail/move.hpp>

namespace argot {

template< class Fut, class Exec >
struct make_concept_map
< PersistentForgetfulThenable< Fut, Exec >
, ARGOT_REQUIRES( ForgetfulThenable< Fut, Exec > )
                ( True< !std::is_same_v< Exec, executor::immediate_t > > )
                ( PersistentForgetfulThenable< Fut, executor::immediate_t > )
                <>
>
{
  template< class ExecP, class Fun >
  constexpr void operator ()( Fut&& self, ExecP&& exec, Fun&& fun ) const
  {
    access_raw_concept_map
    < PersistentForgetfulThenable< Fut, executor::immediate_t > >
    ::forgetful_then
    ( self
    , executor::immediate
    , detail_forgetful_thenable::continuation
      < detail_argot::remove_cvref_t< Exec >, detail_argot::remove_cvref_t< Fun >
      , fut_traits::value_type_t< Fut >
      >
      { ARGOT_FORWARD( ExecP )( exec )
      , ARGOT_FORWARD( Fun )( fun )
      }
    );
  }
};

}  // namespace argot

#ifdef ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION
#include <argot/concepts/persistent_forgetful_thenable/detail/boost_shared_future.hpp>
#endif

#ifdef ARGOT_HAS_STLAB_FUTURE
#include <argot/concepts/persistent_forgetful_thenable/detail/stlab_future.hpp>
#endif

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#endif  // ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_HPP_
