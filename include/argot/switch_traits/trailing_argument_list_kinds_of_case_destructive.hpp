/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_TRAILING_ARGUMENT_LIST_KINDS_OF_CASE_DESTRUCTIVE_HPP
#define ARGOT_SWITCH_TRAITS_TRAILING_ARGUMENT_LIST_KINDS_OF_CASE_DESTRUCTIVE_HPP

#include <argot/concepts/switch_body_case.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot {
namespace switch_traits {

template< class Case, auto Value >
using trailing_argument_list_kinds_of_case_destructive_t
  = ARGOT_REQUIRES( SwitchBodyCase< Case, Value > )
    < typename access_raw_concept_map< SwitchBodyCase< Case, Value > >
      ::trailing_argument_list_kinds_t
    >;
/*
// TODO(mattcalabrese) Pass Value
template< class Case >
using trailing_argument_list_kinds_of_case_destructive
  = call_detail::lazy_expand
    < trailing_argument_list_kinds_of_case_destructive_t, Case >;
*/

// TODO(mattcalabrese) Pass Value
template< class Case, auto Value >
trailing_argument_list_kinds_of_case_destructive_t< Case, Value > constexpr
trailing_argument_list_kinds_of_case_destructive_v{};

}  // namespace argot(::switch_traits)

}  // namespace argot

#endif
// ARGOT_SWITCH_TRAITS_TRAILING_ARGUMENT_LIST_KINDS_OF_CASE_DESTRUCTIVE_HPP
