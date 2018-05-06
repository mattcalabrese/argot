/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_EXECUTOR_TRAITS_EXECUTE_HPP_
#define ARGOT_EXECUTOR_TRAITS_EXECUTE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot::executor_traits {

struct execute_fn
{
  template< class Exec, class Fun
          , ARGOT_REQUIRES( Executor< Exec > )
                          ( InvocableObjectWith< std::decay_t< Fun > > )
                          ( MoveConstructible< std::decay_t< Fun > > )
                          ( DecaySinkable< Fun&& > )
                          ()
          >
  constexpr void operator()( Exec const& exec, Fun&& fun ) const
  {
    (void)access_raw_concept_map< Executor< Exec > >::execute
    ( exec
    , argot_detail::invocable_to_basic_callable_by_value
      ( ARGOT_FORWARD( Fun )( fun ) )
    );
  }
} inline constexpr execute{};

template< class Exec, class Fun >
using result_of_execute = basic_result_of< execute_fn const&, Exec, Fun >;

template< class Exec, class Fun >
using result_of_execute_t = basic_result_of_t< execute_fn const&, Exec, Fun >;

}  // namespace (argot::executor_traits)

#endif  // ARGOT_EXECUTOR_TRAITS_EXECUTE_HPP_
