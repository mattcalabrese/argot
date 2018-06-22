/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPT_TRAITS_NIL_ELEMENT_TYPE_HPP_
#define ARGOT_OPT_TRAITS_NIL_ELEMENT_TYPE_HPP_

#include <argot/detail/detection.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/opt_traits/element_type.hpp>
#include <argot/opt_traits/nil.hpp>

namespace argot::opt_traits {

template< class T >
using nil_element_type_t
  = ARGOT_REQUIRES( OptionalLike< T > )
    < nil< element_type_t< T > > >;

template< class T >
using nil_element_type = call_detail::lazy_expand< nil_element_type_t, T >;

}  // namespace (argot::opt_traits)

#endif  // ARGOT_OPT_TRAITS_NIL_ELEMENT_TYPE_HPP_
