/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_LIFT_HPP_
#define ARGOT_CONC_LIFT_HPP_

//[description
/*`
conc::lift is a facility that takes an ArgumentProvider and returns a
corresponding ConcurrentArgumentProvider that provides what the original
ArgumentProvider provides. It captures the input ArgumentProvider by value.
*/
//]

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/fut/ready.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

struct lift_fn
{
  //<-
  template< class Provider >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentProvider< Provider > );

    using destructive_future_argument_provider_t
      = fut::result_of_ready_t< Provider >;

    ARGOT_NO_UNIQUE_ADDRESS destructive_future_argument_provider_t fut_prov;
  };
  //->
  template< class Provider
          , ARGOT_REQUIRES
            ( ArgumentProvider< detail_argot::remove_cvref_t< Provider > > )
            ( Sinkable< Provider&& > )
            ()
          >
  [[nodiscard]] constexpr auto operator()( Provider&& provider ) const//=;
  //<-
  {
    return impl< detail_argot::remove_cvref_t< Provider > >
    { fut::ready( call_detail::forward_and_sink< Provider >( provider ) ) };
  } //->
} inline constexpr lift{};

template< class Provider >
using result_of_lift//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< lift_fn const&, Provider >; //->

template< class Provider >
using result_of_lift_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< lift_fn const&, Provider >; //->

} // namespace (argot::conc)

//]

namespace argot {

template< class Provider >
struct make_concept_map
< ConcurrentArgumentProvider< conc::lift_fn::impl< Provider > > >
{
  using destructive_future_argument_provider_t
    = typename conc::lift_fn::impl< Provider >
      ::destructive_future_argument_provider_t;

  static constexpr destructive_future_argument_provider_t&&
  as_future( conc::lift_fn::impl< Provider >&& self )
  {
    return ARGOT_MOVE( self.fut_prov );
  }
};

// TODO(mattcalabrese) Uncomment and fix persistent_argument_provider

/*
template< class Provider >
struct make_concept_map
< PersistentConcurrentArgumentProvider< lift_fn::impl< Provider > > >
{
  // TODO(mattcalabrese) Use result of prov::as
  using persistent_argument_provider_t
    = typename prov::as_detail::as_impl< value_type_t< Provider > >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  then_provide( lift_fn::impl< Provider > const& self, Receiver&& rec )
  {
    // TODO(mattcalabrese) Don't use a lambda here and make it rvalue ref qual
    return fut_traits::then
    ( self.provider
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
*/
} // namespace argot

#endif  // ARGOT_CONC_LIFT_HPP_
