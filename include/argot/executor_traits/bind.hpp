/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_EXECUTOR_TRAITS_BIND_HPP_
#define ARGOT_EXECUTOR_TRAITS_BIND_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor_traits/execute.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot::executor_traits {

// TODO(mattcalabrese) Bind values and references appropriately
struct bind_fn
{
  template< class Exec, class Fun >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Executor< Exec > );
    // ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun > );

    // TODO(mattcalabrese)
    template< class... P
            , ARGOT_REQUIRES( InvocableObjectWith< Fun, P&&... > )()
            >
    constexpr decltype( auto ) operator()( P&&... args ) &&
    {
      return executor_traits::execute( ARGOT_MOVE( exec ), ARGOT_MOVE( fun ) );
    }

    ARGOT_NO_UNIQUE_ADDRESS Exec exec;
    ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  };

  // TODO(mattcalabrese) Potentially invocable function
  template< class Exec, class Fun
          , ARGOT_REQUIRES( Executor< detail_argot::remove_cvref_t< Exec > > )
                          ( InvocableObjectWith< std::decay_t< Fun > > )
                          ( MoveConstructible< std::decay_t< Fun > > )
                          ( Sinkable< Exec&& > )
                          ( DecaySinkable< Fun&& > )
                          ()
          >
  constexpr auto operator()( Exec&& exec, Fun&& fun ) const
  {
    return impl< detail_argot::remove_cvref_t< Exec >, std::decay_t< Fun > >
    { exec
    , call_detail::forward_and_decay_sink< Fun >( fun )
    };
  }
} inline constexpr bind{};

template< class Exec, class Fun >
using result_of_bind = basic_result_of< bind_fn const&, Exec, Fun >;

template< class Exec, class Fun >
using result_of_bind_t = basic_result_of_t< bind_fn const&, Exec, Fun >;

}  // namespace (argot::executor_traits)

#endif  // ARGOT_EXECUTOR_TRAITS_BIND_HPP_
