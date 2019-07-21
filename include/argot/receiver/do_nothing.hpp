/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_DO_NOTHING_HPP_
#define ARGOT_RECEIVER_DO_NOTHING_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/gen/make_concept_map.hpp>

namespace argot::receiver {

struct do_nothing_fn
{
  struct impl {};
  constexpr impl operator()() const noexcept { return {}; }
} inline constexpr do_nothing{};

} // namespace (argot::receiver)

namespace argot {

template<>
struct make_concept_map< ArgumentReceiver< receiver::do_nothing_fn::impl > >
{
  template< class LeadingArgLists, class TrailingArgLists, class... P >
  static constexpr void
  receive_branch
  ( receiver::do_nothing_fn::impl
  , LeadingArgLists, TrailingArgLists, P&&...
  ) noexcept
  {
  }
};

} // namespace argot

#endif // ARGOT_RECEIVER_DO_NOTHING_HPP_
