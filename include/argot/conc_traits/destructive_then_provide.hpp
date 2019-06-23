/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_TRAITS_DESTRUCTIVE_PROVIDE_HPP_
#define ARGOT_CONC_TRAITS_DESTRUCTIVE_PROVIDE_HPP_

#include <argot/basic_result_of.hpp>
//#include <argot/concepts/concurrent_argument_provider_to.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/then_providable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::conc_traits {

template< class FPackager >
struct destructive_then_provide_fn
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );

  // TODO(mattcalabrese) Require sinkable executor
  template
  < class ConcProvider, class Exec, class Receiver
  , ARGOT_REQUIRES
    //( ConcurrentArgumentProviderTo< ConcProvider, Receiver > ) // TODO(mattcalabrese) Constrain
    ( Executor< detail_argot::remove_cvref_t< Exec > > )
    ( ThenProvidable< ConcProvider, FPackager, Exec > )
    ()
  >
  constexpr decltype( auto )
  operator ()( ConcProvider&& provider, Exec&& exec, Receiver&& rec ) const
  {
    return access_raw_concept_map
    < ThenProvidable< ConcProvider, FPackager, detail_argot::remove_cvref_t< Exec > > >
    ::then_provide( ARGOT_MOVE( provider ), ARGOT_FORWARD( Exec )( exec )
                  , ARGOT_MOVE( rec )
                  );
  }
};

template< class FPackager >
ARGOT_REQUIRES( FuturePackager< FPackager > )
< destructive_then_provide_fn< FPackager > > constexpr
destructive_then_provide{};

template< class FPackager, class ConcProvider, class Exec, class Receiver >
using result_of_destructive_then_provide
  = basic_result_of
    < destructive_then_provide_fn< FPackager > const&
    , ConcProvider, Exec, Receiver
    >;

template< class FPackager, class ConcProvider, class Exec, class Receiver >
using result_of_destructive_then_provide_t
  = basic_result_of_t
    < destructive_then_provide_fn< FPackager > const&
    , ConcProvider, Exec, Receiver
    >;

}  // namespace (argot::conc_traits)

#endif  // ARGOT_CONC_TRAITS_DESTRUCTIVE_PROVIDE_HPP_
