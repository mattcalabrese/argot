/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_GROUP_HPP_
#define ARGOT_CONC_GROUP_HPP_

#include <argot/conc/nothing.hpp>
#include <argot/conc_traits/as_future.hpp>
//#include <argot/conc_traits/destructive_then_provide.hpp>
//#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/fut/augment.hpp>
#include <argot/fut/squash.hpp>
#include <argot/fut_traits/destructive_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/group.hpp>
#include <argot/receiver/with_trailing_concurrent_provider.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot {
namespace conc {
namespace group_detail {

template< class ExpandedHead >
struct secondary_continuation
{
  // TODO(mattcalabrese) Concept assert

  template< class ExpandedTail >
  constexpr auto operator ()( ExpandedTail&& expanded_tail ) &&
  {
    return prov::group
    ( ARGOT_MOVE( expanded_head )
    , ARGOT_FORWARD( ExpandedTail )( expanded_tail )
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS ExpandedHead expanded_head;
};

template< class Tail >
struct primary_continuation
{
  // TODO(mattcalabrese) Concept assert

  template< class ExpandedHead >
  constexpr auto operator ()( ExpandedHead&& expanded_head ) &&
  {
    return fut::augment
    ( conc_traits::as_future( ARGOT_MOVE( tail_provider ) )
    , secondary_continuation< detail_argot::remove_cvref_t< ExpandedHead > >
      { ARGOT_FORWARD( ExpandedHead )( expanded_head ) }
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS Tail tail_provider;
};

}  // namespace argot::conc(::group_detail)

struct group_fn
{
 // TODO(mattcalabrese) Skip over every instance of conc::nothing_t and
  //                     reference to conc::nothing_t.
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
    ARGOT_CONCEPT_ASSERT( ConcurrentArgumentProvider< H > );

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
  static constexpr detail_argot::remove_cvref_t< Provider >
  make_impl( Provider&& provider )
  {
    return call_detail::forward_and_sink< Provider >( provider );
  }

  template< class HeadProvider, class NextProvider, class... TailProviders >
  static constexpr impl_of_t  // TODO(mattcalabrese) Replace with impl directly
  < detail_argot::remove_cvref_t< HeadProvider >
  , detail_argot::remove_cvref_t< NextProvider >
  , detail_argot::remove_cvref_t< TailProviders >...
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
 private:
 public:
  template< class... ConcProvs
          , ARGOT_REQUIRES
            ( ConcurrentArgumentProvider< detail_argot::remove_cvref_t< ConcProvs > >... )
            ( Sinkable< ConcProvs&& >... )
            ()
          >
  [[nodiscard]] constexpr auto operator()( ConcProvs&&... conc_provs ) const
  {
    if constexpr( sizeof...( ConcProvs ) == 0 ) return conc::nothing;
    else
      return make_impl
      ( call_detail::forward_and_sink< ConcProvs >( conc_provs )... );
  }
} inline constexpr group{};

} // namespace argot(::conc)

template< class... ConcProvs >
struct make_concept_map
< ConcurrentArgumentProvider< conc::group_fn::impl< ConcProvs... > > >
{
  // TODO(mattcalabrese) Constrain
  static constexpr auto
  as_future( conc::group_fn::impl< ConcProvs... >&& self )
  {
    return fut::squash
    ( fut::augment
      ( conc_traits::as_future( ARGOT_MOVE( self.head ) )
      , conc::group_detail::primary_continuation
        < typename conc::group_fn::impl< ConcProvs... > ::tail_type >
        { ARGOT_MOVE( self.tail ) }
      )
    );
  }
/*
  template< class Rec >
  static constexpr auto
  then_provide( conc::group_fn::impl< ConcProvs... >&& self, Rec&& rec )
  {
    return fut::squash
    ( conc_traits::destructive_then_provide
      ( ARGOT_MOVE( self.head )
      , receiver::with_trailing_concurrent_provider
        ( ARGOT_MOVE( rec )
        , ARGOT_MOVE( self.tail )
        )
      )
    );
  }*/
};

// TODO(mattcalabrese) Uncomment and fix persistent_argument_provider

/*
template< class ConcProv >
struct make_concept_map
< PersistentConcurrentArgumentProvider< group_fn::impl< ConcProv > > >
{
  // TODO(mattcalabrese) Use result of prov::as
  using persistent_argument_provider_t
    = typename prov::as_detail::as_impl< value_type_t< ConcProv > >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  then_provide( group_fn::impl< ConcProv > const& self, Receiver&& rec )
  {
    // TODO(mattcalabrese) Don't use a lambda here and make it rvalue ref qual
    return fut_traits::then
    ( self.conc_prov
    , [ rec = ARGOT_MOVE( rec ) ]( auto&& provider ) mutable
      {
        return receiver_traits::receive
        ( ARGOT_MOVE( rec )
        , ARGOT_FORWARD( decltype( provider ) )( provider )
        );
      }
    );
  }
};
*/
} // namespace argot

#endif  // ARGOT_CONC_GROUP_HPP_
