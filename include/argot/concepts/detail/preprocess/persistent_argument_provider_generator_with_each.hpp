/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 52 "../../concepts/persistent_argument_provider_generator_with_each.hpp"
template< class Invocable, class... ArgTypes >
struct PersistentArgumentProviderGeneratorWithEach { static bool constexpr argot_gen_detail_is_auto_concept_v = true; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< ArgumentTypes< ArgTypes >... , TransparentRequirement < persistent_argument_provider_generator_with_each_detail ::invocation_returns_an_argument_provider< Invocable, ArgTypes > >... >::type; struct assertion : requirements::assertion {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
