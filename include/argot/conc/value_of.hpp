/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_VALUE_OF_HPP_
#define ARGOT_CONC_VALUE_OF_HPP_

#include <argot/conc/conc_generator.hpp>
#include <argot/prov/value_of.hpp>

namespace argot::conc {

inline constexpr auto value_of = conc::conc_generator( prov::value_of );

using value_of_fn = conc::result_of_conc_generator_t< prov::value_of_fn >;

} // namespace (argot::conc)

#endif  // ARGOT_CONC_VALUE_OF_HPP_
