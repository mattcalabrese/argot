/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_ISOLATED_DEFAULT_HPP_
#define ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_ISOLATED_DEFAULT_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/switch_body_default_for_type.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::switch_traits {

struct destructive_provide_isolated_default_t
{
  // TODO(mattcalabrese) Constrain ValueType to be a valid switch value type.
  //                     Constrain ArgumentReceiver to be able to receive.
  template< class Body, class ValueType, class Receiver
          , ARGOT_REQUIRES( SwitchBodyDefaultForType< Body, ValueType > )
                          ( ArgumentReceiver< remove_cvref_t< Receiver > > )
                          ()
          >
  constexpr decltype( auto )
  operator ()( Body&& body, ValueType value, Receiver&& rec ) const
  {
    return access_raw_concept_map
    < SwitchBodyDefaultForType< Body, ValueType > >
    ::provide_isolated_default
    ( ARGOT_MOVE( body ), ARGOT_MOVE( value )
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
} inline constexpr destructive_provide_isolated_default{};

template< class Body, class ValueType, class Receiver >
using result_of_destructive_provide_isolated_default_t
  = basic_result_of_t
    < destructive_provide_isolated_default_t const&
    , Body&&, ValueType&&, Receiver&&
    >;

template< class Body, class ValueType, class Receiver >
using result_of_destructive_provide_isolated_default
  = basic_result_of
    < destructive_provide_isolated_default_t const&
    , Body&&, ValueType&&, Receiver&&
    >;

}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_DESTRUCTIVE_PROVIDE_ISOLATED_DEFAULT_HPP_
