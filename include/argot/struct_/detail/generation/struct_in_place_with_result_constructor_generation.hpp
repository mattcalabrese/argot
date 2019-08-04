#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

#define ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX                                  \
BOOST_PP_ITERATION()

#define ARGOT_DETAIL_STRUCT_CURR_MEMBER_TYPE                                   \
BOOST_PP_CAT( T, ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX )

#define ARGOT_DETAIL_STRUCT_CURR_FUN_TYPE                                      \
BOOST_PP_CAT( Fun, ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX )

#define ARGOT_DETAIL_STRUCT_CURR_MEMBER                                        \
BOOST_PP_CAT( member, ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX )

#define ARGOT_DETAIL_STRUCT_CURR_FUN                                           \
BOOST_PP_CAT( fun, ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX )

BOOST_PP_COMMA_IF( BOOST_PP_ITERATION() )
ARGOT_DETAIL_STRUCT_CURR_MEMBER
( argot::void_to_regular_void_invoke
  ( ARGOT_FORWARD( ARGOT_DETAIL_STRUCT_CURR_FUN_TYPE )
    ( ARGOT_DETAIL_STRUCT_CURR_FUN )
  )
)

#undef ARGOT_DETAIL_STRUCT_CURR_FUN
#undef ARGOT_DETAIL_STRUCT_CURR_MEMBER
#undef ARGOT_DETAIL_STRUCT_CURR_FUN_TYPE
#undef ARGOT_DETAIL_STRUCT_CURR_MEMBER_TYPE
#undef ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX
