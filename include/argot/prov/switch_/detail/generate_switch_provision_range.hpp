/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PREPROCESSING_MODE
#error This file should only be included when preprocessing specializations.
#else

#include <argot/detail/hash.hpp>
#include <argot/forward.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define ARGOT_PROV_SWITCH_DETAIL_HEADER_MIDNAME                                \
BOOST_PP_CAT                                                                   \
( BOOST_PP_CAT                                                                 \
  ( ot/prov/switch_/detail/preprocessed/switch_provision_                      \
  , BOOST_PP_DEC                                                               \
    ( BOOST_PP_TUPLE_ELEM                                                      \
      ( 0, ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE )            \
    )                                                                          \
  )                                                                            \
, _.h                                                                          \
)

#define ARGOT_PROV_SWITCH_DETAIL_OUTPUT_PATH                                   \
BOOST_PP_STRINGIZE                                                             \
( BOOST_PP_CAT                                                                 \
  ( BOOST_PP_CAT                                                               \
    ( preprocessed/switch_provision_                                           \
    , BOOST_PP_TUPLE_ELEM                                                      \
      ( 1, ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE )            \
    )                                                                          \
  , _.hpp                                                                      \
  )                                                                            \
)

// TODO(mattcalabrese) Don't put the hash anywhere except the top level
#define ARGOT_PROV_SWITCH_DETAIL_INCLUDE                                       \
ARGOT_DETAIL_HASH BOOST_PP_CAT                                                 \
( BOOST_PP_CAT                                                                 \
  ( include <arg                                                               \
  , ARGOT_PROV_SWITCH_DETAIL_HEADER_MIDNAME                                    \
  )                                                                            \
, pp>                                                                          \
)

#pragma wave option( preserve: push )
#pragma wave option( preserve: 2 )
#pragma wave option( output: push )
#pragma wave option( output: ARGOT_PROV_SWITCH_DETAIL_OUTPUT_PATH )
#include <argot/detail/copyright_and_license.hpp>
#if BOOST_PP_TUPLE_ELEM                                                        \
    ( 0, ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE ) > 1
ARGOT_PROV_SWITCH_DETAIL_INCLUDE
#endif

#define BOOST_PP_ITERATION_PARAMS_1                                            \
( 3, ( BOOST_PP_TUPLE_ELEM                                                     \
       ( 0, ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE )           \
     , BOOST_PP_TUPLE_ELEM                                                     \
       ( 1, ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE )           \
     , <argot/prov/switch_/detail/generation/switch_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

#pragma wave option( output: pop )
#pragma wave option( preserve: pop )

#undef ARGOT_PROV_SWITCH_DETAIL_INCLUDE
#undef ARGOT_PROV_SWITCH_DETAIL_OUTPUT_PATH
#undef ARGOT_PROV_SWITCH_DETAIL_HEADER_MIDNAME

#undef ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE

#endif  // ARGOT_PREPROCESSING_MODE
