/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_NESTED_RECEIVER_HPP_
#define ARGOT_RECEIVER_NESTED_RECEIVER_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace receiver {

// TODO(mattcalabrese)
//   Optimize such that if leading and trailing are empty, act as identity.
// TODO(mattcalabrese)
//   Possibly remove the nested of nested optimization
//   (observable during assignment)
struct nested_receiver_t
{
 public:
  template< class Receiver, class LeadingArgLists, class TrailingArgLists >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentReceiver< Receiver > );
    ARGOT_CONCEPT_ASSERT( ArgumentListKinds< LeadingArgLists > );
    ARGOT_CONCEPT_ASSERT( ArgumentListKinds< TrailingArgLists > );

    Receiver receiver;
  };
 private:
  template
  < class Receiver
  , class LeadingArgLists, class TrailingArgLists
  >
  struct impl_maker_of_nonnested_receiver
  {
    using result_type
      = impl< Receiver, LeadingArgLists, TrailingArgLists >;

    template< class T >
    static constexpr result_type run( T&& arg )
    {
      return { call_detail::forward_and_sink< T >( arg ) };
    }
  };

  template< class Receiver >
  struct impl_maker_of_nonnested_receiver
  < Receiver
  , receiver_traits::argument_list_kinds_t<>
  , receiver_traits::argument_list_kinds_t<>
  >
  {
    using result_type = Receiver;

    template< class T >
    static constexpr result_type run( T&& arg )
    {
      return call_detail::forward_and_sink< T >( arg );
    }
  };

  template
  < class Receiver
  , class LeadingArgLists, class TrailingArgLists
  >
  struct impl_maker
    : impl_maker_of_nonnested_receiver
      < Receiver, LeadingArgLists, TrailingArgLists >{};

  template
  < class Receiver
  , class... OriginalLeadingArgLists, class... OriginalTrailingArgLists
  , class... LeadingArgLists, class... TrailingArgLists
  >
  struct impl_maker
  < impl
    < Receiver
    , receiver_traits::argument_list_kinds_t< OriginalLeadingArgLists... >
    , receiver_traits::argument_list_kinds_t< OriginalTrailingArgLists... >
    >
  , receiver_traits::argument_list_kinds_t< LeadingArgLists... >
  , receiver_traits::argument_list_kinds_t< TrailingArgLists... >
  >
  {
    using result_type
      = impl
        < Receiver
        , receiver_traits::argument_list_kinds_t
          < OriginalLeadingArgLists..., LeadingArgLists... >
        , receiver_traits::argument_list_kinds_t
          < TrailingArgLists..., OriginalTrailingArgLists... >
        >;

    template< class T >
    static constexpr result_type run( T&& arg )
    {
      return{ call_detail::sink( ARGOT_FORWARD( T )( arg ).receiver ) };
    }
  };
 public:
  template< class Receiver, class LeadingArgLists, class TrailingArgLists
          , ARGOT_REQUIRES( ArgumentReceiver< detail_argot::remove_cvref_t< Receiver > > )
                          ( ArgumentListKinds< LeadingArgLists > )
                          ( ArgumentListKinds< TrailingArgLists > )
                          ( Sinkable< Receiver&& > )
                          ()
          >
  constexpr auto
  operator ()( Receiver&& rec, LeadingArgLists, TrailingArgLists ) const
  {
    return impl_maker
    < detail_argot::remove_cvref_t< Receiver >, LeadingArgLists , TrailingArgLists >
    ::run( ARGOT_FORWARD( Receiver )( rec ) );  // TODO(mattcalabrese) forward_and_sink
  }
} inline constexpr nested_receiver{};

template< class Receiver, class LeadingArgLists, class TrailingArgLists >
using result_of_nested_receiver_t
  = basic_result_of_t
    < nested_receiver_t const&, Receiver, LeadingArgLists, TrailingArgLists >;

template< class Receiver, class LeadingArgLists, class TrailingArgLists >
using result_of_nested_receiver
  = basic_result_of
    < nested_receiver_t const&, Receiver, LeadingArgLists, TrailingArgLists >;

}  // namespace argot::receiver

// TODO(mattcalabrese) Use a reference wrapper during recursion
template
< class Receiver
, class LeadingArgLists, class TrailingArgLists
>
struct make_concept_map
< ArgumentReceiver
  < receiver::nested_receiver_t::impl
    < Receiver, LeadingArgLists, TrailingArgLists >
  >
>
{
  // TODO(mattcalabrese) Make this not a template
  template
  < class LeadingPs, class TrailingPs, class... P
  , ARGOT_REQUIRES
    ( ArgumentListKinds< LeadingPs > )
    ( ArgumentListKinds< TrailingPs > )
    ( ArgumentReceiverOfKinds
      < Receiver
      , receiver_traits::concatenate_argument_list_kinds_t
        < LeadingArgLists, LeadingPs
        , receiver_traits::argument_list_kinds_t
          < receiver_traits::argument_types_t< P&&... > >
        , TrailingPs, TrailingArgLists
        >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  receive_branch
  ( receiver::nested_receiver_t::impl
    < Receiver, LeadingArgLists, TrailingArgLists >&& self
  , LeadingPs /*leading*/, TrailingPs /*trailing*/, P&&... args
  )
  {
    return receiver_traits::receive_branch
    ( ARGOT_MOVE( self.receiver )
    , receiver_traits::concatenate_argument_list_kinds_t
      < LeadingArgLists, LeadingPs >()
    , receiver_traits::concatenate_argument_list_kinds_t
      < TrailingPs, TrailingArgLists >()
    , ARGOT_FORWARD( P )( args )...
    );
  }
};

}  // namespace argot

#endif  // ARGOT_RECEIVER_NESTED_RECEIVER_HPP_
