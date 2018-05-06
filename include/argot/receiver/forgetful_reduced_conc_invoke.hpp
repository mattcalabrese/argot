/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_FORGETFUL_REDUCED_CONC_INVOKE_HPP_
#define ARGOT_RECEIVER_FORGETFUL_REDUCED_CONC_INVOKE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/reducer_traits/is_homogeneous.hpp>
#include <argot/reducer_traits/reduce.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace receiver {
namespace forgetful_reduced_conc_invoke_detail {

template< class Reducer, class Invocable
        , class LeadingArgLists, class TrailingArgLists
        >
struct continuation;

template< class Reducer, class Invocable
        , class... LeadingArgLists, class... TrailingArgLists
        >
struct continuation
< Reducer, Invocable
, receiver_traits::argument_list_kinds_t< LeadingArgLists... >
, receiver_traits::argument_list_kinds_t< TrailingArgLists... >
>
{
  ARGOT_CONCEPT_ASSERT( ReturnValueReducer< remove_cvref_t< Reducer > > );
  ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Invocable > );

  // TODO(mattcalabrese) Possibly return auto instead of decltype auto
  template< class Provider >
  constexpr decltype( auto ) operator ()( Provider&& provider ) &&
  {
    return prov_traits::provide
    ( ARGOT_FORWARD( Provider )( provider )
    , receiver::nested_receiver
      ( receiver::receiver_reference
        ( receiver::reduced_invoke
          ( ARGOT_MOVE( red ), ARGOT_MOVE( invocable ) )
        )
      , prov_traits::argument_list_kinds_of_destructive_t
        < fut_traits::value_type_t
          < remove_cvref_t
            < result_of_as_future_t
              < conc::result_of_group_t< LeadingArgLists... > >
            >
          >
        >()
      , prov_traits::argument_list_kinds_of_destructive_t
        < fut_traits::value_type_t
          < remove_cvref_t
            < result_of_as_future_t
              < conc::result_of_group_t< TrailingArgLists... > >
            >
          >
        >()
      )
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS Reducer red;
  ARGOT_NO_UNIQUE_ADDRESS Invocable invocable;
};

}  // namespace argot::receiver(::forgetful_reduced_conc_invoke_detail)

struct forgetful_reduced_conc_invoke_t
{
  template< class Exec, class Reducer, class Invocable >
  struct impl
  {
    // TODO(mattcalabrese) Concept assert Exec
    ARGOT_CONCEPT_ASSERT( ReturnValueReducer< remove_cvref_t< Reducer > > );
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Invocable > );

    ARGOT_NO_UNIQUE_ADDRESS Exec exec;
    ARGOT_NO_UNIQUE_ADDRESS Reducer red;
    ARGOT_NO_UNIQUE_ADDRESS Invocable invocable;
  };

  // TODO(mattcalabrese) Constrain exec
  template
  < class Exec, class Reducer, class Invocable
  , ARGOT_REQUIRES( ReturnValueReducer< remove_cvref_t< Reducer > > )
                  ( PotentiallyInvocableObject< std::decay_t< Invocable > > )
                  ( Sinkable< Reducer&& > )
                  ( DecaySinkable< Invocable&& > )
                  ()
  >
  [[nodiscard]]
  constexpr auto operator ()
  ( Exec&& exec, Reducer&& red, Invocable&& invocable ) const
  {
    return impl
    < remove_cvref_t< Exec >
    , remove_cvref_t< Reducer >, std::decay_St< Invocable >
    >
    { call_detail::forward_and_sink< Exec >( exec )
    , call_detail::forward_and_sink< Reducer >( red )
    , call_detail::forward_and_decay_sink< Invocable >( invocable )
    };
  }
} inline constexpr reduced_invoke{};

template< class Exec, class Reducer, class Invocable >
using result_of_forgetful_reduced_conc_invoke_t
  = basic_result_of_t
    < forgetful_reduced_conc_invoke_t const&, Exec, Reducer, Invocable >;

template< class Exec, class Reducer, class Invocable >
using result_of_forgetful_reduced_conc_invoke
  = basic_result_of
    < forgetful_reduced_conc_invoke_t const&, Exec, Reducer, Invocable >;

}  // namespace argot::receiver

template< class Exec, class Reducer, class Invocable >
struct make_concept_map
< ArgumentReceiver
  < receiver::forgetful_reduced_conc_invoke_t::impl
    < Exec, Reducer, Invocable >
  >
>
{
  // TODO(mattcalabrese) Require that all arguments are argument providers
  template
  < class... LeadingArgLists, class... TrailingArgLists, class... P >
  static constexpr decltype( auto )  // TODO(mattcalabrese) Constrain
  receive_branch
  ( receiver::forgetful_reduced_conc_invoke_t::impl
    < forgetful_reduced_conc_invoke_t, Reducer, Invocable >&& self
  , receiver_traits::argument_list_kinds_t< LeadingArgLists... >
  , receiver_traits::argument_list_kinds_t< TrailingArgLists... >
  , P&&... args
  )
  {
    return fut_traits::forgetful_then
    ( conc_traits::as_future( conc::group( ARGOT_FORWARD( P )( args )... ) )
    , ARGOT_MOVE( exec )
    , receiver::forgetful_reduced_conc_invoke_detail::continuation
      < Reducer, Invocable
      , receiver_traits::argument_list_kinds_t< LeadingArgLists... >
      , receiver_traits::argument_list_kinds_t< TrailingArgLists... >
      >
      { ARGOT_MOVE( self.red ), ARGOT_MOVE( self.invocable ) }
    );
  }
};

}  // namespace argot

#endif  // ARGOT_RECEIVER_FORGETFUL_REDUCED_CONC_INVOKE_HPP_
