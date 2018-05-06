/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_EXPAND_CASE_VALUES_FOR_TYPE_HPP_
#define ARGOT_SWITCH_TRAITS_EXPAND_CASE_VALUES_FOR_TYPE_HPP_

#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot::switch_traits {
namespace expand_case_values_for_type_detail {

template< template< auto... > class Template, class ValueType >
struct expand_case_values_for_type_impl
{
  template< auto... Values >
  using apply = Template< static_cast< ValueType >( Values )... >;
};

}  // namespace expand_case_values_for_type_detail

template< class Body, template< auto... > class Template, class ValueType >
using expand_case_values_for_type_t
  = ARGOT_REQUIRES( SwitchBodyForType< Body, ValueType > )
    < typename access_raw_concept_map< SwitchBody< Body > >
      ::template expand_case_values_t
      < case_values_for_type_detail::expand_case_values_for_type_impl
        < Template, ValueType >::template apply
      >
    >;
/*
template< class Body, class ValueType >
using expand_case_values_for_type
  = call_detail::lazy_expand< case_values_for_type_t, Body, ValueType >;

template< class Body, class ValueType >
case_values_for_type_t< Body, ValueType > constexpr case_values_for_type_v{};
*/

}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_EXPAND_CASE_VALUES_FOR_TYPE_HPP_
