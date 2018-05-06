/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PACKAGER_PACKAGE_HPP_
#define ARGOT_PACKAGER_PACKAGE_HPP_

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>

namespace argot::packager_traits {

template< class FPackager, class... P >
struct package_fn
{
  // TODO(mattcalabrese) Assert valid argument types.
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );

  template< class Exec, class Fun
          , ARGOT_REQUIRES( Executor< remove_cvref_t< Exec > > )
                          ( InvocableWith< std::decay_t< Fun >, P... > )
                          ( Sinkable< Exec&& > )
                          ( DecaySinkable< Fun&& > )
                          ()
          >
  constexpr auto operator ()( Exec&& exec, Fun&& fun ) const
  {
    return access_raw_concept_map< FuturePackager< FPackager > >
    ::template package< P... >
    ( call_detail::forward_and_sink< Exec >( exec )
    , call_detail::forward_and_decay_sink< Fun >( fun )
    );
  }
};

// TODO(mattcalabrese) Require valid argument types.
template< class FPackager, class... P >
ARGOT_REQUIRES( FuturePackager< FPackager > )
< package_fn< FPackager, P... > > constexpr package{};

}  // namespace (argot::packager_traits)

#endif  // ARGOT_PACKAGER_PACKAGE_HPP_
