/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_HPP_
#define ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_HPP_

#include <argot/prov/switch_/detail/config.hpp>
#include <argot/prov/switch_/detail/switch_provision_0_cases.hpp>

// If generating switch_provision specializations via the preprocessor...
#if    defined( ARGOT_NO_PREPROCESSED_SWITCH )                                 \
    || defined( ARGOT_PREPROCESSING_MODE )

#include <argot/prov/switch_/detail/generate_switch_provision.hpp>

#else  // Otherwise, use specializations that were already preprocessed...

#include <argot/prov/switch_/detail/preprocessed_switch_provision.hpp>

#endif  // Determination of switch_provision specialization strategy

#endif  // ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_HPP_
