/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_RECEIVER_REFERENCE_HPP_
#define ARGOT_RECEIVER_RECEIVER_REFERENCE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/rvalue_reference.hpp>
#include <argot/contained.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/receive_branch.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace receiver {

// TODO(mattcalabrese)
//   Possibly collapse references to references. Make sure lvalue reference to
//   rvalue reference and rvalue reference to lvalue reference work correctly
//   with respect to reference-collapsing rules.
struct receiver_reference_t
{
 public:
  template< class ReceiverReference >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( RvalueReference< ReceiverReference > );
    ARGOT_CONCEPT_ASSERT
    ( ArgumentReceiver< std::remove_reference_t< ReceiverReference > > );

    contained< ReceiverReference > receiver;
  };
public:
  template< class Receiver >
  constexpr ARGOT_REQUIRES( ArgumentReceiver< Receiver > )
  < impl< Receiver&& > >
  operator ()( Receiver&& receiver ) const noexcept
  {
    return { argot::make_contained< Receiver&& >( ARGOT_MOVE( receiver ) ) };
  }
} inline constexpr receiver_reference{};

template< class Receiver >
using result_of_receiver_reference_t
  = basic_result_of_t< receiver_reference_t const&, Receiver&& >;

template< class Receiver >
using result_of_receiver_reference
  = basic_result_of< receiver_reference_t const&, Receiver&& >;

}  // namespace argot::receiver

// TODO(mattcalabrese) Use a reference wrapper during recursion
template< class ReceiverReference >
struct make_concept_map
< ArgumentReceiver
  < receiver::receiver_reference_t::impl< ReceiverReference > >
>
{
  // TODO(mattcalabrese) SFINAE
  template< class... LeadingPs, class... TrailingPs, class... P >
  static constexpr decltype( auto )
  receive_branch
  ( receiver::receiver_reference_t::impl< ReceiverReference >&& self
  , receiver_traits::argument_list_kinds_t< LeadingPs... >
  , receiver_traits::argument_list_kinds_t< TrailingPs... >
  , P&&... args
  )
  {
    return receiver_traits::receive_branch
    ( argot::access_contained( ARGOT_MOVE( self ).receiver )
    , receiver_traits::argument_list_kinds( LeadingPs()... )
    , receiver_traits::argument_list_kinds( TrailingPs()... )
    , ARGOT_FORWARD( P )( args )...
    );
  }
};

}  // namespace argot

#endif  // ARGOT_RECEIVER_RECEIVER_REFERENCE_HPP_
