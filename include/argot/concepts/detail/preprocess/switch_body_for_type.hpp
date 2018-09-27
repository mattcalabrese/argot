/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 82 "../../concepts/switch_body_for_type.hpp"
template< class Body, class ValueType >
struct SwitchBodyForType { static bool constexpr argot_gen_detail_is_auto_concept_v = true; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< SwitchBody< Body > , SwitchCondition< ValueType > 
, TransparentRequirement < switch_body_for_type_detail::switch_body_for_type_case_requirements < Body, ValueType > > , TransparentRequirement < switch_body_for_type_detail::switch_body_for_type_default_requirements < Body, ValueType > > >::type; struct assertion : requirements::assertion {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
