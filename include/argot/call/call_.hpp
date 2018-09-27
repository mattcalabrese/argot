/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CALL_CALL_TO_HPP_
#define ARGOT_CALL_CALL_TO_HPP_

#include <argot/concepts/argot_invocable_with_persistent_reduction.hpp>
#include <argot/concepts/return_type.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/to.hpp>

namespace argot {

template< class Ret >
struct call_to_fn
{
  ARGOT_CONCEPT_ASSERT( ReturnType< Ret > );

  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( ArgotInvocableWithPersistentReduction
      < reducer::to_t< Ret >, Fun&&, P&&... >
    )
    ()
  >
  constexpr auto operator()( Fun&& fun, P&&... args ) const
  {
    return prov_traits::destructive_provide
    ( prov::default_to_reference_to( ARGOT_FORWARD( P )( args )... )
    , receiver::reduced_invoke
      ( reducer::to< Ret >
      , argot_detail::invocable_to_basic_callable_by_reference
        ( ARGOT_FORWARD( Fun )( fun ) )
      )
    );
  }
};

template< class Ret >
ARGOT_REQUIRES( ReturnType< Ret > )
< call_to_fn< Ret > > constexpr call_{};

} // namespace argot

#endif  // ARGOT_CALL_CALL_TO_HPP_
