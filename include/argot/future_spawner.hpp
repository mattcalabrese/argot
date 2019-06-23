/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUTURE_SPAWNER_HPP_
#define ARGOT_FUTURE_SPAWNER_HPP_

#include <argot/concepts/executor.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>

namespace argot {

template< class FPackager, class Exec >
struct future_spawner
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );
  ARGOT_CONCEPT_ASSERT( Executor< Exec > );

  using packager_t = FPackager;
  using executor_t = Exec;

  executor_t executor;
};

template< class FPackager >
struct future_spawner_fn
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );

  template< class Exec
          , ARGOT_REQUIRES( Executor< detail_argot::remove_cvref_t< Exec > > )
                          ( Sinkable< Exec&& > )
                          ()
          >
  constexpr auto operator()( Exec&& exec ) const
  {
    return future_spawner< FPackager, detail_argot::remove_cvref_t< Exec > >
    { call_detail::forward_and_sink< Exec >( exec ) };
  }
};

template< class FPackager >
ARGOT_REQUIRES( FuturePackager< FPackager > )
< future_spawner_fn< FPackager > > constexpr make_future_spawner{};

} // namespace argot

#endif  // ARGOT_FUTURE_SPAWNER_HPP_
