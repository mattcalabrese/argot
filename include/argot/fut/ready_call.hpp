/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_READY_CALL_HPP_
#define ARGOT_FUT_READY_CALL_HPP_

namespace argot {
namespace fut {

// TODO(mattcalabrese) Overload operator[], similar to call.
struct ready_call_fn
{
  template< class Invocable, class Provider >
  struct impl
  {
    // TODO(mattcalabrese) Concept assert

    ARGOT_NO_UNIQUE_ADDRESS Invocable invocable;
    ARGOT_NO_UNIQUE_ADDRESS Provider provider;
  };

  template< class Invocable, class... Providers
          , ARGOT_REQUIRES
            ( LiftableCall
              < std::decay_t< Invocable >, remove_cvref_t< Providers >... >
            )
            ( DecaySinkable< Invocable&& > )
            ( Sinkable< Providers&& >... )
            ()
          >
  constexpr // TODO(mattcalabrese) SFINAE
  auto operator()( Invocable&&, Providers&&... providers ) const
  {

  }
} inline constexpr ready_call{};

} // namespace argot(::fut)

template< class Invocable, class Provider >
struct make_concept_map
< Future< fut::ready_call_fn::impl< Invocable, Provider > > >
{
  template< class Fun >
  static constexpr auto
  then( fut::ready_call_fn::impl< Invocable, Provider >&& self, Fun&& fun )
  {
    using direct_result_type
      = decltype
        ( prov_traits::provide( ARGOT_MOVE( self.fun ), /*function caller*/ ) );

    return fut::ready_call
    ( ARGOT_MOVE( self.fun )
    ,
    );
  }
};

} // namespace argot

#endif  // ARGOT_FUT_READY_CALL_HPP_
