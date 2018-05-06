/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_CASE_VALUES_FOR_TYPE_HPP_
#define ARGOT_SWITCH_TRAITS_CASE_VALUES_FOR_TYPE_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/value_list.hpp>

namespace argot::switch_traits {

#if 1

namespace case_values_for_type_detail {

template< class Values >
struct case_values_for_type_impl;

template< auto... Values >
struct case_values_for_type_impl< value_list_t< Values... > >
{
  template< class ValueType >
  using apply = value_list_t< static_cast< ValueType >( Values )... >;
};

}  // namespace case_values_for_type_detail

template< class Body, class ValueType >
using case_values_for_type_t
  = ARGOT_REQUIRES( SwitchBodyForType< Body, ValueType > )
    < typename case_values_for_type_detail::case_values_for_type_impl
      < typename access_raw_concept_map< SwitchBody< Body > >::case_values_t >
      ::template apply< ValueType >
    >;

#else

namespace case_values_for_type_detail {

template< class ValueType >
struct case_values_for_type_impl
{
  template< auto... Values >
  using apply = value_list_t< static_cast< ValueType >( Values )... >;
};

}  // namespace case_values_for_type_detail

template< class Body, class ValueType >
using case_values_for_type_t
  = ARGOT_REQUIRES( SwitchBodyForType< Body, ValueType > )
    < typename access_raw_concept_map< SwitchBody< Body > >
      ::template expand_case_values_t
      < case_values_for_type_detail::case_values_for_type_impl< ValueType >
        ::template apply
      >
    >;

#endif

template< class Body, class ValueType >
using case_values_for_type
  = call_detail::lazy_expand< case_values_for_type_t, Body, ValueType >;

template< class Body, class ValueType >
case_values_for_type_t< Body, ValueType > constexpr case_values_for_type_v{};

}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_CASE_VALUES_FOR_TYPE_HPP_
