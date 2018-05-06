/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_READY_RESULT_HPP_
#define ARGOT_FUT_READY_RESULT_HPP_

namespace argot {
namespace fut {

struct ready_result_fn
{
  template< class Fun, class Provider >
  struct impl
  {
    // TODO(mattcalabrese) Concept assert

    ARGOT_NO_UNIQUE_ADDRESS Fun fun;
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
} inline constexpr ready_result{};

} // namespace argot(::fut)

template< class Fun, class Provider >
struct make_concept_map< Future< fut::ready_result_fn::impl< Fun, Provider > > >
{
  template< class Fun >
  static constexpr auto
  then( fut::ready_result_fn::impl< Fun, Provider >&& self, Fun&& fun )
  {
    using direct_result_type
      = decltype
        ( prov_traits::provide( ARGOT_MOVE( self.fun ), /*function caller*/ ) );

    return fut::ready< direct_result_type >
    ( prov_traits::provide( ARGOT_MOVE( self.fun ), /*function caller*/ )
    , /* TODO(mattcalabrese) Call constructor that is RVO friendly */
    );
  }
};

} // namespace argot

#endif  // ARGOT_FUT_READY_RESULT_HPP_
