/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STRUCT_DETAIL_CONFIG_HPP_
#define ARGOT_STRUCT_DETAIL_CONFIG_HPP_

#include <boost/preprocessor/config/limits.hpp>

// #define ARGOT_NO_PREPROCESSED_STRUCT 1

#ifdef ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS_IS_VALID
#error ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS_IS_VALID shall not be user-defined.
#else

// NOTE:
//   If ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS is defined by the user, make
//   certain that every translation unit in the build defines it the same.
#ifndef ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS
#define ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS 32
#endif  // ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS
#if ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS < 0
#error ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS must be greater than 0.
#elif ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS - 1 > BOOST_PP_LIMIT_ITERATION
#error ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS exceeds the Boost.PP iteration limit.
#else
#define ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS_IS_VALID 1
#endif  // The validity checks for ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS

#endif  // The check for ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS_IS_VALID definition

#endif  // ARGOT_STRUCT_DETAIL_CONFIG_HPP_
