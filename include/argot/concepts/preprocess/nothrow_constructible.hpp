/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 34 "../../concepts/nothrow_constructible.hpp"
template< class T, class... P >
struct NothrowConstructible { using ArgotDetailConceptSpec = NothrowConstructible ; static bool constexpr argot_gen_detail_is_auto_concept_v = false; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< Constructible< T, P... > >::type; struct assertion : ::argot::deduced_concept_assertion< ArgotDetailConceptSpec > {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
