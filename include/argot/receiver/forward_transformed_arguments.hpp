/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_FORWARD_TRANSFORMED_ARGUMENTS_HPP_
#define ARGOT_RECEIVER_FORWARD_TRANSFORMED_ARGUMENTS_HPP_

//[description
/*`
receiver::forward_transformed_arguments is a facility that takes an
ArgumentReceiver and a unary /invocable/, resulting in an ArgumentReceiver that
forwards each individual argument it receives to the /invocable/, and passes the
result of those transformations to the original ArgumentReceiver. The original
ArgumentReceiver and the /decayed/ invocable are captured by value.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/group.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::receiver {
//<-
namespace detail_forward_transformed_arguments {

template< class... ArgumentListKinds >
struct individual_argument_types {};

template<>
struct individual_argument_types<>
{
  using type = receiver_traits::argument_list_kinds_t<>;
};

template< class... HeadArgumentListKinds
        , class... TailArgumentListKinds
        >
struct individual_argument_types
< receiver_traits::argument_list_kinds_t
  < receiver_traits::argument_types_t< HeadArgumentListKinds... >
  , TailArgumentListKinds...
  >
>
{
  using type
    = call_detail::concatenate_t
      < receiver_traits::argument_list_kinds_t
        < receiver_traits::argument_types_t< HeadArgumentListKinds >... >
      , typename individual_argument_types
        < TailArgumentListKinds... >::type
      >;
};

template< class... ArgumentListKinds >
using individual_argument_types_t
  = typename individual_argument_types< ArgumentListKinds... >::type;

template< class Invocable, class P, class /*Enabler*/ = void >
struct transformed_argument_types_impl {};

template< class Invocable, class... P >
struct transformed_argument_types_impl
< Invocable, receiver_traits::argument_types_t< P... >
, std::void_t< std::invoke_result_t< Invocable&&, P&& >&&... >
>
{
  using type
    = receiver_traits::argument_types_t
      < std::invoke_result_t< Invocable&&, P&& >&&... >;
};

template< class Invocable, class P >
using transformed_argument_types_impl_t
  = typename transformed_argument_types_impl< Invocable, P >::type;

template< class Invocable, class... ArgumentListKinds >
using transformed_argument_types_t
  = receiver_traits::argument_list_kinds_t
    < transformed_argument_types_impl_t< Invocable, ArgumentListKinds >... >;

template< class Invocable, class... ArgumentListKinds >
transformed_argument_types_t< Invocable, ArgumentListKinds... > constexpr
transformed_argument_types{};

} // namespace argot::receiver(::detail_forward_transformed_arguments)
//->

struct forward_transformed_arguments_fn
{
  //<-
  template< class Receiver, class Invocable >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentReceiver< Receiver > );
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Invocable > );

    Receiver receiver;
    Invocable invocable;
  };
  //->
  template< class Receiver, class Invocable
          , ARGOT_REQUIRES
            ( ArgumentReceiver< detail_argot::remove_cvref_t< Receiver > > )
            ( PotentiallyInvocableObject< std::decay_t< Invocable&& > > )
            ( Sinkable< Receiver&& > )
            ( DecaySinkable< Invocable&& > )
            ()
          >
  constexpr auto
  operator ()( Receiver&& receiver, Invocable&& invocable ) const//=;
  //<-
  {
    return impl
    < detail_argot::remove_cvref_t< Receiver >
    , detail_argot::remove_cvref_t< Invocable >
    >
    { call_detail::forward_and_sink< Receiver >( receiver )
    , call_detail::forward_and_decay_sink< Invocable >( invocable )
    };
  } //->
} inline constexpr forward_transformed_arguments{};

template< class Receiver, class Invocable >
using result_of_forward_transformed_arguments_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t
    < forward_transformed_arguments_fn const&, Receiver&&, Invocable&& >; //->

template< class Receiver, class Invocable >
using result_of_forward_transformed_arguments//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of
    < forward_transformed_arguments_fn const&, Receiver&&, Invocable&& >; //->

} // namespace (argot::receiver)

//]

namespace argot {

template< class Receiver, class Invocable >
struct make_concept_map
< ArgumentReceiver
  < receiver::forward_transformed_arguments_fn::impl< Receiver, Invocable > >
>
{
  // TODO(mattcalabrese) Constraints
  template
  < /*class Self
  , */class... LeadingArgumentListKinds, class... TrailingArgumentListKinds
  , class... P
/*, ARGOT_REQUIRES
    ( InvocableWithKinds
      < Invocable const&
      , receiver::detail_forward_transformed_arguments
        ::individual_argument_types_t
        < receiver_traits::argument_list_kinds_t< LeadingArgumentListKinds... >
        , receiver_traits::argument_list_kinds_t
          < receiver_traits::argument_types_t< P&& >... >
        , receiver_traits::argument_list_kinds_t< TrailingArgumentListKinds... >
        >
      >
    )
    ( ArgumentReceiverOfKinds
      < Receiver
      , call_detail::concatenate_t
        < receiver::detail_forward_transformed_arguments
          ::transformed_argument_types
          < Invocable const&, LeadingArgumentListKinds... >
        , receiver_traits::argument_list_kinds_t
          < receiver_traits::argument_types_t
            < std::invoke_result_t< Invocable const&, P&& >... >
          >
        , receiver::detail_forward_transformed_arguments
          ::transformed_argument_types
          < Invocable const&, TrailingArgumentListKinds... >
        >
      >
    )
    ()*/
  >
  static constexpr decltype( auto )
  receive_branch
  ( receiver::forward_transformed_arguments_fn::impl< Receiver, Invocable >&&
      self
  , receiver_traits::argument_list_kinds_t< LeadingArgumentListKinds... >
  , receiver_traits::argument_list_kinds_t< TrailingArgumentListKinds... >
  , P&&... args
  )
  {
    // TODO(mattcalabrese) Handle void-to-regular-void constexpr_invoke
    return receiver_traits::receive_branch
    ( ARGOT_MOVE( self.receiver )
    , receiver::detail_forward_transformed_arguments
      ::transformed_argument_types
      < Invocable const&, LeadingArgumentListKinds... >
    , receiver::detail_forward_transformed_arguments
      ::transformed_argument_types
      < Invocable const&, TrailingArgumentListKinds... >
    , argot_detail::constexpr_invoke
      ( static_cast< Invocable const& >( self.invocable )
      , ARGOT_FORWARD( P )( args )
      )...
    );
  }
};

} // namespace argot

#endif  // ARGOT_RECEIVER_FORWARD_TRANSFORMED_ARGUMENTS_HPP_
