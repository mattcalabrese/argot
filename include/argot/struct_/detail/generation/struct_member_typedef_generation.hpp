#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

using BOOST_PP_CAT( member_type, BOOST_PP_ITERATION() )
  = void_to_regular_void_t< BOOST_PP_CAT( T, BOOST_PP_ITERATION() ) >;
