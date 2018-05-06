/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_TRAILING_ARGUMENT_LIST_KINDS_OF_DEFAULT_DESTRUCTIVE_HPP_
#define ARGOT_SWITCH_TRAITS_TRAILING_ARGUMENT_LIST_KINDS_OF_DEFAULT_DESTRUCTIVE_HPP_

#include <argot/detail/detection.hpp>
#include <argot/concepts/switch_body_default_for_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot {
namespace switch_traits {

template< class Def, class ValueType >
using trailing_argument_list_kinds_of_default_destructive_t
  = ARGOT_REQUIRES( SwitchBodyDefaultForType< Def, ValueType > )
    < typename access_raw_concept_map
      < SwitchBodyDefaultForType< Def, ValueType > >
      ::trailing_argument_list_kinds_t
    >;

template< class Def, class ValueType >
using trailing_argument_list_kinds_of_default_destructive
  = call_detail::lazy_expand
    < trailing_argument_list_kinds_of_default_destructive_t, Def, ValueType >;

template< class Def, class ValueType >
trailing_argument_list_kinds_of_default_destructive_t< Def, ValueType >
constexpr trailing_argument_list_kinds_of_default_destructive_v{};

}  // namespace argot(::switch_traits)

}  // namespace argot

#endif
// ARGOT_SWITCH_TRAITS_TRAILING_ARGUMENT_LIST_KINDS_OF_DEFAULT_DESTRUCTIVE_HPP_
