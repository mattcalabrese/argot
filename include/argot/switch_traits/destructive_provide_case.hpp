/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_CASE_HPP_
#define ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_CASE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/exceptional_switch_body_case.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/nested_receiver.hpp>
#include <argot/receiver/receiver_reference.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/switch_traits/destructive_provide_isolated_case.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_persistent.hpp>
#include <argot/unreachable_function.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot::switch_traits {

template< auto Value >
struct destructive_provide_case_t
{
  template
  < class Body, class Receiver
  , ARGOT_REQUIRES
    ( SwitchBodyCase< Body, Value > )
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_destructive_t< Body, decltype( Value ) >
      >
    )
    ()
  >
  constexpr decltype( auto )
  operator ()( Body&& body, Receiver&& rec ) const
  {
    if constexpr( is_modeled_v< ExceptionalSwitchBodyCase< Body, Value > > )
    {
      destructive_provide_isolated_case< Value >
      ( ARGOT_MOVE( body )
      , receiver::nested_receiver
        ( receiver::receiver_reference( ARGOT_FORWARD( Receiver )( rec ) )
        , leading_argument_list_kinds_of_case_destructive_t< Body, Value >()
        , trailing_argument_list_kinds_of_case_destructive_t< Body, Value >()
        )
      );

      return unreachable_function
      < receiver_traits::result_of_unbound_receive_branch_t
        < Receiver&&
        , argument_list_kinds_of_body_destructive_t< Body, decltype( Value ) >
        >
      >();
    }
    else
      return destructive_provide_isolated_case< Value >
      ( ARGOT_MOVE( body )
      , receiver::nested_receiver
        ( receiver::receiver_reference( ARGOT_FORWARD( Receiver )( rec ) )
        , leading_argument_list_kinds_of_case_destructive_t< Body, Value >()
        , trailing_argument_list_kinds_of_case_destructive_t< Body, Value >()
        )
      );
  }
};

template< auto Value >
destructive_provide_case_t< Value > constexpr destructive_provide_case{};

// TODO(mattcalabrese) Make result type calculators

/*

template< auto Value, class Body, class Receiver >
using result_of_destructive_provide_t
  = basic_result_of_t
    < destructive_provide_t const&, Body&&, ValueType&&, Receiver&& >;

template< auto Value, class Body, class Receiver >
using result_of_destructive_provide
  = basic_result_of
    < destructive_provide_t const&, Body&&, ValueType&&, Receiver&& >;;
*/
}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_CASE_HPP_
