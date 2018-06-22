/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_TRAITS_PERSISTENT_FORGETFUL_PROVIDE_HPP_
#define ARGOT_CONC_TRAITS_PERSISTENT_FORGETFUL_PROVIDE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/concurrent_argument_provider_to.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/persistent_forgetful_then_providable.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::conc_traits {

// TODO(mattcalabrese) Require sinkable executor
struct persistent_forgetful_then_provide_t
{
  template
  < class ConcProvider, class Exec, class Receiver
  , ARGOT_REQUIRES
    ( ConcurrentArgumentProviderTo< ConcProvider, Receiver > )
    ( Executor< remove_cvref_t< Exec > > )
    ( ForgetfulThenProvidable< ConcProvider, Exec > )
    ()
  >
  constexpr void
  operator ()( ConcProvider&& provider, Exec&& exec, Receiver&& rec ) const
  {
    return access_raw_concept_map
    < PersistentForgetfulThenProvidable
      < ConcProvider, remove_cvref_t< Exec > >
    >::forgetful_then_provide
    ( provider, ARGOT_FORWARD( Exec )( exec ), ARGOT_MOVE( rec ) );
  }
} inline constexpr persistent_forgetful_then_provide{};

template< class ConcProvider, class Exec, class Receiver >
using result_of_persistent_forgetful_then_provide
  = basic_result_of
    < persistent_forgetful_then_provide_t const&
    , ConcProvider, Exec, Receiver
    >;

template< class ConcProvider, class Exec, class Receiver >
using result_of_persistent_forgetful_then_provide_t
  = basic_result_of_t
    < persistent_forgetful_then_provide_t const&
    , ConcProvider, Exec, Receiver
    >;

}  // namespace (argot::conc_traits)

#endif  // ARGOT_CONC_TRAITS_PERSISTENT_FORGETFUL_PROVIDE_HPP_
