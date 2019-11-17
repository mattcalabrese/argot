#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

// Make the includes appear directly so that rebuilds still take place when
// dependencies change.
#if 0
#include <argot/union_/detail/generation/union_constructor_generation.hpp>
#include <argot/union_/detail/generation/union_destroy_generation.hpp>
#include <argot/union_/detail/generation/union_emplace_generation.hpp>
#include <argot/union_/detail/generation/union_member_generation.hpp>
#endif

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_constructor_generation.hpp>       \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

  union
  {
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_member_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
  };

#undef ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES
