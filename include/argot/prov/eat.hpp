/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_EAT_HPP_
#define ARGOT_PROV_EAT_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/prov/nothing.hpp>

namespace argot::prov {

struct eat_fn
{
  template< class... P >
  [[nodiscard]]
  constexpr nothing_t operator ()( P&&... args ) const noexcept { return {}; }
} inline constexpr eat{};

template< class... P >
using result_of_eat = basic_result_of< eat_fn const&, P... >;

template< class... P >
using result_of_eat_t = basic_result_of_t< eat_fn const&, P... >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_EAT_HPP_
