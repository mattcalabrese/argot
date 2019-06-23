/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SPAWNER_PACKAGER_BASE_HPP_
#define ARGOT_SPAWNER_PACKAGER_BASE_HPP_

#include <argot/concepts/executor.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/future_spawner.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::packager {

template< class Child >
struct packager_base
{
  template< class Exec
          , ARGOT_REQUIRES( Executor< detail_argot::remove_cvref_t< Exec > > )
                          ( FuturePackager< Child > )
                          ( Sinkable< Exec&& > )
                          ()
          >
  constexpr auto operator []( Exec&& exec ) const
  {
    return future_spawner< Child, detail_argot::remove_cvref_t< Exec > >
    { call_detail::forward_and_sink< Exec >( exec ) };
  }
};

} // namespace (argot::packager)

#endif  // ARGOT_SPAWNER_PACKAGER_TEMPLATE_HPP_
