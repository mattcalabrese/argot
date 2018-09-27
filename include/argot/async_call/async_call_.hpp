/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_ASYNC_CALL_ASYNC_CALL_TO_HPP_
#define ARGOT_ASYNC_CALL_ASYNC_CALL_TO_HPP_

#include <argot/async_call/detail/continuation_with_reducer.hpp>
#include <argot/conc/group.hpp>
#include <argot/conc_traits/as_future.hpp>
#include <argot/concepts/argot_invocable_with_persistent_reduction.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/return_type.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/fut_traits/then.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/to.hpp>

#include <type_traits>

namespace argot {

template< class FPackager, class Ret >
struct async_call_to_fn
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );
  ARGOT_CONCEPT_ASSERT( ReturnType< Ret > );

  // TODO(mattcalabrese) Make sure executor is valid with packager
  // TODO(mattcalabrese) Check conc::groupability
  // TODO(mattcalabrese) Properly check callability
  template
  < class Exec, class Fun, class... P
  , ARGOT_REQUIRES
    ( Executor< detail_argot::remove_cvref_t< Exec > > )
//    ( ArgotInvocableWithPersistentReduction
//      < reducer::to_t< Ret >, Fun&&, P&&... >
//    )
    ( Sinkable< Exec&& > )
    ( DecaySinkable< Fun&& > )
    ()
  >
  constexpr auto operator()( Exec&& exec, Fun&& fun, P&&... args ) const
  {
    return fut_traits::then< FPackager >
    ( conc_traits::as_future( conc::group( ARGOT_FORWARD( P )( args )... ) )
    , call_detail::forward_and_sink< Exec >( exec )
    , detail_async_call::continuation_with_reducer
      < FPackager, reducer::to_t< Ret >, std::decay_t< Fun > >
      { reducer::to< Ret >
      , call_detail::forward_and_decay_sink< Fun >( fun )
      }
    );
  }
};

template< class FPackager, class Ret >
ARGOT_REQUIRES( FuturePackager< FPackager > )
              ( ReturnType< Ret > )
< async_call_to_fn< FPackager, Ret > > constexpr async_call_{};

} // namespace argot


#endif  // ARGOT_ASYNC_CALL_ASYNC_CALL_TO_HPP_
