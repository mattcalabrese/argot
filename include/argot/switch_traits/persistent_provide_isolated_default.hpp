/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_ISOLATED_DEFAULT_HPP_
#define ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_ISOLATED_DEFAULT_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::switch_traits {

struct persistent_provide_isolated_default_t
{
  //                     Constrain ArgumentReceiver to be able to receive.
  template< class Body, class ValueType, class Receiver
          , ARGOT_REQUIRES
            ( PersistentSwitchBodyDefaultForType< Body, ValueType > )
            ( ArgumentReceiver< remove_cvref_t< Receiver > > )
            ()
          >
  constexpr decltype( auto )
  operator ()( Body const& body, ValueType value, Receiver&& rec ) const
  {
    return access_raw_concept_map
    < PersistentSwitchBodyDefaultForType< Body, ValueType > >
    ::provide_isolated_default
    ( body, ARGOT_MOVE( value ), ARGOT_FORWARD( Receiver )( rec ) );
  }
} inline constexpr persistent_provide_isolated_default{};

template< class Body, class ValueType, class Receiver >
using result_of_persistent_provide_isolated_default_t
  = basic_result_of_t
    < persistent_provide_isolated_default_t const&
    , Body&&, ValueType&&, Receiver&&
    >;

template< class Body, class ValueType, class Receiver >
using result_of_persistent_provide_isolated_default
  = basic_result_of
    < persistent_provide_isolated_default_t const&
    , Body&&, ValueType&&, Receiver&&
    >;

}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_ISOLATED_DEFAULT_HPP_
