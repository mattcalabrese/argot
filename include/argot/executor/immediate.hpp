/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_EXECUTOR_IMMEDIATE_HPP_
#define ARGOT_EXECUTOR_IMMEDIATE_HPP_

#include <argot/concepts/executor.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/make_concept_map.hpp>

namespace argot {
namespace executor {

struct immediate_t {} inline constexpr immediate;

}  // namespace argot(::executor)

template<>
struct make_concept_map< Executor< executor::immediate_t > >
{
  template< class Fun >
  static constexpr void execute( executor::immediate_t, Fun&& fun )
  {
    // TODO(mattcalabrese) Possibly only call r-value or const form.
    (void)ARGOT_FORWARD( Fun )( fun )();
  }
};

} // namespace argot

#endif  // ARGOT_EXECUTOR_IMMEDIATE_HPP_
