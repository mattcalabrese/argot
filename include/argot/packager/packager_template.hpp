/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PACKAGER_PACKAGER_TEMPLATE_HPP_
#define ARGOT_PACKAGER_PACKAGER_TEMPLATE_HPP_

#include <argot/future_spawner.hpp>

namespace argot::packager {

template< class Tag >
struct packager_template
{
  template< class Exec
          , ARGOT_REQUIRES
            ( Executor< detail_argot::remove_cvref_t< Exec > > )
            ( Sinkable< Exec&& > )
            ()
          >
  constexpr auto operator []( Exec&& exec ) const
    -> argot::future_spawner
       < packager_template, detail_argot::remove_cvref_t< Exec > >//=;
  //<-
  {
    return argot::future_spawner
    < packager_template, detail_argot::remove_cvref_t< Exec > >
    { call_detail::forward_and_sink< Exec >( exec ) };
  } //->
};

} // namespace (argot::packager)

#endif  // ARGOT_PACKAGER_PACKAGER_TEMPLATE_HPP_
