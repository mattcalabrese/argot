/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CASE_DETAIL_AS_CONSTANT_HPP_
#define ARGOT_CASE_DETAIL_AS_CONSTANT_HPP_

#include <argot/case/detail/cast_value_list_elements.hpp>
#include <argot/concepts/argument_receiver.hpp> // of
#include <argot/concepts/case_labels.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/concepts/true.hpp>
#include <argot/detail/constant.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>
#include <argot/value_list.hpp>
#include <argot/value_zipper.hpp>

namespace argot {
namespace case_detail {

template< class Cases >
struct as_constant_t {};

template< class Values >
struct values_to_integral_constant_argument_list_kinds;

template< auto... Values >
struct values_to_integral_constant_argument_list_kinds
< value_list_t< Values... > >
{
  using type
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < call_detail::constant< Values >&& >...
      >;
};

template< class Values >
using values_to_integral_constant_argument_list_kinds_t
  = typename values_to_integral_constant_argument_list_kinds< Values >::type;

}  // namespace argot(::case_detail)

template< class Cases >
struct make_concept_map< SwitchBody< case_detail::as_constant_t< Cases > > >
{
  // TODO(mattcalabrese) Don't access raw
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
< SwitchBodyCase< case_detail::as_constant_t< Cases >, Value >
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
 private:
  using typed_value_list
    = case_detail::cast_value_list_elements_t
      < decltype( Value )
      , typename access_raw_concept_map< CaseLabels< Cases > >::case_values_t
      >;

  using partition = value_zipper_find_t< typed_value_list, Value >;
 public:
  using leading_argument_list_kinds_t
    = case_detail::values_to_integral_constant_argument_list_kinds_t
      < typename partition::leading_t >;

  using trailing_argument_list_kinds_t
    = case_detail::values_to_integral_constant_argument_list_kinds_t
      < typename partition::trailing_t >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto ) provide_isolated_case
  ( case_detail::as_constant_t< Cases > self, Receiver&& rec )
  {
    return receiver_traits::receive
    ( ARGOT_FORWARD( Receiver )( rec )
    , std::integral_constant< detail_argot::remove_cvref_t< decltype( Value ) >, Value >()
    );
  }
};

// TODO(mattcalabrese) Constrain
template< class Cases, auto Value >
struct make_concept_map
< PersistentSwitchBodyCase< case_detail::as_constant_t< Cases >, Value > >
{
 private:
  using typed_value_list
    = case_detail::cast_value_list_elements_t
      < decltype( Value )
      , typename access_raw_concept_map< CaseLabels< Cases > >::case_values_t
      >;

  using partition = value_zipper_find_t< typed_value_list, Value >;
 public:
  using leading_argument_list_kinds_t
    = case_detail::values_to_integral_constant_argument_list_kinds_t
      < typename partition::leading_t >;

  using trailing_argument_list_kinds_t
    = case_detail::values_to_integral_constant_argument_list_kinds_t
      < typename partition::trailing_t >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto ) provide_isolated_case
  ( case_detail::as_constant_t< Cases > self, Receiver&& rec )
  {
    // TODO(mattcalabrese) Use constant
    return receiver_traits::receive
    ( ARGOT_FORWARD( Receiver )( rec )
    , std::integral_constant< detail_argot::remove_cvref_t< decltype( Value ) >, Value >()
    );
  }
};

}  // namespace argot

#endif  // ARGOT_CASE_DETAIL_AS_CONSTANT_HPP_
