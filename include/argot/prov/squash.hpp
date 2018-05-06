/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SQUASH_HPP_
#define ARGOT_PROV_SQUASH_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/higher_order_argument_provider.hpp>
#include <argot/concepts/higher_order_persistent_argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/prov_traits/argument_list_kinds_of.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver/nested_receiver.hpp>
#include <argot/receiver/provide_arguments_to.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace prov {
namespace squash_detail {

template< class ArgumentTypes >
struct squashed_argument_types_impl_impl;

template< class... P >
struct squashed_argument_types_impl_impl
< receiver_traits::argument_types_t< P... > >
{
  using type
    = call_detail::concatenate_t
      < prov_traits::argument_list_kinds_of_t< P >... >;
};

template< class ArgumentListKinds >
struct squashed_argument_types_impl;

template< class... ArgumentListKinds >
struct squashed_argument_types_impl
< receiver_traits::argument_list_kinds_t< ArgumentListKinds... > >
{
  using type
    = call_detail::concatenate_t
      < typename squashed_argument_types_impl_impl< ArgumentListKinds >
        ::type...
      >;
};

template< class Provider >
using squashed_argument_types_t
  = typename squashed_argument_types_impl
    < prov_traits::argument_list_kinds_of_destructive_t< Provider > >::type;

template< class Provider >
using persistent_squashed_argument_types_t
  = typename squashed_argument_types_impl
    < prov_traits::argument_list_kinds_of_persistent_t< Provider > >::type;

}  // namespace argot::prov(::squash_detail)

struct squash_fn
{
 public:
  template< class Provider >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( HigherOrderArgumentProvider< Provider > );

    ARGOT_NO_UNIQUE_ADDRESS Provider provider;
  };
 public:
  template< class Provider
          , ARGOT_REQUIRES
            ( HigherOrderArgumentProvider< remove_cvref_t< Provider > > )
            ( Sinkable< Provider&& > )
            ()
          >
  [[nodiscard]] constexpr auto operator ()( Provider&& provider ) const
  {
    using provider_type = remove_cvref_t< Provider >;

    // TODO(mattcalabrese) Possibly generalize conditions
    if constexpr( std::is_same_v< provider_type, prov::nothing_t > )
      return prov::nothing;
    else
      if constexpr( prov::value_of_fn::is_unary_value_of_v< provider_type > )
        return prov::value_of_fn::head_value
        ( ARGOT_FORWARD( Provider )( provider ) );
      else
        return impl< remove_cvref_t< Provider > >
        { call_detail::forward_and_sink< Provider >( provider ) };
  }
} inline constexpr squash{};

template< class Provider >
using result_of_squash = basic_result_of< squash_fn const&, Provider >;

template< class Provider >
using result_of_squash_t = basic_result_of_t< squash_fn const&, Provider >;

}  // namespace argot(::prov)

template< class Provider >
struct make_concept_map< ArgumentProvider< prov::squash_fn::impl< Provider > > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , prov::squash_detail::squashed_argument_types_t< Provider >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::squash_fn::impl< Provider >&& self, Receiver&& rec )
  {
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( self.provider )
    , receiver::provide_arguments_to
      ( receiver::receiver_reference( ARGOT_MOVE( rec ) ) )
    );
  }
};

template< class Provider >
struct make_concept_map
< PersistentArgumentProvider< prov::squash_fn::impl< Provider > >
, ARGOT_REQUIRES( HigherOrderPersistentArgumentProvider< Provider > )<>
>
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , prov::squash_detail::persistent_squashed_argument_types_t< Provider >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::squash_fn::impl< Provider > const& self, Receiver&& rec )
  {
    return prov_traits::persistent_provide
    ( self.provider
    , receiver::provide_arguments_to
      ( receiver::receiver_reference( ARGOT_MOVE( rec ) ) )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_SQUASH_HPP_
