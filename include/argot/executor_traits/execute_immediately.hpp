/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_EXECUTOR_TRAITS_EXECUTE_IMMEDIATELY_HPP_
#define ARGOT_EXECUTOR_TRAITS_EXECUTE_IMMEDIATELY_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/immediate_executor.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::executor_traits {

struct execute_immediately_fn
{
  // TODO(mattcalabrese) Optimize for rvalue overloads of execute.
  template< class Exec, class Fun
          , ARGOT_REQUIRES( ImmediateExecutor< Exec > )
                          ( InvocableObjectWith< std::decay_t< Fun > > )
                          ( MoveConstructible< std::decay_t< Fun > > )
                          ( DecaySinkable< Fun&& > )
                          ()
          >
  constexpr decltype( auto ) operator()( Exec const& exec, Fun&& fun ) const
  {
    return access_raw_concept_map< ImmediateExecutor< Exec > >::execute
    ( exec
    , argot_detail::invocable_to_basic_callable_by_value
      ( ARGOT_FORWARD( Fun )( fun ) )
    );
  }
} inline constexpr execute_immediately{};

template< class Exec, class Fun >
using result_of_execute_immediately
  = basic_result_of< execute_immediately_fn const&, Exec, Fun >;

template< class Exec, class Fun >
using result_of_execute_immediately_t
  = basic_result_of_t< execute_immediately_fn const&, Exec, Fun >;

}  // namespace (argot::executor_traits)

#endif  // ARGOT_EXECUTOR_TRAITS_EXECUTE_IMMEDIATELY_HPP_
