/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_FORGETFUL_INVOKE_HPP_
#define ARGOT_RECEIVER_FORGETFUL_INVOKE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <type_traits>

namespace argot::receiver {

struct forgetful_invoke_fn
{
  template< class Fun >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Fun > );

    ARGOT_NO_UNIQUE_ADDRESS Fun invocable;
  };

  template
  < class Fun
  , ARGOT_REQUIRES
    ( PotentiallyInvocableObject< std::decay_t< Fun > > )
    ( DecaySinkable< Fun&& > )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Fun&& invocable ) const
  {
    return impl< std::decay_t< Fun > >
    { call_detail::forward_and_decay_sink< Fun >( invocable ) };
  }
} inline constexpr forgetful_invoke{};

template< class Fun >
using result_of_forgetful_invoke_t
  = basic_result_of_t< forgetful_invoke_fn const&, Fun >;

template< class Fun >
using result_of_forgetful_invoke
  = basic_result_of< forgetful_invoke_fn const&, Fun >;

}  // namespace (argot::receiver)

namespace argot {

template< class Fun >
struct make_concept_map
< ArgumentReceiver< receiver::forgetful_invoke_fn::impl< Fun > > >
{
  // TODO(mattcalabrese) Constrain
  template
  < class... LeadingArgLists, class... TrailingArgLists, class... P >
  static constexpr void
  receive_branch
  ( receiver::forgetful_invoke_fn::impl< Fun >&& self
  , receiver_traits::argument_list_kinds_t< LeadingArgLists... >
  , receiver_traits::argument_list_kinds_t< TrailingArgLists... >
  , P&&... args
  )
  {
    argot_detail::constexpr_invoke
    ( ARGOT_MOVE( self.invocable ), ARGOT_FORWARD( P )( args )... );
  }
};

}  // namespace argot

#endif  // ARGOT_RECEIVER_FORGETFUL_INVOKE_HPP_
