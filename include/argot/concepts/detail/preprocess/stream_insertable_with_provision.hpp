/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 53 "../../concepts/stream_insertable_with_provision.hpp"
template< class Stream, class Provider >
struct StreamInsertableWithProvision { static bool constexpr argot_gen_detail_is_auto_concept_v = true; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< ArgumentProvider< detail_argot::remove_cvref_t< Provider > > , TransparentRequirement < detail_stream_insertable_with_provision ::stream_insertable_with_provision_requirements < Stream, Provider > > >::type; struct assertion : requirements::assertion {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
