/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_EXPAND_CASE_VALUES_HPP_
#define ARGOT_SWITCH_TRAITS_EXPAND_CASE_VALUES_HPP_

#include <argot/concepts/switch_body.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot::switch_traits {

template< class Body, template< auto... > class Template >
using expand_case_values_t
  = ARGOT_REQUIRES( SwitchBody< Body > )
    < typename access_raw_concept_map< SwitchBody< Body > >
      ::template expand_case_values_t< Template >
    >;

// TODO(mattcalabrese) Make lazy form.
/*
template< class Body >
case_values_t< Body > constexpr case_values_v{};
*/

} // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_EXPAND_CASE_VALUES_HPP_
