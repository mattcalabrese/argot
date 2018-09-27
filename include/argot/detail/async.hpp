/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_ASYNC_HPP_
#define ARGOT_DETAIL_ASYNC_HPP_

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor_traits/execute.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/value_of.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/same_type_or_fail.hpp>

namespace argot_detail {

// TODO(mattcalabrese) Make this destructive_async
struct async_fn
{
  // TODO(mattcalabrese) Allow persistent executors
  template< class Exec, class Fun, class... P
          , ARGOT_REQUIRES
            ( Executor< Exec > )
            ( InvocableWith< std::decay_t< Fun >&&, P&&... > )
            ( DecaySinkable< Fun&& > )
            ( Sinkable< P&& >... )
            ()
          >
  constexpr auto operator()( Exec&& exec, Fun&& fun, P&&... args ) const
  {
    // TODO(mattcalabrese) Don't use a lambda and use ARGOT_NO_UNIQUE_ADDRESS
    executor_traits::destructive_execute
    ( ARGOT_MOVE( exec )
    , [ fun = call_detail::forward_and_decay_sink< Fun >( fun )
      , provider = prov::value_of( ARGOT_FORWARD( args )... )
      ]() mutable
      {
        // TODO(mattcalabrese) Fix. Currently this doesn't return a future!
        prov_traits::destructive_provide
        ( ARGOT_MOVE( provider )
        , receiver::reduced_invoke
          ( reducer::same_type_or_fail
          , ARGOT_MOVE( fun )
          )
        )
      }
    );
  }

} inline constexpr async{};

} // namespace (argot_detail)

#endif  // ARGOT_DETAIL_ASYNC_HPP_
