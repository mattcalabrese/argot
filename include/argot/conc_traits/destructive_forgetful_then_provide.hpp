/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_TRAITS_DESTRUCTIVE_FORGETFUL_PROVIDE_HPP_
#define ARGOT_CONC_TRAITS_DESTRUCTIVE_FORGETFUL_PROVIDE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/concurrent_argument_provider_to.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/forgetful_then_providable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::conc_traits {

// TODO(mattcalabrese) Require sinkable executor
struct destructive_forgetful_then_provide_fn
{
  template
  < class ConcProvider, class Exec, class Receiver
  , ARGOT_REQUIRES
    ( ConcurrentArgumentProviderTo< ConcProvider, Receiver > )
    ( Executor< detail_argot::remove_cvref_t< Exec > > )
    ( ForgetfulThenProvidable< ConcProvider, Exec > )
    ()
  >
  constexpr void
  operator ()( ConcProvider&& provider, Exec&& exec, Receiver&& rec ) const
  {
    return access_raw_concept_map
    < ForgetfulThenProvidable< ConcProvider, detail_argot::remove_cvref_t< Exec > > >
    ::forgetful_then_provide
    ( ARGOT_MOVE( provider ), ARGOT_FORWARD( Exec )( exec )
    , ARGOT_MOVE( rec )
    );
  }
} inline constexpr destructive_forgetful_then_provide{};

template< class ConcProvider, class Exec, class Receiver >
using result_of_destructive_forgetful_then_provide
  = basic_result_of
    < destructive_forgetful_then_provide_fn const&
    , ConcProvider, Exec, Receiver
    >;

template< class ConcProvider, class Exec, class Receiver >
using result_of_destructive_forgetful_then_provide_t
  = basic_result_of_t
    < destructive_forgetful_then_provide_fn const&
    , ConcProvider, Exec, Receiver
    >;

}  // namespace (argot::conc_traits)

#endif  // ARGOT_CONC_TRAITS_DESTRUCTIVE_FORGETFUL_PROVIDE_HPP_
