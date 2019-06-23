/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_RUN_HPP_
#define ARGOT_PROV_RUN_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/persistent_invocable_object_with.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace prov {

struct run_fn
{
  template< class Fun >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun > );

    ARGOT_NO_UNIQUE_ADDRESS Fun invocable;
  };

  template< class Fun
          , ARGOT_REQUIRES( InvocableObjectWith< std::decay_t< Fun > > )
                          ( DecaySinkable< Fun&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator ()( Fun&& fun ) const
  {
    return impl< detail_argot::remove_cvref_t< Fun > >
    { call_detail::forward_and_decay_sink< Fun >( fun ) };
  }
} inline constexpr run{};

template< class Fun >
using result_of_run = basic_result_of< run_fn const&, Fun >;

template< class Fun >
using result_of_run_t = basic_result_of_t< run_fn const&, Fun >;

}  // namespace argot(::prov)

template< class Fun >
struct make_concept_map< ArgumentProvider< prov::run_fn::impl< Fun > > >
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t<> >;

  template< class Receiver
          , ARGOT_REQUIRES
            ( ArgumentReceiverOf
              < Receiver
              , receiver_traits::argument_types_t<>
              >
            )
            ()
          >
  static constexpr decltype( auto )
  provide( prov::run_fn::impl< Fun >&& self, Receiver&& rec )
  {
    argot_detail::constexpr_invoke( ARGOT_MOVE( self.invocable ) );
    return receiver_traits::receive( ARGOT_FORWARD( Receiver )( rec ) );
  }
};

template< class Fun >
struct make_concept_map
< PersistentArgumentProvider< prov::run_fn::impl< Fun > >
, ARGOT_REQUIRES( PersistentInvocableObjectWith< Fun > )<>
>
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t<> >;

  template< class Receiver
          , ARGOT_REQUIRES
            ( ArgumentReceiverOf
              < Receiver
              , receiver_traits::argument_types_t<>
              >
            )
            ()
          >
  static constexpr decltype( auto )
  provide( prov::run_fn::impl< Fun > const& self, Receiver&& rec )
  {
    argot_detail::constexpr_invoke( self.invocable );
    return receiver_traits::receive( ARGOT_FORWARD( Receiver )( rec ) );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_RUN_HPP_
