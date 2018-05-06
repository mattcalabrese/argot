/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_FWD_HPP_
#define ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_FWD_HPP_

#include <cstddef>

namespace argot::prov::switch_detail {

enum class provision_kind;

template< std::size_t NumRemainingCases, provision_kind Kind >
struct switch_provision;

}  // namespace (argot::prov::switch_detail)

#endif  // ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_FWD_HPP_
