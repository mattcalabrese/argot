/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_NUM_CASES_HPP_
#define ARGOT_SWITCH_TRAITS_NUM_CASES_HPP_

#include <argot/concepts/switch_body.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/switch_traits/case_values.hpp>
#include <argot/value_list.hpp>

#include <cstddef>
#include <type_traits>

namespace argot::switch_traits {
namespace num_cases_detail {

template< class Values >
struct num_cases_impl;

template< auto... Values >
struct num_cases_impl< value_list_t< Values... > >
{
  using type = std::integral_constant< std::size_t, sizeof...( Values ) >;
};

} // namespace argot::switch_traits(::num_cases_detail)

template< class Body >
using num_cases_t
  = ARGOT_REQUIRES( SwitchBody< Body > )
    < typename num_cases_detail::num_cases_impl< case_values_t< Body > >
      ::type
    >;

template< class Body >
using num_cases
  = call_detail::lazy_expand< num_cases_t, Body >;

template< class Body >
num_cases_t< Body > constexpr num_cases_v{};

} // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_NUM_CASES_HPP_
