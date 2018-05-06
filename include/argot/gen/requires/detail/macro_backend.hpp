/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_REQUIRES_DETAIL_MACRO_BACKEND_HPP_
#define ARGOT_GEN_REQUIRES_DETAIL_MACRO_BACKEND_HPP_

#include <boost/preprocessor/control/iif.hpp>
#include <boost/vmd/is_empty.hpp>

#define ARGOT_DETAIL_END_TEMPLATE_PARAMETER_LIST_REQUIRES( ... )               \
result< int > = 0

#define ARGOT_DETAIL_REQUIRES_AND( ... )                                       \
and_< __VA_ARGS__ >::_::template ARGOT_RESULT_

#define ARGOT_DETAIL_REQUIRES_AND_( ... )                                      \
and_< __VA_ARGS__ >::_::template ARGOT_RESULT

#define ARGOT_RESULT( ... )                                                    \
BOOST_PP_IIF( BOOST_VMD_IS_EMPTY( __VA_ARGS__ )                                \
            , ARGOT_DETAIL_END_TEMPLATE_PARAMETER_LIST_REQUIRES                \
            , ARGOT_DETAIL_REQUIRES_AND                                        \
            )( __VA_ARGS__ )

#define ARGOT_RESULT_( ... )                                                   \
BOOST_PP_IIF( BOOST_VMD_IS_EMPTY( __VA_ARGS__ )                                \
            , ARGOT_DETAIL_END_TEMPLATE_PARAMETER_LIST_REQUIRES                \
            , ARGOT_DETAIL_REQUIRES_AND_                                       \
            )( __VA_ARGS__ )

#endif  // ARGOT_GEN_REQUIRES_DETAIL_MACRO_BACKEND_HPP_
