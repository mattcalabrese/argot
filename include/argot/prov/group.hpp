/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_GROUP_HPP_
#define ARGOT_PROV_GROUP_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov/provider_reference.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/receiver/with_trailing_provider.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace prov {

struct group_fn
{
 public:
  // TODO(mattcalabrese) Skip over every instance of prov::nothing_t and
  //                     reference to prov::nothing_t.
  //                     Collapse groups of groups.
  template< class... T >
  struct impl_of;

  template< class... T >
  using impl_of_t = typename impl_of< T... >::type;

  template< class... T >
  struct impl;

  template< class H, class N, class... T >
  struct impl< H, N, T... >
  {
    ARGOT_CONCEPT_ASSERT( ArgumentProvider< H > );

    using tail_type = impl_of_t< N, T... >;

    ARGOT_NO_UNIQUE_ADDRESS H head;
    ARGOT_NO_UNIQUE_ADDRESS impl_of_t< N, T... > tail;
  };

  template< class H >
  struct impl_of< H >
  {
    using type = H;
  };

  template< class H, class N, class... T >
  struct impl_of< H, N, T... >
  {
    using type = impl< H, N, T... >;
  };

  template< class Provider >
  static constexpr remove_cvref_t< Provider >
  make_impl( Provider&& provider )
  {
    return call_detail::forward_and_sink< Provider >( provider );
  }

  template< class HeadProvider, class NextProvider, class... TailProviders >
  static constexpr impl_of_t  // TODO(mattcalabrese) Replace with impl directly
  < remove_cvref_t< HeadProvider >
  , remove_cvref_t< NextProvider >
  , remove_cvref_t< TailProviders >...
  >
  make_impl( HeadProvider&& head_provider, NextProvider&& next_provider
           , TailProviders&&... tail_providers
           )
  {
    return
    { call_detail::forward_and_sink< HeadProvider >( head_provider )
    , make_impl
      ( call_detail::forward_and_sink< NextProvider >( next_provider )
      , call_detail::forward_and_sink< TailProviders >( tail_providers )...
      )
    };
  }
 public:
  template< class... Providers
          , ARGOT_REQUIRES
            ( ArgumentProvider< remove_cvref_t< Providers > >... )
            ( Sinkable< Providers&& >... )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Providers&&... providers ) const
  noexcept( ( call_detail::is_nothrow_sinkable_v< Providers&& > && ... ) )
  {
    if constexpr( sizeof...( Providers ) == 0 ) return prov::nothing;
    else
      return make_impl
      ( call_detail::forward_and_sink< Providers >( providers )... );
  }
} inline constexpr group{};

template< class... Providers >
using result_of_group = basic_result_of< group_fn const&, Providers... >;

template< class... Providers >
using result_of_group_t = basic_result_of_t< group_fn const&, Providers... >;

}  // namespace argot(::prov)

template< class... T >
struct make_concept_map
< ArgumentProvider< prov::group_fn::impl< T... > > >
{
  // TODO(mattcalabrese) Make this conditional noexcept
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , call_detail::permute_t
        < prov_traits::argument_list_kinds_of_destructive_t< T >... >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::group_fn::impl< T... >&& self, Receiver&& rec )
  {
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( self.head )
    , receiver::with_trailing_provider
      ( receiver::receiver_reference( ARGOT_MOVE( rec ) )
      , prov::provider_reference( ARGOT_MOVE( self.tail ) )
      )
    );
  }
};

template< class... T >
struct make_concept_map
< PersistentArgumentProvider< prov::group_fn::impl< T... > >
, ARGOT_REQUIRES( PersistentArgumentProvider< T >... )<>
>
{
  // TODO(mattcalabrese) Make this conditional noexcept
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , call_detail::permute_t
        < prov_traits::argument_list_kinds_of_persistent_t< T >... >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::group_fn::impl< T... > const& self, Receiver&& rec )
  {
    return prov_traits::persistent_provide
    ( self.head
    , receiver::with_trailing_provider
      ( receiver::receiver_reference( ARGOT_MOVE( rec ) )
      , prov::provider_reference( self.tail )
      )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_GROUP_HPP_
