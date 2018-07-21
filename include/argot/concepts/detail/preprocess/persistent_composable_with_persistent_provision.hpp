/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 83 "../../concepts/persistent_composable_with_persistent_provision.hpp"
template< class Provider, class... Transformations >
struct PersistentComposableWithPersistentProvision { static bool constexpr argot_gen_detail_is_auto_concept_v = true; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< PersistentArgumentProvider< Provider > , TransparentRequirement < persistent_composable_with_persistent_provision_detail ::composable_wih_provision_requirements< Provider, Transformations... > > >::type; struct assertion : requirements::assertion {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
