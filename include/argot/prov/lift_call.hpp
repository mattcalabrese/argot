/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_LIFT_CALL_HPP_
#define ARGOT_PROV_LIFT_CALL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of_lifted_call.hpp>
#include <argot/concepts/argument_receiver_of_lifted_persistent_call.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/invocable_object_with_kinds.hpp>
#include <argot/concepts/liftable_call.hpp>
#include <argot/concepts/liftable_persistent_call.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/invocable_reference.hpp>
#include <argot/lazy_expand.hpp>
#include <argot/move.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver/forward_result_to.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace prov {

struct lift_call_fn
{
 public:
  // TODO(mattcalabrese) Group prior to passing.
  template< class Invocable, class... Providers >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentProvider< Providers >... );
    ARGOT_CONCEPT_ASSERT( InvocableObjectWithKinds
                          < Invocable
                          , prov_traits::argument_list_kinds_of_destructive_t
                            < result_of_group_t< Providers&&... > >
                          >
                        );

    using invocable_type = Invocable;
    using args_type = result_of_group_t< Providers... >;

    ARGOT_NO_UNIQUE_ADDRESS Invocable invocable;
    ARGOT_NO_UNIQUE_ADDRESS args_type args;
  };
 public:
  // TODO(mattcalabrese) Make sure result is a valid argument type.
  // TODO(mattcalabrese) remove_cvref for each provider.
  template
  < class Invocable, class... Providers
  , ARGOT_REQUIRES
    ( LiftableCall
      < std::decay_t< Invocable >, remove_cvref_t< Providers >... >
    )
    ( DecaySinkable< Invocable&& > )
    ( Sinkable< Providers&& >... )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Invocable&& invocable, Providers&&... args ) const
  {
    return impl< std::decay_t< Invocable >, remove_cvref_t< Providers >... >
    { call_detail::forward_and_decay_sink< Invocable >( invocable )
    , prov::group( call_detail::forward_and_sink< Providers >( args )... )
    };
  }
} inline constexpr lift_call{};

template< class Invocable, class... Providers >
using result_of_lift_call
  = basic_result_of< lift_call_fn const&, Invocable, Providers... >;

template< class Invocable, class... Providers >
using result_of_lift_call_t
  = basic_result_of_t< lift_call_fn const&, Invocable, Providers... >;

}  // namespace argot(::prov)

template< class Invocable, class... Providers >
struct make_concept_map
< ArgumentProvider< prov::lift_call_fn::impl< Invocable, Providers... > > >
{
  // TODO(mattcalabrese)
  //   Fix constraint (return_types_of_call provider grouping messes this up )
  //   Requires sinkability (maybe okay)
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfLiftedCall< Receiver, Invocable, Providers... > )()
  >
  static constexpr decltype( auto )
  provide( prov::lift_call_fn::impl< Invocable, Providers... >&& self
         , Receiver&& rec
         )
  {
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( self.args )
    , receiver::forward_result_to
      ( receiver::receiver_reference( ARGOT_MOVE( rec ) )
      , invocable_reference( ARGOT_MOVE( self.invocable ) )
      )
    );
  }
};

// TODO(mattcalabrese) Properly constrain
// TODO(mattcalabrese) Make sure result is a valid argument type
template< class Invocable, class... Providers >
struct make_concept_map
< PersistentArgumentProvider
  < prov::lift_call_fn::impl< Invocable, Providers... > >
, ARGOT_REQUIRES( LiftablePersistentCall< Invocable, Providers... > )<>
>
{
  // TODO(mattcalabrese)
  //   Fix constraint (return_types_of_call provider grouping messes this up )
  //   Incorrectly requires sinkability.
  template
  < class Receiver
  // TODO(mattcalabrese) Uncomment this when the concept definition is fixed.
  // , ARGOT_REQUIRES
  //   ( ArgumentReceiverOfLiftedPersistentCall
  //     < Receiver, Invocable, Providers... >
  //   )
  //   ()
  >
  static constexpr decltype( auto )
  provide( prov::lift_call_fn::impl< Invocable, Providers... > const& self
         , Receiver&& rec
         )
  {
    return prov_traits::persistent_provide
    ( self.args
    , receiver::forward_result_to
      ( receiver::receiver_reference( ARGOT_MOVE( rec ) )
      , invocable_reference( self.invocable )
      )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_LIFT_CALL_HPP_
