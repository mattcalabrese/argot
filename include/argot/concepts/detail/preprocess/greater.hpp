/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 34 "../../concepts/greater.hpp"
template< auto V, auto W >
struct Greater { using ArgotDetailConceptSpec = Greater ; static bool constexpr argot_gen_detail_is_auto_concept_v = false; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< >::type; struct assertion : ::argot::deduced_concept_assertion< ArgotDetailConceptSpec > {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
