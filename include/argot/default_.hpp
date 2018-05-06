/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DEFAULT_HPP_
#define ARGOT_DEFAULT_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_provider_generator_with.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/persistent_argument_provider_generator_with.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_default.hpp>
#include <argot/concepts/switch_body_default_for_type.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/group.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/value_list.hpp>

#include <type_traits>

namespace argot {

template< class Provider >
struct bound_default
{
  ARGOT_CONCEPT_ASSERT( ArgumentProvider< Provider > );

  ARGOT_NO_UNIQUE_ADDRESS Provider provider;
};

struct default_t
{
  template< class... Providers
          , ARGOT_REQUIRES( ArgumentProvider< remove_cvref_t< Providers > >... )
                          ( Sinkable< Providers&& >... )
                          ()
          >
  [[nodiscard]] constexpr auto operator ()( Providers&&... providers ) const
  {
    return bound_default< prov::result_of_group_t< Providers&&... > >
    { prov::group
      ( call_detail::forward_and_sink< Providers&& >( providers )... )
    };
  }
 public:
  struct unreachable_impl {};

  template< class Fun >
  struct fail_impl
  {
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Fun > );

    ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  };

  template< class Generator >
  struct generate_impl
  {
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Generator > );

    ARGOT_NO_UNIQUE_ADDRESS Generator generator;
  };
 public:
  static constexpr unreachable_impl unreachable{};

  template< class Fun
          , ARGOT_REQUIRES
            ( PotentiallyInvocableObject< std::decay_t< Fun > > )
            ( DecaySinkable< Fun&& > )
            ()
          >
  [[nodiscard]] static constexpr auto fail( Fun&& fun )
  {
    return fail_impl< std::decay_t< Fun > >
    { call_detail::forward_and_decay_sink< Fun&& >( fun ) };
  }

  template< class Generator
          , ARGOT_REQUIRES
            ( PotentiallyInvocableObject< std::decay_t< Generator > > )
            ( DecaySinkable< Generator&& > )
            ()
          >
  [[nodiscard]]
  static constexpr auto generate_from_value( Generator&& generator )
  {
    return generate_impl< std::decay_t< Generator > >
    { call_detail::forward_and_decay_sink< Generator&& >( generator ) };
  }
} inline constexpr default_{};

template< class... Providers >
using result_of_default
  = basic_result_of< default_t const&, Providers... >;

template< class... Providers >
using result_of_default_t
  = basic_result_of_t< default_t const&, Providers... >;

using default_unreachable_t = default_t::unreachable_impl;

template<>
struct make_concept_map< SwitchBody< default_t::unreachable_impl > >
{
  using case_values_t = value_list_t<>;
};

template<>
struct make_concept_map
< SwitchBodyDefault< default_t::unreachable_impl > > {};

template< class ValueType >
struct make_concept_map
< SwitchBodyDefaultForType< default_t::unreachable_impl, ValueType >
, ARGOT_REQUIRES( SwitchCondition< ValueType > )<>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) constexpr?
  // TODO(mattcalabrese) Unqualify Receiver?
  template< class Receiver >
  static ARGOT_REQUIRES( ArgumentReceiver< remove_cvref_t< Receiver > > )
  < impossible > provide_isolated_default
  ( default_t::unreachable_impl, ValueType, Receiver&& rec )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template< class ValueType >
struct make_concept_map
< PersistentSwitchBodyDefaultForType
  < default_t::unreachable_impl, ValueType >
, ARGOT_REQUIRES( SwitchCondition< ValueType > )<>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) constexpr?
  // TODO(mattcalabrese) Unqualify Receiver?
  template< class Receiver >
  static ARGOT_REQUIRES( ArgumentReceiver< remove_cvref_t< Receiver > > )
  < impossible > provide_isolated_default
  ( default_t::unreachable_impl, ValueType, Receiver&& rec )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template< class Fun >
struct make_concept_map< SwitchBody< default_t::fail_impl< Fun > > >
{
  using case_values_t = value_list_t<>;
};

template< class Fun >
struct make_concept_map
< SwitchBodyDefault< default_t::fail_impl< Fun > > > {};

template< class Fun, class ValueType >
struct make_concept_map
< SwitchBodyDefaultForType< default_t::fail_impl< Fun >, ValueType >
, ARGOT_REQUIRES( SwitchCondition< ValueType > )
                ( InvocableWith< Fun&&, ValueType&& > )
                <>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver
          , ARGOT_REQUIRES( ArgumentReceiver< remove_cvref_t< Receiver > > )()
          >
  static impossible
  provide_isolated_default( default_t::fail_impl< Fun >&& self, ValueType value
                          , Receiver&& rec
                          )
  {
    argot_detail::constexpr_invoke
    ( ARGOT_MOVE( self.fun ), ARGOT_MOVE( value ) );

    ARGOT_DETAIL_UNREACHABLE();
  }
};

