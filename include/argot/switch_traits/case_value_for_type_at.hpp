/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_CASE_VALUE_FOR_TYPE_AT_HPP_
#define ARGOT_SWITCH_TRAITS_CASE_VALUE_FOR_TYPE_AT_HPP_

#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/gen/requires.hpp>
#include <argot/switch_traits/case_values_for_type.hpp>
#include <argot/value_zipper.hpp>

#include <cstddef>

namespace argot::switch_traits {

// TODO(mattcalabrese) Constrain to the index being in range.
template< class Body, class ValueType, std::size_t Index >
ARGOT_REQUIRES( SwitchBodyForType< Body, ValueType > )
< ValueType > constexpr case_value_for_type_at_v
  = value_zipper_at_t< case_values_for_type_t< Body, ValueType >, Index >
    ::value;

// TODO(mattcalabrese) Make non-eager form

}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_CASE_VALUE_FOR_TYPE_AT_HPP_
