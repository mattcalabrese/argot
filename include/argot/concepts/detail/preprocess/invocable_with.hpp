/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 35 "../../concepts/invocable_with.hpp"
template< class Invocable, class... P >
struct InvocableWith { using ArgotDetailConceptSpec = InvocableWith ; static bool constexpr argot_gen_detail_is_auto_concept_v = false; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< >::type; struct assertion : ::argot::deduced_concept_assertion< ArgotDetailConceptSpec > {}; };
template< class Invocable, class... P >
struct make_concept_map
< InvocableWith< Invocable, P... >
, typename call_detail::detached_fast_enable_if
< argot_detail::is_invocable_v< Invocable&&, P&&... > >
::_::template apply<>
> {};
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
