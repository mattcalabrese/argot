/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CASE_DETAIL_UNREACHABLE_CASE_HPP_
#define ARGOT_CASE_DETAIL_UNREACHABLE_CASE_HPP_

#include <argot/impossible.hpp>
#include <argot/case/detail/cast_value_list_elements.hpp>
#include <argot/concepts/argument_receiver.hpp> // of
#include <argot/concepts/case_labels.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/concepts/true.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/value_list.hpp>
#include <argot/value_zipper.hpp>

namespace argot {
namespace case_detail {

template< class Cases >
struct unreachable_case_t {};

}  // namespace argot(::case_detail)

template< class Cases >
struct make_concept_map
< SwitchBody< case_detail::unreachable_case_t< Cases > > >
{
  using case_values_t
    = typename access_raw_concept_map< CaseLabels< Cases > >::case_values_t;

  template< template< auto... > class Template >
  using expand_case_values_t
    = typename access_raw_concept_map< CaseLabels< Cases > >
      ::template expand_case_values_t< Template >;
};

// TODO(mattcalabrese) Constrain
template< class Cases, auto Value >
struct make_concept_map
< SwitchBodyCase< case_detail::unreachable_case_t< Cases >, Value >
, ARGOT_REQUIRES
  ( True
    < value_zipper_contains_v
      < case_detail::cast_value_list_elements_t
        < decltype( Value )
        , typename access_raw_concept_map< CaseLabels< Cases > >::case_values_t
        >
      , Value
      >
    >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain and possibly push unreachable into default argument
  template< class Receiver >
  static impossible provide_isolated_case
  ( case_detail::unreachable_case_t< Cases > self, Receiver&& rec ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

// TODO(mattcalabrese) Constrain
template< class Cases, auto Value >
struct make_concept_map
< PersistentSwitchBodyCase< case_detail::unreachable_case_t< Cases >, Value > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain and possibly push unreachable into default argument
  template< class Receiver >
  static impossible provide_isolated_case
  ( case_detail::unreachable_case_t< Cases > self, Receiver&& rec ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

}  // namespace argot

#endif  // ARGOT_CASE_DETAIL_UNREACHABLE_CASE_HPP_
