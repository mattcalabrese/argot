/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TRAITS_IS_HOMOGENEOUS_HPP_
#define ARGOT_REDUCER_TRAITS_IS_HOMOGENEOUS_HPP_

#include <argot/gen/make_concept_map.hpp>
#include <argot/concepts/return_value_reducer.hpp>

namespace argot {
namespace reducer_traits {

// TODO(mattcalabrese) Only enable if it's a return value reducer
template< class Reducer >
using is_homogeneous
  = typename access_raw_concept_map< ReturnValueReducer< Reducer > >
    ::is_homogeneous;

template< class Reducer >
bool constexpr is_homogeneous_v = is_homogeneous< Reducer >::value;

}  // namespace argot::reducer_traits
}  // namespace argot

#endif  // ARGOT_REDUCER_TRAITS_IS_HOMOGENEOUS_HPP_
