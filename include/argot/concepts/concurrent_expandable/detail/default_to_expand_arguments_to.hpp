/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONC_EXPANDABLE_DETAIL_DEFAULT_TO_EXPAND_ARGUMENTS_TO_HPP_
#define ARGOT_DETAIL_CONC_EXPANDABLE_DETAIL_DEFAULT_TO_EXPAND_ARGUMENTS_TO_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/expandable.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/provider_reference.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/nested_receiver.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace detail_expandable {

template< class... ProviderArgumentListKinds >
struct expanded_argument_list_kinds;

template<>
struct expanded_argument_list_kinds<>
{
  using type = receiver_traits::argument_list_kinds_t<>;
};

template< class P >
constexpr auto default_to_expand_arguments( P&& arg )
{
  using param_type_if_provider = call_detail::result_of_sinklike_cast_t< P&& >;
  using raw_type = detail_argot::remove_cvref_t< P&& >;

  using argument_provider_concept_instance
    = typename argot_detail::conditional
      < std::is_rvalue_reference_v< param_type_if_provider > >
      ::template meta_apply
      < ArgumentProvider, PersistentArgumentProvider, raw_type >;

  // TODO(mattcalabrese) sinklike_cast instead of forward for first branch.
  if constexpr( ARGOT_IS_MODELED( argument_provider_concept_instance ) )
    return prov::provider_reference( ARGOT_FORWARD( P )( arg ) );
  else
    return access_raw_concept_map< Expandable< P&& > >
    ::expand( ARGOT_FORWARD( P )( arg ) );
}

// TODO(mattcalabrese) Make this SFINAE-aware (does it need to be?)
template< class... Exps, class... TailProviderArgumentListKinds >
struct expanded_argument_list_kinds
< receiver_traits::argument_types_t< Exps... >
, TailProviderArgumentListKinds...
>
{
  using type = call_detail::concatenate_t
  < prov_traits::result_of_provide_t
    < decltype( ( default_to_expand_arguments )( ARGOT_DECLVAL( Exps&& ) ) )
    , receiver::result_of_return_argument_list_kinds_t&&
    >...
  , typename expanded_argument_list_kinds
    < TailProviderArgumentListKinds... >::type
  >;
};

template< class... ProviderArgumentListKinds >
using expanded_argument_list_kinds_t
  = typename expanded_argument_list_kinds< ProviderArgumentListKinds... >::type;

struct default_to_expand_arguments_to_t
{
  template< class Receiver >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentReceiver< Receiver > );

    ARGOT_NO_UNIQUE_ADDRESS Receiver receiver;
  };

  template< class Receiver
          , ARGOT_REQUIRES( ArgumentReceiver< detail_argot::remove_cvref_t< Receiver > > )
                          ( Sinkable< Receiver&& > )
                          ()
          >
  constexpr auto operator ()( Receiver&& receiver ) const
  {
    return impl< detail_argot::remove_cvref_t< Receiver > >
    { call_detail::forward_and_sink< Receiver >( receiver ) };
  }
} inline constexpr default_to_expand_arguments_to{};

template< class Receiver >
using result_of_default_to_expand_arguments_to_t
  = basic_result_of_t< default_to_expand_arguments_to_t const&, Receiver >;

template< class Receiver >
using result_of_default_to_expand_arguments_to
  = basic_result_of< default_to_expand_arguments_to_t const&, Receiver  >;

}  // namespace argot(::detail_expandable)

template< class Receiver >
struct make_concept_map
< ArgumentReceiver
  < detail_expandable::default_to_expand_arguments_to_t::impl< Receiver > >
>
{
  // TODO(mattcalabrese)
  //   Properly expand out all of the Leading and Trailing args
  //   Return decltype(auto)
  template< class... LeadingArgumentListKinds
          , class... TrailingArgumentListKinds
          , class... Exps
          >
  static constexpr /*prov_traits::result_of_provide_t
  < prov::result_of_group_t
    < decltype
      ( access_raw_concept_map< Expandable< Exps&& > >
        ::expand( ARGOT_DECLVAL( Exps ) )
      )...
    >
  , receiver::result_of_nested_receiver_t
    < receiver::result_of_receiver_reference_t< Receiver&& >
    , receiver::detail_expand_arguments_to::expanded_argument_list_kinds_t
      < LeadingArgumentListKinds... >
    , receiver::detail_expand_arguments_to::expanded_argument_list_kinds_t
      < TrailingArgumentListKinds... >
    >
  >*/
  decltype( auto )
  receive_branch
  ( detail_expandable::default_to_expand_arguments_to_t::impl< Receiver >&& self
  , receiver_traits::argument_list_kinds_t< LeadingArgumentListKinds... >
  , receiver_traits::argument_list_kinds_t< TrailingArgumentListKinds... >
  , Exps&&... exps
  )
  {
    return prov_traits::provide  // TODO(mattcalabrese) Don't rely on group
    ( prov::group
      ( detail_expandable::default_to_expand_arguments
        ( ARGOT_FORWARD( Exps )( exps ) )...
      )
    , receiver::nested_receiver
      ( receiver::receiver_reference( ARGOT_MOVE( self.receiver ) )
      , detail_expandable::expanded_argument_list_kinds_t
        < LeadingArgumentListKinds... >()
      , detail_expandable::expanded_argument_list_kinds_t
        < TrailingArgumentListKinds... >()
      )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_DETAIL_CONC_EXPANDABLE_DETAIL_DEFAULT_TO_EXPAND_ARGUMENTS_TO_HPP_
