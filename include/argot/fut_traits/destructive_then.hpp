/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUTURE_TRAITS_DESTRUCTIVE_THEN_HPP_
#define ARGOT_FUTURE_TRAITS_DESTRUCTIVE_THEN_HPP_

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/thenable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/future_spawner.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/packager_traits/package.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot::fut_traits {

template< class FPackager >
struct destructive_then_fn
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );

  // TODO(mattcalabrese) Possibly change invocability constraint to include
  //                     arguments to continuations being const-qualified iff
  //                     the value_type is copyable.
  template< class Fut, class Exec, class Fun
          , ARGOT_REQUIRES
            ( Future< Fut > )
            ( Executor< detail_argot::remove_cvref_t< Exec > > )
            ( Thenable< Fut, FPackager, detail_argot::remove_cvref_t< Exec > > )
            ( InvocableWith< std::decay_t< Fun&& >, value_type_t< Fut >&& > )
            ( Sinkable< Exec&& > )
            ( DecaySinkable< Fun&& > )
            ()
          >
  constexpr auto operator ()( Fut&& self, Exec&& exec, Fun&& fun ) const
  {
    // TODO(mattcalabrese) Perform the decay sink as a cast to avoid moves.
    return access_raw_concept_map
    < Thenable< Fut, FPackager, detail_argot::remove_cvref_t< Exec > > >
    ::then( ARGOT_MOVE( self )
          , call_detail::forward_and_sink< Exec >( exec )
          , call_detail::forward_and_decay_sink< Fun >( fun )
          );
  }
};

template< class FPackager >
ARGOT_REQUIRES( FuturePackager< FPackager > )
< destructive_then_fn< FPackager > > constexpr destructive_then{};

} // namespace (argot::fut_traits)

#endif  // ARGOT_FUTURE_TRAITS_DESTRUCTIVE_THEN_HPP_
