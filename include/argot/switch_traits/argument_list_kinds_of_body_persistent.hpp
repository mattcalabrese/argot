/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_BODY_PERSISTENT_HPP_
#define ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_BODY_PERSISTENT_HPP_

#include <argot/impossible.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_switch_body_for_type.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/switch_traits/argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/argument_list_kinds_of_default_persistent.hpp>
#include <argot/switch_traits/case_value_for_type_at.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_default_persistent.hpp>
#include <argot/switch_traits/num_cases.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_default_persistent.hpp>

#include <type_traits>
#include <utility>

namespace argot::switch_traits {
namespace argument_list_kinds_of_body_persistent_detail {

struct empty_body_impl
{
  using type = receiver_traits::argument_list_kinds_t<>;
};

template< class Body, class ValueType >
struct default_based_impl
{
  using type
    = call_detail::concatenate_t
      < leading_argument_list_kinds_of_default_persistent_t< Body, ValueType >
      , argument_list_kinds_of_default_persistent_t< Body, ValueType >
      , trailing_argument_list_kinds_of_default_persistent_t< Body, ValueType >
      >;
};

template< class Body, class ValueType >
struct case_based_impl
{
  using type
    = call_detail::concatenate_t
      < leading_argument_list_kinds_of_case_persistent_t
        < Body, case_value_for_type_at_v< Body, ValueType, 0 > >
      , argument_list_kinds_of_case_persistent_t
        < Body, case_value_for_type_at_v< Body, ValueType, 0 > >
      , trailing_argument_list_kinds_of_case_persistent_t
        < Body, case_value_for_type_at_v< Body, ValueType, 0 > >
      >;
};

template< class Body, class ValueType >
struct no_cases_impl
{
  using type
    = typename argot_detail::conditional
      < is_modeled_v
        < PersistentSwitchBodyDefaultForType< Body, ValueType > >
      >::template apply
      < default_based_impl< Body, ValueType >
      , empty_body_impl
      >::type;
};

}  // namespace
   //   argot::switch_traits(::argument_list_kinds_of_body_persistent_detail)

template< class Body, class ValueType >
using argument_list_kinds_of_body_persistent_t
  = ARGOT_REQUIRES( PersistentSwitchBodyForType< Body, ValueType > )
    < typename argot_detail::conditional< num_cases_v< Body > == 0 >
      ::template apply
      < argument_list_kinds_of_body_persistent_detail
        ::no_cases_impl< Body, ValueType >
      , argument_list_kinds_of_body_persistent_detail
        ::case_based_impl< Body, ValueType >
      >::type
    >;

template< class Body, class ValueType >
using argument_list_kinds_of_body_persistent
  = call_detail::lazy_expand
    < argument_list_kinds_of_body_persistent_t, Body, ValueType >;

// TODO(mattcalabrese) Pass Value
template< class Body, class ValueType >
argument_list_kinds_of_body_persistent_t< Body, ValueType > constexpr
argument_list_kinds_of_body_persistent_v{};

}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_BODY_PERSISTENT_HPP_
