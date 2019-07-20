/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FORGETFUL_ASYNC_CALL_HPP_
#define ARGOT_FORGETFUL_ASYNC_CALL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/conc/group.hpp>
#include <argot/conc_traits/as_future.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/fut_traits/forgetful_then.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/forgetful_invoke.hpp>

#include <type_traits>

namespace argot {

struct forgetful_async_call_t
{
 private:
  template< class Fun >
  struct continuation
  {
    // TODO(mattcalabrese) concept assert potentially invocable

    // TODO(mattcalabrese) conditional noexcept
    // TODO(mattcalabrese) take by forwarding reference
    template< class Provider >
    constexpr void operator ()( Provider provider ) &&
    {
      prov_traits::destructive_provide
      ( ARGOT_MOVE( provider )
      , receiver::forgetful_invoke( ARGOT_FORWARD( Fun )( fun ) )
      );
    }

    ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  };
 public:
  // TODO(mattcalabrese) Check callability
  template
  < class Exec, class Fun, class... P
  , ARGOT_REQUIRES
    ( Executor< detail_argot::remove_cvref_t< Exec > > )
    ( ConcurrentArgumentProvider< detail_argot::remove_cvref_t< P >... > )
    ( Sinkable< Exec&& > )
    ( DecaySinkable< Fun&& > )
    ( Sinkable< P&& >... )
    ()
  >
  constexpr void operator ()( Exec&& exec, Fun&& fun, P&&... args ) const
  {
    // TODO(mattcalabrese) Force the grouping to not defer execution.

    fut_traits::forgetful_then
    ( conc_traits::as_future( conc::group( ARGOT_FORWARD( P )( args )... ) )
    , call_detail::forward_and_sink< Exec >( exec )
    , continuation< std::decay_t< Fun > >
      { call_detail::forward_and_decay_sink< Fun >( fun ) }
    );
  }
} inline constexpr forgetful_async_call{};

template< class Exec, class Fun, class... P >
using result_of_forgetful_async_call_t
  = basic_result_of_t< forgetful_async_call_t const&, Exec, Fun, P... >;

template< class Exec, class Fun, class... P >
using result_of_forgetful_async_call
  = basic_result_of< forgetful_async_call_t const&, Exec, Fun, P... >;

} // namespace argot

#endif  // ARGOT_FORGETFUL_ASYNC_CALL_HPP_