template< class Fun, class ValueType >
struct make_concept_map
< PersistentSwitchBodyDefaultForType
  < default_t::fail_impl< Fun >, ValueType >
, ARGOT_REQUIRES( SwitchCondition< ValueType > )
                ( InvocableWith< Fun const&, ValueType&& > )
                <>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver
          , ARGOT_REQUIRES( ArgumentReceiver< remove_cvref_t< Receiver > > )()
          >
  static impossible provide_isolated_default
  ( default_t::fail_impl< Fun > const& self, ValueType value, Receiver&& rec )
  {
    argot_detail::constexpr_invoke( self.fun, ARGOT_MOVE( value ) );

    ARGOT_DETAIL_UNREACHABLE();
  }
};

template< class Provider >
struct make_concept_map< SwitchBody< bound_default< Provider > > >
{
  using case_values_t = value_list_t<>;
};

template< class Provider >
struct make_concept_map< SwitchBodyDefault< bound_default< Provider > > >
{};

template< class Provider, class ValueType >
struct make_concept_map
< SwitchBodyDefaultForType< bound_default< Provider >, ValueType >
, ARGOT_REQUIRES( SwitchCondition< ValueType > )<>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver
          , ARGOT_REQUIRES
            ( ArgumentProviderTo< Provider, remove_cvref_t< Receiver > > )()
          >
  static constexpr decltype( auto ) provide_isolated_default
  ( bound_default< Provider >&& self, ValueType, Receiver&& rec )
  {
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( self.provider )
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

template< class Provider, class ValueType >
struct make_concept_map
< PersistentSwitchBodyDefaultForType< bound_default< Provider >, ValueType >
, ARGOT_REQUIRES( SwitchCondition< ValueType > )
                ( PersistentArgumentProvider< Provider > )
                <>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  template
  < class Receiver
  , ARGOT_REQUIRES
    ( PersistentArgumentProviderTo< Provider, remove_cvref_t< Receiver > > )()
  >
  static constexpr decltype( auto ) provide_isolated_default
  ( bound_default< Provider > const& self, ValueType, Receiver&& rec )
  {
    return prov_traits::persistent_provide
    ( self.provider
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

template< class Generator >
struct make_concept_map< SwitchBody< default_t::generate_impl< Generator > > >
{
  using case_values_t = value_list_t<>;
};

template< class Generator >
struct make_concept_map
< SwitchBodyDefault< default_t::generate_impl< Generator > > > {};

template< class Generator, class ValueType >
struct make_concept_map
< SwitchBodyDefaultForType
  < default_t::generate_impl< Generator >, ValueType >
, ARGOT_REQUIRES( SwitchCondition< ValueType > )
                ( ArgumentProviderGeneratorWith< Generator, ValueType&& > )
                <>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentProviderTo
      < argot_detail::result_of_constexpr_invoke_t< Generator&&, ValueType&& >
      , remove_cvref_t< Receiver >
      >
    )
    ()
  >
  static constexpr decltype( auto ) provide_isolated_default
  ( default_t::generate_impl< Generator >&& self, ValueType value
  , Receiver&& rec
  )
  {
    return prov_traits::destructive_provide
    ( argot_detail::constexpr_invoke
      ( ARGOT_MOVE( self.generator ), ARGOT_MOVE( value ) )
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

template< class Generator, class ValueType >
struct make_concept_map
< PersistentSwitchBodyDefaultForType
  < default_t::generate_impl< Generator >, ValueType >
, ARGOT_REQUIRES
  ( SwitchCondition< ValueType > )
  ( PersistentArgumentProviderGeneratorWith< Generator, ValueType&& > )
  <>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentProviderTo
      < argot_detail::result_of_constexpr_invoke_t
        < Generator const&, ValueType&& >
      , remove_cvref_t< Receiver >
      >
    )
    ()
  >
  static constexpr decltype( auto ) provide_isolated_default
  ( default_t::generate_impl< Generator > const& self, ValueType value
  , Receiver&& rec
  )
  {
    return prov_traits::destructive_provide
    ( argot_detail::constexpr_invoke( self.generator, ARGOT_MOVE( value ) )
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_DEFAULT_HPP_
