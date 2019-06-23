/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_TRAITS_RECEIVE_HPP_
#define ARGOT_RECEIVER_TRAITS_RECEIVE_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/rvalue.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace receiver_traits {

// TODO(mattcalabrese) Calculate with result_of
template< class Receiver, class... P >
using result_of_receive_t
  = ARGOT_REQUIRES( Rvalue< Receiver > )
    < decltype
      ( access_raw_concept_map
        < ArgumentReceiver< std::remove_reference_t< Receiver > > >
        ::receive_branch
        ( ARGOT_DECLVAL( Receiver )
        , receiver_traits::argument_list_kinds()
        , receiver_traits::argument_list_kinds()
        , ARGOT_DECLVAL( P )...
        )
      )
    >;

template< class Receiver, class... P >
using result_of_receive
  = call_detail::lazy_expand< result_of_receive_t, Receiver, P... >;

struct receive_t
{
  template
  < class Receiver, class... P
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf< Receiver, argument_types_t< P&&... > > )()
  >
  constexpr decltype( auto ) operator ()( Receiver&& rec, P&&... args ) const
  {
    return access_raw_concept_map< ArgumentReceiver< Receiver > >
    ::receive_branch
    ( ARGOT_MOVE( rec )
    , receiver_traits::argument_list_kinds()
    , receiver_traits::argument_list_kinds()
    , ARGOT_FORWARD( P )( args )...
    );
  }
} inline constexpr receive{};

// TODO(mattcalabrese) Uncomment this
#if 0

template< class Receiver, class... P >
using result_of_receive_t
  = basic_result_of_t< receive_t const&, Receiver, P... >;

template< class Receiver, class... P >
using result_of_receive
  = basic_result_of< receive_t const&, Receiver, P... >;

#endif

}  // namespace argot::receiver_traits
}  // namespace argot

#endif  // ARGOT_RECEIVER_TRAITS_RECEIVE_HPP_
