/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_TRAITS_BRANCH_TO_PROVISION_HPP_
#define ARGOT_RECEIVER_TRAITS_BRANCH_TO_PROVISION_HPP_

// TODO(mattcalabrese) Move this to prov_traits instead of receiver_traits

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/exceptional_argument_provider.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/gen/transparent_requirement.hpp>
#include <argot/prov_traits/argument_list_kinds_of.hpp>
#include <argot/receiver/nested_receiver.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/unreachable_function.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::receiver_traits {
namespace branch_to_provision_detail {

template< class Receiver, class L, class T, class ProviderArgumentLists >
struct argument_receiver_of;

template< class Receiver, class... L, class... T
        , class... ProviderArgumentLists
        >
struct argument_receiver_of
< Receiver, argument_list_kinds_t< L... >, argument_list_kinds_t< T... >
, argument_list_kinds_t< ProviderArgumentLists... >
>
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < ArgumentReceiverOf< Receiver, L..., ProviderArgumentLists..., T... > >;
};

} // namespace argot::receiver_traits(::branch_to_provision_detail)

// TODO(mattcalabrese) Make forms for destruct and persistent providers.
struct branch_to_provision_t
{
  template
  < class Receiver, class... L, class... T, class Provider
  , ARGOT_REQUIRES
    ( ArgumentReceiver< Receiver > )
    ( ArgumentProvider< detail_argot::remove_cvref_t< Provider > > )
    ( TransparentRequirement
      < branch_to_provision_detail::argument_receiver_of
        < Receiver
        , argument_list_kinds_t< L... >
        , argument_list_kinds_t< T... >
        , prov_traits::argument_list_kinds_of_t< Provider >
        >
      >
    )
    ()
  >
  constexpr decltype( auto )
  operator ()
  ( Receiver&& r
  , argument_list_kinds_t< L... > /*leading_possibilities*/
  , argument_list_kinds_t< T... > /*trailing_possibilities*/
  , Provider&& provider
  ) const
  {
    if constexpr( is_modeled_v< ExceptionalArgumentProvider< Provider > > )
    {
      prov_traits::provide
      ( static_cast< Provider&& >( provider )
      , receiver::nested_receiver
        ( receiver::receiver_reference( static_cast< Receiver&& >( r ) )
        , argument_list_kinds_t< L... >{}
        , argument_list_kinds_t< T... >{}
        )
      );

      return unreachable_function
      < result_of_unbound_receive_branch_t
        < Receiver&&
        , call_detail::concatenate_t
          < argument_list_kinds_t< L... >, argument_list_kinds_t< T... > >&&
        >
      >();
    }
    else
      return prov_traits::provide
      ( static_cast< Provider&& >( provider )
      , receiver::nested_receiver
        ( receiver::receiver_reference( static_cast< Receiver&& >( r ) )
        , argument_list_kinds_t< L... >{}
        , argument_list_kinds_t< T... >{}
        )
      );
  }
} inline constexpr branch_to_provision{};

template
< class Receiver
, class LeadingPossibilities, class TrailingPossibilities
, class Provider
>
using result_of_branch_to_provision
  = basic_result_of
    < branch_to_provision_t const&
    , Receiver&&
    , LeadingPossibilities&&, TrailingPossibilities&&
    , Provider&&
    >;

template
< class Receiver
, class LeadingPossibilities, class TrailingPossibilities
, class Provider
>
using result_of_branch_to_provision_t
  = basic_result_of_t
    < branch_to_provision_t const&
    , Receiver&&
    , LeadingPossibilities&&, TrailingPossibilities&&
    , Provider&&
    >;
} // namespace (argot::receiver_traits)

#endif  // ARGOT_RECEIVER_TRAITS_BRANCH_TO_PROVISION_HPP_
