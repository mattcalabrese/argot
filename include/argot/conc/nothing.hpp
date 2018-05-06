/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_NOTHING_HPP_
#define ARGOT_CONC_NOTHING_HPP_

#include <argot/conc/lift.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::conc {

inline constexpr auto nothing = conc::lift( prov::nothing );

using nothing_t = remove_cvref_t< decltype( nothing ) >;

}  // namespace (argot::conc)

#endif  // ARGOT_CONC_NOTHING_HPP_
