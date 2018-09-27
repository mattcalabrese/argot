/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 54 "../../concepts/persistent_invocable_object_with_persistent_provision.hpp"
template< class Invocable, class... Providers >
struct PersistentInvocableObjectWithPersistentProvision { static bool constexpr argot_gen_detail_is_auto_concept_v = true; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< InvocableObjectWithProvision< Invocable, Providers... > , TransparentRequirement < detail_persistent_invocable_object_with_persistent_provision::requirements < Invocable, Providers... > > >::type; struct assertion : requirements::assertion {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
