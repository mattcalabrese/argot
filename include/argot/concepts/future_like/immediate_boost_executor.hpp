/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_FUTURE_LIKE_IMMEDIATE_BOOST_EXECUTOR_HPP_
#define ARGOT_CONCEPTS_FUTURE_LIKE_IMMEDIATE_BOOST_EXECUTOR_HPP_

#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/forward.hpp>
#include <argot/gen/requires.hpp>

#include <type_traits>

namespace argot::future_like_boost_future_detail {

struct immediate_boost_executor
{
  immediate_boost_executor() = default;

  immediate_boost_executor( const immediate_boost_executor& ) = delete;
  immediate_boost_executor& operator=
  ( const immediate_boost_executor& ) = delete;

  // TODO(mattcalabrese)
  //   Possibly require void return type on closure as boost specifies it.
  // TODO(mattcalabrese) Exception specification (possibly terminate on exception).
  template< class Closure
          , ARGOT_REQUIRES
            ( InvocableObjectWith< std::decay_t< Closure > > )
            ( CopyConstructible< std::decay_t< Closure > > )
            ( DecaySinkable< Closure&& > )
            ()
          >
  static constexpr void submit( Closure&& closure )
  {
    argot_detail::constexpr_invoke( ARGOT_FORWARD( Closure )( closure ) );
  }

  // TODO(mattcalabrese): Possibly do something other than unreachable.
  [[noreturn]] static void close() { ARGOT_DETAIL_UNREACHABLE(); }

  [[nodiscard]] static constexpr bool closed() { return false; }

  static constexpr bool try_executing_one() { return false; }

  template< class Pred
          , ARGOT_REQUIRES
            ( InvocableObjectWith< std::decay_t< Pred > > )
            ( CopyConstructible< std::decay_t< Pred > > )
            ( DecaySinkable< Pred&& > )
            ()
          >
  static constexpr bool reschedule_until( Pred&& predicate ) { return false; }
};

}  // namespace (argot::future_like_boost_future_detail)

#endif  // ARGOT_CONCEPTS_FUTURE_LIKE_IMMEDIATE_BOOST_EXECUTOR_HPP_
