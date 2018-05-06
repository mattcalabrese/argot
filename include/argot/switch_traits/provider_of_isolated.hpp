/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_PROVIDER_OF_CASE_HPP_
#define ARGOT_SWITCH_TRAITS_PROVIDER_OF_CASE_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/concepts/switch_body_default.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/concepts/switch_condition.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/switch_traits/argument_list_kinds_of_case_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/argument_list_kinds_of_default_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_default_persistent.hpp>
#include <argot/switch_traits/destructive_provide_isolated_case.hpp>
#include <argot/switch_traits/destructive_provide_isolated_default.hpp>
#include <argot/switch_traits/persistent_provide_isolated_case.hpp>
#include <argot/switch_traits/persistent_provide_isolated_default.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace switch_traits {
namespace provider_of_isolated_detail {

template< class Body, auto Value >
struct provider_of_isolated_case_t
{
  ARGOT_CONCEPT_ASSERT( SwitchBodyCase< Body, Value > );

  Body body;
};

template< class Body, auto Value >
struct provider_of_isolated_default_t
{
  ARGOT_CONCEPT_ASSERT( SwitchBodyDefaultForType< Body, decltype( Value ) > );

  Body body;
};

}  // namespace argot::switch_traits(::provider_of_isolated_detail)

// TODO(mattcalabrese) Make the concept contain this, but with a default.
template< auto Value >
struct provider_of_isolated_t
{
  ARGOT_CONCEPT_ASSERT( SwitchCondition< decltype( Value ) > );

  // TODO(mattcalabrese) Move the disjunction requirement into its own concept.
  template
  < class Body
  , ARGOT_REQUIRES
    ( SwitchBodyForType< remove_cvref_t< Body >, decltype( Value ) > )
    ( Or
      < SwitchBodyCase< remove_cvref_t< Body >, Value >
      , SwitchBodyDefault< remove_cvref_t< Body > >
      >
    )
    ( Sinkable< Body&& > )
    ()
  >
  constexpr auto operator ()( Body&& body ) const
  {
    using body_t = remove_cvref_t< Body >;

    if constexpr( is_modeled_v< SwitchBodyCase< body_t, Value > > )
      return provider_of_isolated_detail::provider_of_isolated_case_t
      < body_t, Value > { ARGOT_FORWARD( Body )( body ) };
    else
      return provider_of_isolated_detail::provider_of_isolated_default_t
      < body_t, Value > { ARGOT_FORWARD( Body )( body ) };
  }
};

template< auto Value >
ARGOT_REQUIRES( SwitchCondition< decltype( Value ) > )
< provider_of_isolated_t< Value > > constexpr provider_of_isolated{};

// TODO(mattcalabrese) Make result of calculators

}  // namespace argot(::switch_traits)

template< class Body, auto Value >
struct make_concept_map
< ArgumentProvider
  < switch_traits::provider_of_isolated_detail
    ::provider_of_isolated_case_t< Body, Value >
  >
>
{
  using argument_list_kinds_of_destructive_t
    = switch_traits::argument_list_kinds_of_case_destructive_t< Body, Value >;

  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_destructive_t
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( switch_traits::provider_of_isolated_detail
           ::provider_of_isolated_case_t< Body, Value >&& self
         , Receiver&& rec
         )
  {
    return switch_traits::destructive_provide_isolated_case< Value >
    ( ARGOT_MOVE( self.body ), ARGOT_FORWARD( Receiver )( rec ) );
  }
};

template< class Body, auto Value >
struct make_concept_map
< PersistentArgumentProvider
  < switch_traits::provider_of_isolated_detail
    ::provider_of_isolated_case_t< Body, Value >
  >
, ARGOT_REQUIRES( PersistentSwitchBodyCase< Body, Value > )<>
>
{
  using argument_list_kinds_of_persistent_t
    = switch_traits::argument_list_kinds_of_case_persistent_t< Body, Value >;

  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_persistent_t
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( switch_traits::provider_of_isolated_detail
           ::provider_of_isolated_case_t< Body, Value > const& self
         , Receiver&& rec
         )
  {
    return switch_traits::persistent_provide_isolated_case< Value >
    ( self.body, ARGOT_FORWARD( Receiver )( rec ) );
  }
};

template< class Body, auto Value >
struct make_concept_map
< ArgumentProvider
  < switch_traits::provider_of_isolated_detail
    ::provider_of_isolated_default_t< Body, Value >
  >
>
{
  using argument_list_kinds_of_destructive_t
    = switch_traits::argument_list_kinds_of_default_destructive_t
      < Body, decltype( Value ) >;

  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_destructive_t
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( switch_traits::provider_of_isolated_detail
           ::provider_of_isolated_default_t< Body, Value >&& self
         , Receiver&& rec
         )
  {
    return switch_traits::destructive_provide_isolated_default
    ( ARGOT_MOVE( self.body ), Value, ARGOT_FORWARD( Receiver )( rec ) );
  }
};

template< class Body, auto Value >
struct make_concept_map
< PersistentArgumentProvider
  < switch_traits::provider_of_isolated_detail
    ::provider_of_isolated_default_t< Body, Value >
  >
, ARGOT_REQUIRES
  ( PersistentSwitchBodyDefaultForType< Body, decltype( Value ) > )
  <>
>
{
  using argument_list_kinds_of_persistent_t
    = switch_traits::argument_list_kinds_of_default_persistent_t
      < Body, decltype( Value ) >;

  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_persistent_t
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( switch_traits::provider_of_isolated_detail
           ::provider_of_isolated_default_t< Body, Value > const& self
         , Receiver&& rec
         )
  {
    return switch_traits::persistent_provide_isolated_default
    ( self.body, Value, ARGOT_FORWARD( Receiver )( rec ) );
  }
};

}  // namespace argot

#endif  // ARGOT_SWITCH_TRAITS_PROVIDER_OF_CASE_HPP_
