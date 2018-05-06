/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_DETAIL_CONFIG_HPP_
#define ARGOT_PROV_SWITCH_DETAIL_CONFIG_HPP_

#include <boost/preprocessor/config/limits.hpp>

// #define ARGOT_NO_PREPROCESSED_SWITCH 1

#ifdef ARGOT_MAX_PREPROCESSED_SWITCH_CASES_IS_VALID
#error ARGOT_MAX_PREPROCESSED_SWITCH_CASES_IS_VALID shall not be user-defined.
#else

// NOTE:
//   If ARGOT_MAX_PREPROCESSED_SWITCH_CASES is defined by the user, make
//   certain that every translation unit in the build defines it the same.
#ifndef ARGOT_MAX_PREPROCESSED_SWITCH_CASES
#define ARGOT_MAX_PREPROCESSED_SWITCH_CASES 16
#endif  // BOOST_CALL_END_SWITCH_CASE_COUNT
#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES < 0
#error ARGOT_MAX_PREPROCESSED_SWITCH_CASES must be greater than 0.
#elif ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1 > BOOST_PP_LIMIT_ITERATION
#error ARGOT_MAX_PREPROCESSED_SWITCH_CASES exceeds the Boost.PP iteration limit.
#else
#define ARGOT_MAX_PREPROCESSED_SWITCH_CASES_IS_VALID 1
#endif  // The validity checks for ARGOT_MAX_PREPROCESSED_SWITCH_CASES

#endif  // The check for ARGOT_MAX_PREPROCESSED_SWITCH_CASES_IS_VALID definition

#endif  // ARGOT_PROV_SWITCH_DETAIL_CONFIG_HPP_
