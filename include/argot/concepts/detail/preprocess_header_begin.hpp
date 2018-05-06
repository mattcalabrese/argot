/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#ifdef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#pragma wave option( output: push )
#pragma wave option( line: push )
#pragma wave option( preserve: push )
#pragma wave option( preserve: 2 )
#pragma wave option( line: 0 )
#pragma wave option( output: ARGOT_CONCEPTS_DETAIL_OUTPUT_HEADER )
#include <argot/detail/copyright_and_license.hpp>
#pragma wave option( preserve: 0 )

#else

#undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME

#endif
