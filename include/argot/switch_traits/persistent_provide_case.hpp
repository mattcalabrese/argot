/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_CASE_HPP_
#define ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_CASE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/exceptional_persistent_switch_body_case.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_persistent.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/persistent_provide_isolated_case.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_persistent.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/unreachable_function.hpp>

#include <type_traits>

namespace argot::switch_traits {

template< auto Value >
struct persistent_provide_case_t
{
  template
  < class Body, class Receiver
  , ARGOT_REQUIRES
    ( PersistentSwitchBodyCase< Body, Value > )
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_persistent_t< Body, decltype( Value ) >
      >
    )
    ()
  >
  constexpr decltype( auto )
  operator ()( Body const& body, Receiver&& rec ) const
  {
    if constexpr
    ( is_modeled_v< ExceptionalPersistentSwitchBodyCase< Body, Value > > )
    {
      persistent_provide_isolated_case< Value >
      ( body
      , receiver::nested_receiver
        ( receiver::receiver_reference( ARGOT_FORWARD( Receiver )( rec ) )
        , leading_argument_list_kinds_of_case_persistent_t< Body, Value >()
        , trailing_argument_list_kinds_of_case_persistent_t< Body, Value >()
        )
      );

      return unreachable_function
      < receiver_traits::result_of_unbound_receive_branch_t
        < Receiver&&
        , argument_list_kinds_of_body_persistent_t< Body, decltype( Value ) >
        >
      >();
    }
    else
      return persistent_provide_isolated_case< Value >
      ( body
      , receiver::nested_receiver
        ( receiver::receiver_reference( ARGOT_FORWARD( Receiver )( rec ) )
        , leading_argument_list_kinds_of_case_persistent_t< Body, Value >()
        , trailing_argument_list_kinds_of_case_persistent_t< Body, Value >()
        )
      );
  }
};

template< auto Value >
persistent_provide_case_t< Value > constexpr persistent_provide_case{};

// TODO(mattcalabrese) Make result type calculators

/*

template< auto Value, class Case, class Receiver >
using result_of_destructive_provide_t
  = basic_result_of_t
    < destructive_provide_t const&, Case&&, ValueType&&, Receiver&& >;

template< auto Value, class Case, class Receiver >
using result_of_destructive_provide
  = basic_result_of
    < destructive_provide_t const&, Case&&, ValueType&&, Receiver&& >;;
*/
}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_CASE_HPP_
