/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_DETAIL_PREPROCESSED_SWITCH_PROVISION_HPP_
#define ARGOT_PROV_SWITCH_DETAIL_PREPROCESSED_SWITCH_PROVISION_HPP_

#include <argot/prov/switch_/detail/config.hpp>

#ifdef ARGOT_NO_PREPROCESSED_SWITCH
#error Unexpected inclusion of preprocessed switch forms.
#else  // Otherwise, all is fine. Proceed to include the specializations.

#include <argot/concepts/switch_body_default.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/prov/switch_/detail/config.hpp>
#include <argot/prov/switch_/detail/switch_impl_fwd.hpp>
#include <argot/prov/switch_/detail/switch_provision_base.hpp>
#include <argot/prov/switch_/detail/switch_provision_fwd.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_persistent.hpp>
#include <argot/switch_traits/case_value_for_type_at.hpp>
#include <argot/switch_traits/destructive_provide_case.hpp>
#include <argot/switch_traits/destructive_provide_default.hpp>
#include <argot/switch_traits/num_cases.hpp>
#include <argot/switch_traits/persistent_provide_case.hpp>
#include <argot/switch_traits/persistent_provide_default.hpp>
#include <argot/unreachable_function.hpp>

#include <cstddef>

namespace argot::prov::switch_detail {

// TODO(mattcalabrese) Binary search the values.
#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES <= 2
#include <argot/prov/switch_/detail/preprocessed/switch_provision_default_definition_2_.hpp>
#include <argot/prov/switch_/detail/preprocessed/switch_provision_2_.hpp>
#elif ARGOT_MAX_PREPROCESSED_SWITCH_CASES <= 4
#include <argot/prov/switch_/detail/preprocessed/switch_provision_default_definition_4_.hpp>
#include <argot/prov/switch_/detail/preprocessed/switch_provision_4_.hpp>
#elif ARGOT_MAX_PREPROCESSED_SWITCH_CASES <= 8
#include <argot/prov/switch_/detail/preprocessed/switch_provision_default_definition_8_.hpp>
#include <argot/prov/switch_/detail/preprocessed/switch_provision_8_.hpp>
#elif ARGOT_MAX_PREPROCESSED_SWITCH_CASES <= 16
#include <argot/prov/switch_/detail/preprocessed/switch_provision_default_definition_16_.hpp>
#include <argot/prov/switch_/detail/preprocessed/switch_provision_16_.hpp>
#else
#error ARGOT_MAX_PREPROCESSED_SWITCH_CASES too large for preprocessed forms.
#endif

}  // namespace (argot::prov::switch_detail)

#endif  // End of check that usage of preprocessed switching is specified.

#endif  // ARGOT_PROV_SWITCH_DETAIL_PREPROCESSED_SWITCH_PROVISION_HPP_
