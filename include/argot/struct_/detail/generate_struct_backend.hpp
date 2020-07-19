/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STRUCT_DETAIL_GENERATE_STRUCT_BACKEND_HPP_
#define ARGOT_STRUCT_DETAIL_GENERATE_STRUCT_BACKEND_HPP_

#include <argot/detail/forward.hpp>
#include <argot/detail/if_.hpp>
#include <argot/detail/variadic_range.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/struct_/detail/config.hpp>
#include <argot/struct_/detail/struct_backend_fwd.hpp>
#include <argot/void_.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <cstddef>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace argot {

template< class... T >
class struct_;

namespace detail_struct {

// Make the include appear directly so that rebuilds still take place when
// dependencies change.
#if 0
#include <argot/struct_/detail/generation/struct_generation.hpp>
#endif

#define BOOST_PP_ITERATION_PARAMS_1                                            \
( 3, ( 0, ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS                               \
     , <argot/struct_/detail/generation/struct_generation.hpp>                 \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

template< class... T >
using form_struct_tree = detail_argot::form_tree< struct_impl, T... >;

template< class... T >
using form_pure_struct = struct_< contained< T >... >;

} // namespace argot(::detail_struct)
} // namespace argot

#endif  // ARGOT_STRUCT_DETAIL_GENERATE_STRUCT_BACKEND_HPP_
