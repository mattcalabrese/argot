/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_PROVIDE_ARGUMENTS_TO_HPP_
#define ARGOT_RECEIVER_PROVIDE_ARGUMENTS_TO_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/provider_reference.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/nested_receiver.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/remove_cvref.hpp>

namespace argot {
namespace receiver {
namespace provide_arguments_to_detail {

template< class... ProviderArgumentListKinds >
struct squashed_argument_list_kinds;

template<>
struct squashed_argument_list_kinds<>
{
  using type = receiver_traits::argument_list_kinds_t<>;
};

// TODO(mattcalabrese) Make this SFINAE-aware (does it need to be?)
template< class... Providers, class... TailProviderArgumentListKinds >
struct squashed_argument_list_kinds
< receiver_traits::argument_types_t< Providers... >
, TailProviderArgumentListKinds...
>
{
  using type = call_detail::concatenate_t
  < prov_traits::result_of_provide_t
    < Providers&&, result_of_return_argument_list_kinds_t&& >...
  , typename squashed_argument_list_kinds
    < TailProviderArgumentListKinds... >::type
  >;
};

template< class... ProviderArgumentListKinds >
using squashed_argument_list_kinds_t
  = typename squashed_argument_list_kinds< ProviderArgumentListKinds... >::type;

}  // namespace argot::receiver(::provide_arguments_to_detail)

struct provide_arguments_to_t
{
  template< class Receiver >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentReceiver< Receiver > );

    ARGOT_NO_UNIQUE_ADDRESS Receiver receiver;
  };

  template< class Receiver
          , ARGOT_REQUIRES( ArgumentReceiver< remove_cvref_t< Receiver > > )
                          ( Sinkable< Receiver&& > )
                          ()
          >
  constexpr auto operator ()( Receiver&& receiver ) const
  {
    return impl< remove_cvref_t< Receiver > >
    { call_detail::forward_and_sink< Receiver >( receiver ) };
  }
} inline constexpr provide_arguments_to{};

template< class Receiver >
using result_of_provide_arguments_to_t
  = basic_result_of_t< provide_arguments_to_t const&, Receiver >;

template< class Receiver >
using result_of_provide_arguments_to
  = basic_result_of< provide_arguments_to_t const&, Receiver  >;

}  // namespace argot(::receiver)

template< class Receiver >
struct make_concept_map
< ArgumentReceiver< receiver::provide_arguments_to_t::impl< Receiver > > >
{
  // TODO(mattcalabrese)
  //   Properly expand out all of the Leading and Trailing args
  template< class... LeadingArgumentListKinds
          , class... TrailingArgumentListKinds
          , class... Providers
          >
  static constexpr prov_traits::result_of_provide_t
  < prov::result_of_group_t
    < prov::result_of_provider_reference_t< Providers >... >
  , receiver::result_of_nested_receiver_t
    < receiver::result_of_receiver_reference_t< Receiver&& >
    , receiver::provide_arguments_to_detail::squashed_argument_list_kinds_t
      < LeadingArgumentListKinds... >
    , receiver::provide_arguments_to_detail::squashed_argument_list_kinds_t
      < TrailingArgumentListKinds... >
    >
  >
  receive_branch
  ( receiver::provide_arguments_to_t::impl< Receiver >&& self
  , receiver_traits::argument_list_kinds_t< LeadingArgumentListKinds... >
  , receiver_traits::argument_list_kinds_t< TrailingArgumentListKinds... >
  , Providers&&... providers
  )
  {
    return prov_traits::provide  // TODO(mattcalabrese) Don't rely on group
    ( prov::group
      ( prov::provider_reference( ARGOT_FORWARD( Providers )( providers ) )... )
    , receiver::nested_receiver
      ( receiver::receiver_reference( ARGOT_MOVE( self.receiver ) )
      , receiver::provide_arguments_to_detail::squashed_argument_list_kinds_t
        < LeadingArgumentListKinds... >()
      , receiver::provide_arguments_to_detail::squashed_argument_list_kinds_t
        < TrailingArgumentListKinds... >()
      )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_RECEIVER_PROVIDE_ARGUMENTS_TO_HPP_
