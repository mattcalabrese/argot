/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CASE_DETAIL_DISJOINT_CASES_BASE_HPP_
#define ARGOT_CASE_DETAIL_DISJOINT_CASES_BASE_HPP_

#include <argot/case/detail/as_constant.hpp>
#include <argot/case/detail/disjoint_as_is.hpp>
#include <argot/case/detail/disjoint_provided.hpp>
#include <argot/case/detail/unreachable_case.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::case_detail {

template< class ChildType >
struct disjoint_cases_base
{
  static constexpr unreachable_case_t< ChildType > unreachable{};

  static constexpr as_constant_t< ChildType > as_constant{};

  static constexpr disjoint_as_is< ChildType > as_is{};

  template< class Provider >
  constexpr
  ARGOT_REQUIRES( ArgumentProvider< detail_argot::remove_cvref_t< Provider > > )
                ( Sinkable< Provider&& > )
  < disjoint_provided_t< detail_argot::remove_cvref_t< Provider > > >
  operator()( Provider&& provider ) const
  {
    return { call_detail::forward_and_sink< Provider >( provider ) };
  }
};

} // namespace (argot::case_detail)

#endif  // ARGOT_CASE_DETAIL_DISJOINT_CASES_BASE_HPP_
