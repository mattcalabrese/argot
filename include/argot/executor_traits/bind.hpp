/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_EXECUTOR_TRAITS_BIND_HPP_
#define ARGOT_EXECUTOR_TRAITS_BIND_HPP_

//[description
/*`
executor_traits::bind is a facility for combining an Executor and an
InvocableObjectWith into a single function object that triggers execution of the
InvocableObjectWith via the Executor whenever the resultant function object is
called.

[note The resultant function object returns `void` when called. If you wish to
      retrieve a Future instead, use packager_traits::package.
]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor_traits/execute.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::executor_traits {

struct bind_fn
{
  //<-
  template< class Exec, class Fun >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Executor< Exec > );
    ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun > );

    constexpr decltype( auto ) operator()() &&
    {
      return executor_traits::execute( ARGOT_MOVE( exec ), ARGOT_MOVE( fun ) );
    }

    ARGOT_NO_UNIQUE_ADDRESS Exec exec;
    ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  };
  //->
  template< class Exec, class Fun
          , ARGOT_REQUIRES
            ( Executor< detail_argot::remove_cvref_t< Exec > > )
            ( InvocableObjectWith< std::decay_t< Fun > > )
            ( MoveConstructible< std::decay_t< Fun > > )
            ( Sinkable< Exec&& > )
            ( DecaySinkable< Fun&& > )
            ()
          >
  constexpr auto operator()( Exec&& exec, Fun&& fun ) const//=;
  //<-
  {
    return impl< detail_argot::remove_cvref_t< Exec >, std::decay_t< Fun > >
    { exec
    , call_detail::forward_and_decay_sink< Fun >( fun )
    };
  } //->
} inline constexpr bind{};

template< class Exec, class Fun >
using result_of_bind//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< bind_fn const&, Exec, Fun >; //->

template< class Exec, class Fun >
using result_of_bind_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< bind_fn const&, Exec, Fun >; //->

} // namespace (argot::executor_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Exec&& exec`]
  [A Sinkable reference to a possibly-qualified Executor]
  [The Executor via which `fun` is to be run]
 ]
 [[`Fun&& fun`]
  [A DecaySinkable reference to a nullary InvocableWith]
  [The InvocableWith to be run]
 ]
]
*/

//]

#endif  // ARGOT_EXECUTOR_TRAITS_BIND_HPP_
