/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CASE_CASE_HPP_
#define ARGOT_CASE_CASE_HPP_

#include <argot/case/detail/cases_base.hpp>
#include <argot/concepts/case_labels.hpp>
#include <argot/concepts/switch_condition.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/value_list.hpp>

namespace argot {

template< auto Value >
struct case_t
  : private case_detail::cases_base< case_t< Value > >
{
  ARGOT_CONCEPT_ASSERT( SwitchCondition< decltype( Value ) > );

  using base_t = case_detail::cases_base< case_t< Value > >;
 public:
   using base_t::as_constant;
   using base_t::as_is;
   using base_t::operator();
   using base_t::unreachable;
};

template< auto Value >
ARGOT_REQUIRES( SwitchCondition< decltype( Value ) > )
< case_t< Value > > constexpr case_{};

// TODO(mattcalabrese) Result of calculators

template< auto Value >
struct make_concept_map
< CaseLabels< case_t< Value > >
, ARGOT_REQUIRES( SwitchCondition< decltype( Value ) > )<>
>
{
  using case_values_t = value_list_t< Value >;

  template< template< auto... > class Template >
  using expand_case_values_t = Template< Value >;
};

} // namespace argot

#endif  // ARGOT_CASE_CASE_HPP_
