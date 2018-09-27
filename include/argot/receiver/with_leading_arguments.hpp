/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_WITH_LEADING_ARGUMENTS_HPP_
#define ARGOT_RECEIVER_WITH_LEADING_ARGUMENTS_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/receiver/with_leading_arguments/detail/with_leading_arguments_invoker.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace receiver {

struct with_leading_arguments_t
{
  template
  < class Receiver
  , class LeadingKinds, class TrailingKinds, class... P
  >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentReceiver< Receiver > );
    ARGOT_CONCEPT_ASSERT( ArgumentListKinds< LeadingKinds > );
    ARGOT_CONCEPT_ASSERT( ArgumentListKinds< TrailingKinds > );
    ARGOT_CONCEPT_ASSERT( Reference< P >... );

    using invoker_type
      = decltype
        ( with_leading_arguments_detail::make_receive_branch_invoker
          ( LeadingKinds(), TrailingKinds(), ARGOT_DECLVAL( P )... )
        );

    ARGOT_NO_UNIQUE_ADDRESS Receiver receiver;
    ARGOT_NO_UNIQUE_ADDRESS invoker_type invoker;
  };

  // TODO(mattcalabrese) Constrain
  template
  < class Receiver
  , class LeadingKinds, class TrailingKinds, class... P
  >
  constexpr ARGOT_REQUIRES
  ( ArgumentReceiver< detail_argot::remove_cvref_t< Receiver > > )
  ( ArgumentListKinds< LeadingKinds > )
  ( ArgumentListKinds< TrailingKinds > )
  ( Sinkable< Receiver&& > )
  < impl
    < detail_argot::remove_cvref_t< Receiver >
    , LeadingKinds
    , TrailingKinds
    , P&&...
    >
  >
  operator ()
  ( Receiver&& receiver, LeadingKinds /*leading*/, TrailingKinds /*trailing*/
  , P&&... args
  ) const
  {
    return { ARGOT_FORWARD( Receiver )( receiver )
           , with_leading_arguments_detail::make_receive_branch_invoker
             ( LeadingKinds(), TrailingKinds()
             , ARGOT_FORWARD( P )( args )...
             )
           };
  }
} inline constexpr with_leading_arguments{};

template
< class Receiver
, class LeadingArgs, class TrailingArgs, class... P
>
using result_of_with_leading_arguments
  = basic_result_of
    < with_leading_arguments_t const&
    , Receiver, LeadingArgs, TrailingArgs, P...
    >;

template
< class Receiver
, class LeadingArgs, class TrailingArgs, class... P
>
using result_of_with_leading_arguments_t
  = basic_result_of_t
    < with_leading_arguments_t const&
    , Receiver, LeadingArgs, TrailingArgs, P...
    >;

} // namespace argot::receiver

// TODO(mattcalabrese) Fix this (uses old-style constraints and forwarding)
template
< class Receiver
, class OLeadingPossibilities, class OTrailingPossibilities
, class... OP
>
struct make_concept_map
< ArgumentReceiver
  < receiver::with_leading_arguments_t::impl
    < Receiver
    , OLeadingPossibilities, OTrailingPossibilities, OP...
    >
  >
>
{
  template
  < class LeadingPossibilities, class TrailingPossibilities, class... P
  , ARGOT_REQUIRES
    ( ArgumentListKinds< LeadingPossibilities > )
    ( ArgumentListKinds< TrailingPossibilities > )
    ( ArgumentReceiverOfKinds
      < Receiver
      , receiver::with_leading_arguments_detail::possibilities_t
        < OLeadingPossibilities, OTrailingPossibilities
        , receiver_traits::argument_types_t< OP&&... >
        , LeadingPossibilities, TrailingPossibilities
        , receiver_traits::argument_types_t< P&&... >
        >
      >
    )
    ()
  >
  static constexpr decltype( auto ) receive_branch
  ( receiver::with_leading_arguments_t::impl
    < Receiver, OLeadingPossibilities, OTrailingPossibilities, OP... >&& self
  , LeadingPossibilities, TrailingPossibilities, P&&... args
  )
  {
    return self.invoker
    ( std::true_type()
    , ARGOT_MOVE( self.receiver )
    , LeadingPossibilities(), TrailingPossibilities()
    , ARGOT_FORWARD( P )( args )...
    );
  }
};

} // namespace argot

#endif  // ARGOT_RECEIVER_WITH_INITIAL_ARGUMENTS_HPP_
