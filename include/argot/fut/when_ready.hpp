/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_WHEN_READY_HPP_
#define ARGOT_CONC_WHEN_READY_HPP_

#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/then.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>

namespace argot {
namespace conc {

struct when_ready_fn
{
  template< class Fut >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Future< Fut > );

    Fut future_like;
  };

  template< class Fut
          , ARGOT_REQUIRES( Future< Fut > )
                          ( Sinkable< Fut&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator()( Fut&& future_like ) const
  {
    return impl< remove_cvref_t< Fut > >{ ARGOT_FORWARD( Fut )( future_like ) };
  }
} inline constexpr when_ready{};

} // namespace argot(::conc)

template< class Fut >
struct make_concept_map
< ConcurrentArgumentProvider< when_ready_fn::impl< Fut > > >
{
  template< class Receiver >
  static constexpr decltype( auto )
  then_provide( when_ready_fn::impl< Fut >&& self, Receiver&& rec )
  {
    // TODO(mattcalabrese) Don't use a lambda here and make it rvalue ref qual
    return fut_traits::then
    ( ARGOT_MOVE( self.future_like )
    , [ rec = ARGOT_MOVE( rec ) ]( auto&& provider ) mutable
      {
        return receiver_traits::receive
        ( ARGOT_MOVE( rec )
        , ARGOT_FORWARD( decltype( provider ) )( provider )
        );
      }
    );
  }
};

} // namespace argot

#endif  // ARGOT_CONC_WHEN_READY_HPP_
