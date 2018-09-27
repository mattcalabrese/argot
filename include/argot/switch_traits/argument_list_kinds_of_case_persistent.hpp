/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_CASE_PERSISTENT_HPP_
#define ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_CASE_PERSISTENT_HPP_

#include <argot/impossible.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace switch_traits {
namespace argument_list_kinds_of_case_persistent_detail {

template< class Case, auto Value >
using explicit_argument_list_kinds_of_t
  = typename access_raw_concept_map< SwitchBodyCase< Case, Value > >
    ::argument_list_kinds_of_case_persistent_t;

template< class Case, auto Value >
struct explicit_argument_list_kinds_of
{
  using type = explicit_argument_list_kinds_of_t< Case, Value >;
};

template< class Case, auto Value, class = void >
struct explicit_argument_list_kinds_of_case_persistent_is_detected
  : std::false_type {};

template< class Case, auto Value >
struct explicit_argument_list_kinds_of_case_persistent_is_detected
< Case, Value, std::void_t< explicit_argument_list_kinds_of_t< Case, Value > > >
  : std::true_type {};

template< class Case, auto Value >
struct deduce_argument_list_kinds_of
{
 private:
  using detected_result_type
    = decltype
      ( access_raw_concept_map< PersistentSwitchBodyCase< Case, Value > >
        ::provide_isolated_case
        ( ARGOT_DECLVAL( Case const& )
        , ARGOT_DECLVAL( receiver::result_of_return_argument_list_kinds_t&& )
        )
      );
 public:
  using type
    = typename argot_detail::conditional
      < std::is_same_v< detected_result_type, impossible > >
      ::template apply
      < receiver_traits::argument_list_kinds_t<>
      , detected_result_type
      >;
};

} // namespace
   //   argot::case_traits(::argument_list_kinds_of_case_persistent_detail)

template< class Case, auto Value >
using argument_list_kinds_of_case_persistent_t
  = ARGOT_REQUIRES( PersistentSwitchBodyCase< Case, Value > )
    < typename argot_detail::conditional
      < argument_list_kinds_of_case_persistent_detail
        ::explicit_argument_list_kinds_of_case_persistent_is_detected
        < Case, Value >::value
      >::template apply
      < argument_list_kinds_of_case_persistent_detail
        ::explicit_argument_list_kinds_of< Case, Value >
      , argument_list_kinds_of_case_persistent_detail
        ::deduce_argument_list_kinds_of< Case, Value >
      >::type
    >;
/*
// TODO(mattcalabrese) Pass Value
template< class Case >
using argument_list_kinds_of_case_persistent
  = call_detail::lazy_expand< argument_list_kinds_of_case_persistent_t, Case >;
*/

// TODO(mattcalabrese) Pass Value
template< class Case, auto Value >
argument_list_kinds_of_case_persistent_t< Case, Value > constexpr
argument_list_kinds_of_case_persistent_v{};

} // namespace argot(::switch_traits)

} // namespace argot

#endif  // ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_CASE_PERSISTENT_HPP_
