/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_DEFAULT_HPP_
#define ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_DEFAULT_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/exceptional_switch_body_default_for_type.hpp>
#include <argot/concepts/switch_body_default_for_type.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/receiver/nested_receiver.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/switch_traits/destructive_provide_isolated_default.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_default_destructive.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_default_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/unreachable_function.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::switch_traits {

struct destructive_provide_default_t
{
  template
  < class Body, class ValueType, class Receiver
  , ARGOT_REQUIRES
    ( SwitchBodyDefaultForType< Body, ValueType > )
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_destructive_t< Body, ValueType >
      >
    )
    ()
  >
  constexpr decltype( auto )
  operator ()( Body&& body, ValueType value, Receiver&& rec ) const
  {
    if constexpr
    ( is_modeled_v< ExceptionalSwitchBodyDefaultForType< Body, ValueType > > )
    {
      destructive_provide_isolated_default
      ( ARGOT_MOVE( body ), value
      , receiver::nested_receiver
        ( receiver::receiver_reference( ARGOT_FORWARD( Receiver )( rec ) )
        , leading_argument_list_kinds_of_default_destructive_t
          < Body, ValueType >()
        , trailing_argument_list_kinds_of_default_destructive_t
          < Body, ValueType >()
        )
      );

      return unreachable_function
      < receiver_traits::result_of_unbound_receive_branch_t
        < Receiver&&
        , argument_list_kinds_of_body_destructive_t< Body, ValueType >
        >
      >();
    }
    else
      return destructive_provide_isolated_default
      ( ARGOT_MOVE( body ), value
      , receiver::nested_receiver
        ( receiver::receiver_reference( ARGOT_FORWARD( Receiver )( rec ) )
        , leading_argument_list_kinds_of_default_destructive_t
          < Body, ValueType >()
        , trailing_argument_list_kinds_of_default_destructive_t
          < Body, ValueType >()
        )
      );
  }
} inline constexpr destructive_provide_default{};

template< class Body, class ValueType, class Receiver >
using result_of_destructive_provide_default_t
  = basic_result_of_t
    < destructive_provide_default_t const&, Body&&, ValueType&&, Receiver&& >;

template< class Body, class ValueType, class Receiver >
using result_of_destructive_provide_default
  = basic_result_of
    < destructive_provide_default_t const&, Body&&, ValueType&&, Receiver&& >;

}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_DEFAULT_HPP_
