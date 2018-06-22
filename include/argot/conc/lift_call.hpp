/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_LIFT_CALL_HPP_
#define ARGOT_CONC_LIFT_CALL_HPP_

#include <argot/conc/bless_result.hpp>
#include <argot/conc/group.hpp>
#include <argot/conc_traits/as_future.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/liftable_call.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/fut/augment.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot::conc {

struct lift_call_fn
{
  // TODO(mattcalabrese) Constrain the invocable
  template< class Invocable, class... ConcProvs
          , ARGOT_REQUIRES
            ( ConcurrentArgumentProvider< remove_cvref_t< ConcProvs > >... )
            //( LiftableCall
            //  < std::decay_t< Invocable >
            //  , fut_traits::value_type_t
            //    < conc_traits::future_t< remove_cvref_t< ConcProvs > > >...
            //  >
            //)
            ( DecaySinkable< Invocable&& > )
            ( Sinkable< ConcProvs&& >... )
            ()
          >
  [[nodiscard]]
  constexpr auto operator()( Invocable&& invocable
                           , ConcProvs&&... conc_provs
                           ) const
  {
    return conc::bless_result
    ( fut::augment
    , conc_traits::as_future
      ( conc::group
        ( call_detail::forward_and_sink< ConcProvs >( conc_provs )... )
      )
    , conc::lift_call_fn::continuation< std::decay_t< Invocable > >
      { call_detail::forward_and_decay_sink< Invocable >( invocable ) }
    );
  }
 private:
  template< class Invocable >
  struct continuation
  {
    // TODO(mattcalabrese) Concept assert

    template< class Provider >
    constexpr auto operator ()( Provider&& provider ) &&
    {
      return prov::lift_call
      ( ARGOT_MOVE( invocable ), ARGOT_FORWARD( Provider )( provider ) );
    }

    ARGOT_NO_UNIQUE_ADDRESS Invocable invocable;
  };
} inline constexpr lift_call{};

} // namespace (argot::conc)

#endif  // ARGOT_CONC_LIFT_CALL_HPP_
