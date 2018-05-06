#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif

using BOOST_PP_CAT( alternative_type, BOOST_PP_ITERATION() )
  = BOOST_PP_CAT( T, BOOST_PP_ITERATION() );

ARGOT_NO_UNIQUE_ADDRESS
call_detail::holder< BOOST_PP_CAT( T, BOOST_PP_ITERATION() ) >
BOOST_PP_CAT( alternative, BOOST_PP_ITERATION() );

#endif  // ARGOT_PREPROCESSING_MODE
