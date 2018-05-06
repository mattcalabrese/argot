/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUTURE_TRAITS_VALUE_TYPE_HPP_
#define ARGOT_FUTURE_TRAITS_VALUE_TYPE_HPP_

#include <argot/concepts/future.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/lazy_expand.hpp>

#include <utility>

namespace argot::fut_traits {

template< class Fut >
using value_type_t
  = ARGOT_REQUIRES( Future< Fut > )
    < typename access_raw_concept_map< Future< Fut > >::value_type_t >;

template< class Fut >
using value_type = lazy_expand< value_type_t, Fut >;

} // namespace argot::fut_traits

#endif  // ARGOT_FUTURE_TRAITS_VALUE_TYPE_HPP_
