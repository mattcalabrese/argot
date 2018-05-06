/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_DETAIL_CONCEPTS_PREPROCESSING_HELPERS_HPP_
#define ARGOT_CONCEPTS_DETAIL_CONCEPTS_PREPROCESSING_HELPERS_HPP_

#include <argot/detail/hash.hpp>

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#ifdef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#define ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER                              \
<argot/concepts/detail/preprocess_concepts_error.hpp>

#define ARGOT_CONCEPTS_DETAIL_INPUT_HEADER                                     \
BOOST_PP_STRINGIZE                                                             \
( BOOST_PP_CAT                                                                 \
  ( BOOST_PP_CAT( ../../concept                                                \
                , ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()              \
                )                                                              \
  , pp                                                                         \
  )                                                                            \
)

#define ARGOT_CONCEPTS_DETAIL_OUTPUT_HEADER                                    \
BOOST_PP_STRINGIZE                                                             \
( BOOST_PP_CAT                                                                 \
  ( BOOST_PP_CAT( ../preproces                                                 \
                , ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()              \
                )                                                              \
  , pp                                                                         \
  )                                                                            \
)

#define ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( line_num )                \
ARGOT_DETAIL_HASH line line_num ARGOT_CONCEPTS_DETAIL_INPUT_HEADER

#else

// TODO(mattcalabrese)
//   Produce explicit error when the file doesn't exist by way of including a
//   backup file with a static_assert that describes which file is missing.

#ifndef ARGOT_NO_PREPROCESSED_CONCEPTS
#define ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER 1
#endif

#define ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER                              \
BOOST_PP_CAT                                                                   \
( BOOST_PP_CAT( <argot/concepts/preproces                                      \
              , ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                \
              )                                                                \
, pp>                                                                          \
)                                                                              \

#define ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( dummy_param )

#endif

#endif  // ARGOT_CONCEPTS_DETAIL_CONCEPTS_PREPROCESSING_HELPERS_HPP_
