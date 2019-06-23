/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_REDUCED_INVOKE_HPP_
#define ARGOT_RECEIVER_REDUCED_INVOKE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/reducer_traits/is_homogeneous.hpp>
#include <argot/reducer_traits/reduce.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace receiver {
namespace reduced_invoke_detail {

// TODO(mattcalabrese) Make callable only as an rvalue
// TODO(mattcalabrese) Require Fun is an rvalue and move instead of forward
template< class Fun, class... P >
constexpr auto bind_all( Fun&& fun, P&&... args )
{
  return [ &fun, &args... ]() -> decltype( auto )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... );
  };
}

template< class Fun, class P >
struct raw_return_types_of_calls_impl;

// TODO(mattcalabrese) Define without an instantiation.
template< class Fun, class... P >
struct raw_return_types_of_calls_impl
< Fun, receiver_traits::argument_types_t< P... > >
{
  using type = argot_detail::result_of_constexpr_invoke_t< Fun&&, P... >;
};

template< class Fun, class... ArgumentListKinds >
using raw_return_types_of_calls_impl_t
  = typename raw_return_types_of_calls_impl< Fun, ArgumentListKinds... >::type;

template< class Fun, class... ArgumentListKinds >
using raw_return_types_of_calls_t
  = reducer_traits::return_types_t
    < raw_return_types_of_calls_impl_t< Fun, ArgumentListKinds >... >;

}  // namespace argot::receiver::reduced_invoke_detail

struct reduced_invoke_t
{
  template< class Reducer, class Invocable >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ReturnValueReducer< detail_argot::remove_cvref_t< Reducer > > );
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Invocable > );

    Reducer reducer;
    Invocable invocable;
  };

  template
  < class Reducer, class Invocable
  , ARGOT_REQUIRES( ReturnValueReducer< detail_argot::remove_cvref_t< Reducer > > )
                  ( PotentiallyInvocableObject< std::decay_t< Invocable > > )
                  ( Sinkable< Reducer&& > )
                  ( DecaySinkable< Invocable&& > )
                  ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Reducer&& reducer, Invocable&& invocable ) const
  {
    return impl< detail_argot::remove_cvref_t< Reducer >, std::decay_t< Invocable > >
    { call_detail::forward_and_sink< Reducer >( reducer )
    , call_detail::forward_and_decay_sink< Invocable >( invocable )
    };
  }
} inline constexpr reduced_invoke{};

template< class Reducer, class Invocable >
using result_of_reduced_invoke_t
  = basic_result_of_t< reduced_invoke_t const&, Reducer, Invocable >;

template< class Reducer, class Invocable >
using result_of_reduced_invoke
  = basic_result_of< reduced_invoke_t const&, Reducer, Invocable >;

}  // namespace argot::receiver

template< class Reducer, class Invocable >
struct make_concept_map
< ArgumentReceiver< receiver::reduced_invoke_t::impl< Reducer, Invocable > > >
{
  template
  < class... LeadingArgLists, class... TrailingArgLists, class... P >
  static constexpr decltype( auto )  // TODO(mattcalabrese) Constrain
  receive_branch
  ( receiver::reduced_invoke_t::impl< Reducer, Invocable >&& self
  , receiver_traits::argument_list_kinds_t< LeadingArgLists... >
  , receiver_traits::argument_list_kinds_t< TrailingArgLists... >
  , P&&... args
  )
  {
    return reducer_traits::reduce
    ( ARGOT_MOVE( self.reducer )
    , typename argot_detail::conditional
      < !reducer_traits::is_homogeneous_v< Reducer > >::template half_meta_apply
      < receiver::reduced_invoke_detail::raw_return_types_of_calls_t
      , reducer_traits::return_types_t<>
      , Invocable, LeadingArgLists...
      >{}
    , typename argot_detail::conditional
      < !reducer_traits::is_homogeneous_v< Reducer > >::template half_meta_apply
      < receiver::reduced_invoke_detail::raw_return_types_of_calls_t
      , reducer_traits::return_types_t<>
      , Invocable, TrailingArgLists...
      >{}
    , receiver::reduced_invoke_detail::bind_all
      ( ARGOT_MOVE( self.invocable ), ARGOT_FORWARD( P )( args )... )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_RECEIVER_REDUCED_INVOKE_HPP_
