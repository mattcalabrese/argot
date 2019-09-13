/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_MAX_ARGUMENT_LIST_LENGTH_HPP_
#define ARGOT_DETAIL_MAX_ARGUMENT_LIST_LENGTH_HPP_

#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <algorithm>
#include <cstddef>

namespace argot::detail_argot {

template< class Kinds >
inline ARGOT_REQUIRES( ArgumentListKinds< Kinds > )
< std::size_t > constexpr max_argument_list_length_v;

template< class... Lists >
inline std::size_t constexpr max_argument_list_length_v
< receiver_traits::argument_list_kinds_t< Lists... > >
  = std::max( { Lists::length_v... } );

} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_MAX_ARGUMENT_LIST_LENGTH_HPP_
