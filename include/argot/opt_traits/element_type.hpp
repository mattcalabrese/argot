/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPT_TRAITS_ELEMENT_TYPE_HPP_
#define ARGOT_OPT_TRAITS_ELEMENT_TYPE_HPP_

#include <argot/concepts/optional_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot::opt_traits {

template< class Opt >
using element_type_t
  = ARGOT_REQUIRES( OptionalLike< Opt > )
    < typename access_raw_concept_map< OptionalLike< Opt > >::element_type_t >;

template< class Opt >
using element_type = call_detail::lazy_expand< element_type, Opt >;

}  // namespace (argot::opt_traits)

#endif  // ARGOT_OPT_TRAITS_ELEMENT_TYPE_HPP_
