/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CASE_DETAIL_CAST_VALUE_LIST_ELEMENTS_HPP_
#define ARGOT_CASE_DETAIL_CAST_VALUE_LIST_ELEMENTS_HPP_

#include <argot/value_list.hpp>

namespace argot {
namespace case_detail {

// TODO(mattcalabrese) Constrain to castability

template< class ValueType, class ValueList >
struct cast_value_list_elements {};

template< class ValueType, auto... Values >
struct cast_value_list_elements< ValueType, value_list_t< Values... > >
{
  using type = value_list_t< static_cast< ValueType >( Values )... >;
};

template< class ValueType, class ValueList >
using cast_value_list_elements_t
  = typename cast_value_list_elements< ValueType, ValueList >::type;

} // namespace argot(::case_detail)
} // namespace argot

#endif  // ARGOT_CASE_DETAIL_CAST_VALUE_LIST_ELEMENTS_HPP_
