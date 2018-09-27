/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_LIFT_TRANSFORM_HPP_
#define ARGOT_PROV_LIFT_TRANSFORM_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/compose.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/composable_with_persistent_provision.hpp>
#include <argot/concepts/composable_with_provision.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/invocable_reference.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver/forward_transformed_arguments.hpp>
#include <argot/receiver/receiver_reference.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace prov {

struct lift_transform_fn
{
 public:
  template< class Provider, class Transformation >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentProvider< Provider > );
    ARGOT_CONCEPT_ASSERT( ComposableWithProvision< Provider, Transformation > );

    ARGOT_NO_UNIQUE_ADDRESS Provider provider;
    ARGOT_NO_UNIQUE_ADDRESS Transformation transformation;
  };
 public:
  // TODO(mattcalabrese) constrain the transformations
  template
  < class Provider, class... Transformations
  , ARGOT_REQUIRES
    ( ComposableWithProvision
      < detail_argot::remove_cvref_t< Provider >
      , std::decay_t< Transformations >...
      >
    )
    ( Sinkable< Provider&& > )
    ( DecaySinkable< Transformations&& >... )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Provider&& provider
                            , Transformations&&... transformations
                            ) const
  {
    if constexpr( sizeof...( Transformations ) == 0 )
      return call_detail::forward_and_sink< Provider >( provider );
    else
      return impl
      < detail_argot::remove_cvref_t< Provider >
      , result_of_compose_t< Transformations&&... >
      >
      { call_detail::forward_and_sink< Provider >( provider )
      , compose
        ( call_detail::forward_and_decay_sink< Transformations >
          ( transformations )...
        )
      };
  }
} inline constexpr lift_transform{};

template< class Provider, class... Transformations >
using result_of_lift_transform//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of
    < lift_transform_fn const&, Provider&&, Transformations... >; //->

template< class Provider, class... Transformations >
using result_of_lift_transform_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t
    < lift_transform_fn const&, Provider&&, Transformations... >; //->

} // namespace argot(::prov)

template< class Provider, class Transformation >
struct make_concept_map
< ArgumentProvider< prov::lift_transform_fn::impl< Provider, Transformation > > >
{
  // TODO(mattcalabrese)
  //   Constrain to the ability for everything to be received
  template< class Receiver >
  static constexpr prov_traits::result_of_destructive_provide_t
  < Provider&&
  , receiver::result_of_forward_transformed_arguments_t
    < receiver::result_of_receiver_reference_t< Receiver&& >
    , result_of_invocable_reference_t< Transformation const& >
    >
  >
  provide( prov::lift_transform_fn::impl< Provider, Transformation >&& self
         , Receiver&& rec
         )
  {
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( self.provider )
    , receiver::forward_transformed_arguments
      ( receiver::receiver_reference( ARGOT_FORWARD( Receiver )( rec ) )
      , invocable_reference  // TODO(mattcalabrese) execute the last one via move
        ( static_cast< Transformation const& >( self.transformation ) )
      )
    );
  }
};

template< class Provider, class Transformation >
struct make_concept_map
< PersistentArgumentProvider
  < prov::lift_transform_fn::impl< Provider, Transformation > >
, ARGOT_REQUIRES
  ( ComposableWithPersistentProvision< Provider, Transformation > )
  <>
>
{
  // TODO(mattcalabrese)
  //   Constrain to the ability for everything to be received
  template< class Receiver >
  static constexpr prov_traits::result_of_persistent_provide_t
  < Provider const&
  , receiver::result_of_forward_transformed_arguments_t
    < receiver::result_of_receiver_reference_t< Receiver&& >
    , result_of_invocable_reference_t< Transformation const& >
    >
  >
  provide( prov::lift_transform_fn::impl< Provider, Transformation > const& self
         , Receiver&& rec
         )
  {
    return prov_traits::persistent_provide
    ( self.provider
    , receiver::forward_transformed_arguments
      ( receiver::receiver_reference( ARGOT_FORWARD( Receiver )( rec ) )
      , invocable_reference( self.transformation )
      )
    );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_LIFT_TRANSFORM_HPP_
