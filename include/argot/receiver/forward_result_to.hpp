/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_FORWARD_RESULT_TO_HPP_
#define ARGOT_RECEIVER_FORWARD_RESULT_TO_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/invocable_with_each.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/group.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace receiver {

namespace forward_result_to_detail {

template< class Fun, class P >
struct result_types_as_argument_types_impl_impl;

template< class Fun, class... P >
struct result_types_as_argument_types_impl_impl
< Fun, receiver_traits::argument_types_t< P... > >
  : argot_detail::result_of_constexpr_invoke< Fun&&, P&&... >{};

// TODO(mattcalabrese) Remove && if supporting prvalues
template< class Fun, class P >
using result_types_as_argument_types_impl
  = receiver_traits::argument_types_t
    < typename result_types_as_argument_types_impl_impl< Fun, P >::type&& >;

template< class Fun, class... ArgumentListKinds >
using result_types_as_argument_types_t
  = receiver_traits::argument_list_kinds_t
    < result_types_as_argument_types_impl< Fun, ArgumentListKinds >... >;

template< class Fun, class... ArgumentListKinds >
result_types_as_argument_types_t< Fun, ArgumentListKinds... > constexpr
result_types_as_argument_types{};

} // namespace argot::receiver::forward_result_to_detail

struct forward_result_to_t
{
  template< class Receiver, class Invocable >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentReceiver< Receiver > );
    // TODO(mattcalabrese) Make sure Fun is possibly an invocable

    Receiver receiver;
    Invocable invocable;
  };

    // TODO(mattcalabrese) Constrain to Fun being possibly an invocable
    // TODO(mattcalabrese) decay_sink the invocable
  template< class Receiver, class Invocable >
  constexpr ARGOT_REQUIRES( ArgumentReceiver< Receiver > )
                          ( Sinkable< Receiver&& > )
                          ( Sinkable< Invocable&& > )
  < impl< detail_argot::remove_cvref_t< Receiver >, detail_argot::remove_cvref_t< Invocable > > >
  operator ()( Receiver&& receiver, Invocable&& invocable ) const
  {
    return { call_detail::forward_and_sink< Receiver >( receiver )
           , call_detail::forward_and_sink< Invocable >( invocable )
           };
  }
} inline constexpr forward_result_to{};

template< class Receiver, class Invocable >
using result_of_forward_result_to_t
  = basic_result_of_t< forward_result_to_t const&, Receiver&&, Invocable&& >;

template< class Receiver, class Invocable >
using result_of_forward_result_to
  = basic_result_of< forward_result_to_t const&, Receiver&&, Invocable&& >;

} // namespace argot::receiver

// TODO(mattcalabrese) Fix this (uses old-style constraints and forwarding)
template< class Receiver, class Invocable >
struct make_concept_map
< ArgumentReceiver
  < receiver::forward_result_to_t::impl< Receiver, Invocable > >
>
{
  template
  < class... LeadingArgumentListKinds
  , class... TrailingArgumentListKinds
  , class... P
  , ARGOT_REQUIRES
    ( InvocableWithEach< Invocable&&, LeadingArgumentListKinds... > )
    ( InvocableWith< Invocable&&, P&&... > )
    ( InvocableWithEach< Invocable&&, TrailingArgumentListKinds... > )
    ( ArgumentReceiverOf
      < Receiver
      , receiver::forward_result_to_detail::result_types_as_argument_types_impl
        < Invocable&&, LeadingArgumentListKinds >...
      , receiver_traits::argument_types_t
        < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... >&& > // TODO(mattcalabrese) Remove if supporting prvalues
      , receiver::forward_result_to_detail::result_types_as_argument_types_impl
        < Invocable&&, TrailingArgumentListKinds >...
      >
    )
    ()
  >
  static constexpr decltype( auto )
  receive_branch
  ( receiver::forward_result_to_t::impl< Receiver, Invocable >&& self
  , receiver_traits::argument_list_kinds_t< LeadingArgumentListKinds... >
  , receiver_traits::argument_list_kinds_t< TrailingArgumentListKinds... >
  , P&&... args
  )
  {
    // TODO(mattcalabrese) Handle void-to-regular-void constexpr_invoke
    return receiver_traits::receive_branch
    ( ARGOT_MOVE( self.receiver )
    , receiver::forward_result_to_detail::result_types_as_argument_types
      < Invocable&&, LeadingArgumentListKinds... >
    , receiver::forward_result_to_detail::result_types_as_argument_types
      < Invocable&&, TrailingArgumentListKinds... >
    , argot_detail::constexpr_invoke
      ( ARGOT_MOVE( self.invocable )
      , ARGOT_FORWARD( P )( args )...
      )
    );
  }
};

} // namespace argot

#endif  // ARGOT_RECEIVER_FORWARD_RESULT_TO_HPP_
