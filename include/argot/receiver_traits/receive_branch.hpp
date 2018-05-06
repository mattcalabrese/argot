/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_TRAITS_RECEIVE_BRANCH_HPP_
#define ARGOT_RECEIVER_TRAITS_RECEIVE_BRANCH_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/detail/detection.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/move.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace receiver_traits {

struct receive_branch_t
{
  template
  < class Receiver, class LeadingPossibilites, class TrailingPossibilites
  , class... P
  , ARGOT_REQUIRES
    ( ArgumentListKinds< LeadingPossibilites > )
    ( ArgumentListKinds< TrailingPossibilites > )
    ( ArgumentReceiverOfKinds
      < Receiver
      , concatenate_argument_list_kinds_t
        < LeadingPossibilites
        , argument_list_kinds_t< argument_types_t< P&&... > >
        , TrailingPossibilites
        >
      >
    )
    ()
  >
  constexpr decltype( auto ) operator ()
  ( Receiver&& r
  , LeadingPossibilites /*leading*/, TrailingPossibilites /*trailing*/
  , P&&... args
  ) const
  {
    return access_raw_concept_map
    < ArgumentReceiver< std::remove_reference_t< Receiver > > >::receive_branch
    ( ARGOT_MOVE( r )
    , LeadingPossibilites(), TrailingPossibilites()
    , ARGOT_FORWARD( P )( args )...
    );
  }
} inline constexpr receive_branch{};


// TODO(mattcalabrese) Define in terms of the unbound form.
// TODO(mattcalabrese) Properly constrain.
template< class Receiver, class L, class T, class... P >
using result_of_receive_branch_t
  = basic_result_of_t< receive_branch_t const&, Receiver&&, L&&, T&&, P&&... >;

template< class Receiver, class L, class T, class... P >
using result_of_receive_branch
  = basic_result_of< receive_branch_t const&, Receiver&&, L&&, T&&, P&&... >;

template< class Receiver, class P >
struct result_of_unbound_receive_branch_impl {};

template< class Receiver >
struct result_of_unbound_receive_branch_impl
< Receiver, argument_list_kinds_t<> >
{
  using type = impossible;
};

template< class Receiver, class... H, class... T >
struct result_of_unbound_receive_branch_impl
< Receiver
, argument_list_kinds_t< argument_types_t< H... >, T... >
> : result_of_receive_branch
    < Receiver&&
    , argument_list_kinds_t<>&&
    , argument_list_kinds_t< T... >&&
    , H&&...
    > {};

// TODO(mattcalabrese) Constrain
template< class Receiver, class P >
using result_of_unbound_receive_branch_t
  = typename result_of_unbound_receive_branch_impl< Receiver, P >::type;

template< class Receiver, class P >
using result_of_unbound_receive_branch
  = call_detail::lazy_expand< result_of_unbound_receive_branch_t, P >;

}  // namespace argot::receiver_traits
}  // namespace argot

#endif  // ARGOT_RECEIVER_TRAITS_RECEIVE_BRANCH_HPP_
