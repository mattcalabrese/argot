/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_WITH_TRAILING_CONCURRENT_PROVIDER_HPP_
#define ARGOT_RECEIVER_WITH_TRAILING_CONCURRENT_PROVIDER_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/conc_traits/then_provide.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_provider_to.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/receiver/with_leading_values.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace receiver {

struct with_trailing_concurrent_provider_t
{
  template< class Receiver, class Provider >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentReceiver< Receiver > );
    ARGOT_CONCEPT_ASSERT( ConcurrentArgumentProvider< Provider > );

    ARGOT_NO_UNIQUE_ADDRESS Receiver receiver;
    ARGOT_NO_UNIQUE_ADDRESS Provider provider;
  };

  template< class Receiver, class Provider >
  constexpr
  ARGOT_REQUIRES( ArgumentReceiver< remove_cvref_t< Receiver > > )
                ( ConcurrentArgumentProvider< remove_cvref_t< Provider > > )
                ( Sinkable< Receiver&& > )
                ( Sinkable< Provider&& > )
  < impl< remove_cvref_t< Receiver >, remove_cvref_t< Provider > > >
  operator ()( Receiver&& receiver, Provider&& provider ) const
  {
    return
    { call_detail::forward_and_sink< Receiver >( receiver )
    , call_detail::forward_and_sink< Provider >( provider )
    };
  }
} inline constexpr with_trailing_concurrent_provider{};

template< class Receiver, class Provider >
using result_of_with_trailing_concurrent_provider_t
  = basic_result_of_t
    < with_trailing_concurrent_provider_t const&, Receiver, Provider >;

template< class Receiver, class Provider >
using result_of_with_trailing_concurrent_provider
  = basic_result_of
    < with_trailing_concurrent_provider_t const&, Receiver, Provider >;

}  // namespace argot::receiver

template< class Receiver, class Provider >
struct make_concept_map
< ArgumentReceiver
  < receiver::with_trailing_concurrent_provider_t::impl< Receiver, Provider > >
>
{
  template
  < class LeadingArgs, class TrailingArgs, class... P/*
  , ARGOT_REQUIRES
    ( ConcurrentArgumentProviderTo
      < Provider
      , receiver::result_of_with_leading_arguments_t
        < receiver::result_of_receiver_reference_t< Receiver&& >
        , LeadingArgs, TrailingArgs, P&&...
        >
      >
    )
    ()*/  // TODO(mattcalabrese) Constrain
  >
  static constexpr decltype( auto )
  receive_branch
  ( receiver::with_trailing_concurrent_provider_t::impl
    < Receiver, Provider >&& self
  , LeadingArgs, TrailingArgs, P&&... args
  )
  {
    // TODO(mattcalabrese) Squash?
    return conc_traits::then_provide
    ( ARGOT_MOVE( self.provider )
    , receiver::with_leading_values
      ( ARGOT_MOVE( self.receiver )
      , LeadingArgs{}, TrailingArgs{}, ARGOT_FORWARD( P )( args )...
      )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_RECEIVER_WITH_TRAILING_CONCURRENT_PROVIDER_HPP_
