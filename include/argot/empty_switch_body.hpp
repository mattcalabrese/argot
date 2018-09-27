/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_EMPTY_SWITCH_BODY_HPP_
#define ARGOT_EMPTY_SWITCH_BODY_HPP_

#include <argot/concepts/persistent_switch_body_for_type.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/concepts/switch_condition.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/value_list.hpp>

namespace argot {

struct empty_switch_body_t {} inline constexpr empty_switch_body{};

template<>
struct make_concept_map< SwitchBody< empty_switch_body_t > >
{
  using case_values_t = value_list_t<>;

  template< template< auto... > class Template >
  using expand_case_values_t = Template<>;
};

} // namespace argot

#endif  // ARGOT_EMPTY_SWITCH_BODY_HPP_
