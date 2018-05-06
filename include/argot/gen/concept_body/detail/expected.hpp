/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_EXPECTED_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_EXPECTED_HPP_

#include <argot/gen/concept_body/detail/variadic_identity.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>

////////////////////////////////////////////////////////////////////////////////
// An "Expected" in this DSL represents the current parse state or failure    //
// information. Its structure is of the form:                                 //
//   kind(state)                                                              //
//                                                                            //
// where "kind" is the token "failure" or the token "success" (not quoted).   //
// If "kind" is "failure", then "state" is of the form:                       //
//   statement_number, error_string                                           //
//                                                                            //
// where "statement_number" is a 1-based index of the statement that is being //
// logically represented at the point at which the parse error occurs, and    //
// "error_string" is one or more adjacent string literals that describe the   //
// error.                                                                     //
//                                                                            //
// If "kind" is "success", then "state" is of the form:                       //
//   statement_number, (code_to_generate), (remaining_text)                   //
//                                                                            //
// where "statement_number" is a 1-based index of the statement that is       //
// currently being parsed, "code_to_generate" is C++ code to be output if the //
// overall parse is successful, and "remaining_text" is the the text that     //
// is still left to be parsed.                                                //
////////////////////////////////////////////////////////////////////////////////

#define ARGOT_GEN_DETAIL_EXPECTED_EXP( ... ) __VA_ARGS__

#define ARGOT_GEN_DETAIL_CONSTRUCT_EXPECTED_VALUE( ... ) value( __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_CONSTRUCT_UNEXPECTED( ... ) unexpected( __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_VISIT_EXPECTED( macro_root, expected )                \
BOOST_PP_IIF( ARGOT_GEN_DETAIL_EXPECTED_IS_VALUE( expected )                   \
            , BOOST_PP_CAT( macro_root, value )                                \
            , BOOST_PP_CAT( macro_root, unexpected )                           \
            )

#define ARGOT_GEN_DETAIL_EXPECTED_IS_VALUE( expected )                         \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_EXPECTED_IS_VALUE, expected )

#define ARGOT_GEN_DETAIL_EXPECTED_IS_UNEXPECTED( expected )                    \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_EXPECTED_IS_UNEXPECTED, expected )

#define ARGOT_GEN_DETAIL_GET_EXPECTED_VALUE( expected )                        \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_EAT_VALUE_, expected )

#define ARGOT_GEN_DETAIL_GET_EXPECTED_UNEXPECTED( expected )                   \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_EAT_UNEXPECTED_, expected )

#define ARGOT_GEN_DETAIL_EXPECTED_BIND( macro, expected )                      \
ARGOT_GEN_DETAIL_VISIT_EXPECTED                                                \
( ARGOT_GEN_DETAIL_EXPECTED_BIND_IMPL_, expected )( macro, expected )

#define ARGOT_GEN_DETAIL_EXPECTED_BIND_IMPL_unexpected( macro, expected )      \
ARGOT_GEN_DETAIL_VARIADIC_IDENTITY( expected )

#define ARGOT_GEN_DETAIL_EXPECTED_BIND_IMPL_value( macro, expected ) macro

#define ARGOT_GEN_DETAIL_EAT_VALUE_value
#define ARGOT_GEN_DETAIL_EAT_UNEXPECTED_unexpected

#define ARGOT_GEN_DETAIL_EXPECTED_IS_VALUEvalue( ... ) 1
#define ARGOT_GEN_DETAIL_EXPECTED_IS_VALUEunexpected( ... ) 0

#define ARGOT_GEN_DETAIL_EXPECTED_IS_UNEXPECTEDvalue( ... ) 0
#define ARGOT_GEN_DETAIL_EXPECTED_IS_UNEXPECTEDunexpected( ... ) 1

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_EXPECTED_HPP_
