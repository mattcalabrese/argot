#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

if( state_traits::less_than< BOOST_PP_CAT( member_type, BOOST_PP_ITERATION() ) >
    ( lhs.BOOST_PP_CAT( member, BOOST_PP_ITERATION() )
    , rhs.BOOST_PP_CAT( member, BOOST_PP_ITERATION() )
    )
  )
  return true;

if( state_traits::less_than< BOOST_PP_CAT( member_type, BOOST_PP_ITERATION() ) >
    ( rhs.BOOST_PP_CAT( member, BOOST_PP_ITERATION() )
    , lhs.BOOST_PP_CAT( member, BOOST_PP_ITERATION() )
    )
  )
  return false;
