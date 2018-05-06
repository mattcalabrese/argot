/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CASE_DISJOINT_CASE_SET_HPP_
#define ARGOT_CASE_DISJOINT_CASE_SET_HPP_

#include <argot/case/detail/cases_base.hpp>
#include <argot/concepts/case_labels.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/value_list.hpp>

namespace argot {

template< auto Value >
struct disjoint_case_set_t
  : private case_detail::cases_base< disjoint_case_set_t< Values... > >
{
  using base_t = case_detail::cases_base< disjoint_case_set_t< Values... > >;
 public:
   using base_t::as_constant;
   using base_t::as_is;
   using base_t::operator();
   using base_t::unreachable;
};

// TODO(mattcalabrese) Constrain to no duplicate cases
template< auto... Values >
ARGOT_REQUIRES( SwitchCondition< decltype( Values ) >... )
disjoint_case_set_t< Values... > constexpr disjoint_case_set{};

// TODO(mattcalabrese) Result of calculators

template< auto... Values >
struct make_concept_map< disjoint_case_set_t< Values > >
{
  using case_values_t = value_list_t< Values... >;
};
}  // namespace argot

#endif  // ARGOT_CASE_DISJOINT_CASE_SET_HPP_
