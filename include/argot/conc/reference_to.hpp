/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_REFERENCE_TO_HPP_
#define ARGOT_CONC_REFERENCE_TO_HPP_

#include <argot/conc/conc_generator.hpp>
#include <argot/prov/reference_to.hpp>

namespace argot::conc {

inline constexpr auto reference_to = conc::conc_generator( prov::reference_to );

using reference_to_fn
  = conc::result_of_conc_generator_t< prov::reference_to_t >;

} // namespace (argot::conc)

#endif  // ARGOT_CONC_REFERENCE_TO_HPP_
