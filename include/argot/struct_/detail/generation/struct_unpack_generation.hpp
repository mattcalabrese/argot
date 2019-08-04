#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

, static_cast
  < call_detail::give_qualifiers_to_t
    < Self&&
    , typename access_raw_concept_map
      < TupleLike< detail_argot::remove_cvref_t< Self > > >
      ::template element_type_t< BOOST_PP_ITERATION() >
    >
  >
  ( self.elements.BOOST_PP_CAT( member, BOOST_PP_ITERATION() ) )
