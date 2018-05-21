/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_DETAIL_GENERATE_UNION_BACKEND_HPP_
#define ARGOT_UNION_DETAIL_GENERATE_UNION_BACKEND_HPP_

#include <argot/detail/holder.hpp>
#include <argot/forward.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/union_/detail/config.hpp>
#include <argot/union_/detail/union_backend_fwd.hpp>
#include <argot/void_.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace argot::detail_union {

// Make the include appear directly so that rebuilds still take place when
// dependencies change.
#if 0
#include <argot/union_/detail/generation/union_generation.hpp>
#endif

#define BOOST_PP_ITERATION_PARAMS_1                                            \
( 3, ( 1, ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES                            \
     , <argot/union_/detail/generation/union_generation.hpp>                   \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

}  // namespace (argot::detail_union)

#endif  // ARGOT_UNION_DETAIL_GENERATE_UNION_BACKEND_HPP_
