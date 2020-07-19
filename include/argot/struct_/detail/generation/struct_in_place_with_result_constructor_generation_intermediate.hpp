#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2019, 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

#define ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX                                  \
BOOST_PP_ITERATION()

#define ARGOT_DETAIL_STRUCT_CURR_MEMBER_TYPE                                   \
BOOST_PP_CAT( T, ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX )

#define ARGOT_DETAIL_STRUCT_CURR_MEMBER                                        \
BOOST_PP_CAT( member, ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX )

BOOST_PP_COMMA_IF( BOOST_PP_ITERATION() )
ARGOT_DETAIL_STRUCT_CURR_MEMBER
( detail_argot::variadic_sized_range_run
  <   ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX
    * detail_argot::amount_at_depth( NextDepth )
  , ARGOT_DETAIL_STRUCT_CURR_MEMBER_TYPE
    ::template num_leaves< NextDepth >::value
  >( make_ith_member_fun_fn< NextDepth, ARGOT_DETAIL_STRUCT_CURR_MEMBER_TYPE >()
   , ARGOT_FORWARD( Funs )( funs )...
   )
)

#undef ARGOT_DETAIL_STRUCT_CURR_MEMBER
#undef ARGOT_DETAIL_STRUCT_CURR_MEMBER_TYPE
#undef ARGOT_DETAIL_STRUCT_CURR_MEMBER_INDEX
