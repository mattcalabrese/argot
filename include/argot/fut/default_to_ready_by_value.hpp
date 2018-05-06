/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_DEFAULT_TO_READY_BY_VALUE_HPP_
#define ARGOT_FUT_DEFAULT_TO_READY_BY_VALUE_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/fut/group.hpp>
#include <argot/gen/and.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::fut {

struct default_to_ready_by_value_fn
{
 private:
  // TODO(mattcalabrese) Minimize template instantiations using cast tricks.
  template
  < class... P
  , ARGOT_REQUIRES
    ( Not< ArgumentProvider< remove_cvref_t< P > > > )  // TODO(mattcalabrese) Produce warning
    ( Sinkable< P&& > )
    ()
  >
  constexpr auto operator()( P&&... args ) const
  {

  }

} inline constexpr default_to_ready_by_value{};

} // namespace (argot::fut)

#endif  // ARGOT_FUT_DEFAULT_TO_READY_BY_VALUE_HPP_
