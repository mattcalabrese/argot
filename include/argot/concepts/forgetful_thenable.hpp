/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_FORGETFUL_THENABLE_HPP_
#define ARGOT_CONCEPTS_FORGETFUL_THENABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/true.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/concept_assert.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/fut_traits/config.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/forgetful_thenable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Fut, class Exec >
ARGOT_EXPLICIT_CONCEPT( ForgetfulThenable )
(
  Future< Fut >,
  Executor< Exec >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

// This preprocessor block includes concept maps for all detected future-likes.
#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/executor_traits/execute.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace detail_forgetful_thenable {

template< class Fun, class ValueType >
struct bound_function
{
  ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, ValueType&& > );

  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  ARGOT_NO_UNIQUE_ADDRESS ValueType arg;  // TODO(mattcalabrese) Use contained to account for references

  constexpr void operator ()() &&
  {
    (void)argot_detail::constexpr_invoke
    ( ARGOT_MOVE( fun ), ARGOT_FORWARD( ValueType )( arg ) );
  }
};

template< class Exec, class Fun, class ValueType >
struct continuation
{
  ARGOT_CONCEPT_ASSERT( Executor< Exec > );
  ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, ValueType&& > );
  ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, ValueType const& > );

  // TODO(mattcalabrese) Require argument syncability
  constexpr void operator ()( ValueType&& arg ) &&
  {
    (void)executor_traits::execute
    ( ARGOT_MOVE( exec )
    , bound_function< Fun, ValueType >{ ARGOT_MOVE( fun ), ARGOT_MOVE( arg ) }
    );
  }

  // TODO(mattcalabrese) Require argument syncability
  constexpr void operator ()( ValueType const& arg ) &&
  {
    (void)executor_traits::execute
    ( ARGOT_MOVE( exec )
    , bound_function< Fun, ValueType >{ ARGOT_MOVE( fun ), arg }
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS Exec exec;
  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
};

template< class Exec, class Fun, class ValueType >
struct continuation< Exec, Fun, ValueType& >
{
  ARGOT_CONCEPT_ASSERT( Executor< Exec > );
  ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, ValueType& > );

  constexpr void operator ()( ValueType& arg ) &&
  {
    (void)executor_traits::execute
    ( ARGOT_MOVE( exec )
    , bound_function< Fun, ValueType >{ ARGOT_MOVE( fun ), arg }
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS Exec exec;
  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
};

}  // namespace argot(::detail_forgetful_thenable)

template< class Fut, class Exec >
struct make_concept_map
< ForgetfulThenable< Fut, Exec >
, ARGOT_REQUIRES( Future< Fut > )
                ( Executor< Exec > )
                ( True< !std::is_same_v< Exec, executor::immediate_t > > )
                ( ForgetfulThenable< Fut, executor::immediate_t > )
                <>
>
{
  template< class ExecP, class Fun >
  constexpr void operator ()( Fut&& self, ExecP&& exec, Fun&& fun ) const
  {
    access_raw_concept_map
    < ForgetfulThenable< Fut, executor::immediate_t > >
    ::forgetful_then
    ( ARGOT_MOVE( self )
    , executor::immediate
    , detail_forgetful_thenable::continuation
      < remove_cvref_t< Exec >, remove_cvref_t< Fun >
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
#include <argot/concepts/forgetful_thenable/detail/boost_future.hpp>
#include <argot/concepts/forgetful_thenable/detail/boost_shared_future.hpp>
#endif

#ifdef ARGOT_HAS_STLAB_FUTURE
#include <argot/concepts/forgetful_thenable/detail/stlab_future.hpp>
#endif

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#endif  // ARGOT_CONCEPTS_FORGETFUL_THENABLE_HPP_
