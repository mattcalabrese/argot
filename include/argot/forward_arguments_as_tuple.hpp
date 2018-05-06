/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FORWARD_ARGUMENTS_AS_TUPLE_HPP_
#define ARGOT_FORWARD_ARGUMENTS_AS_TUPLE_HPP_

#include <argot/forward.hpp>

#include <tuple>
#include <utility>

namespace argot {

struct forward_arguments_as_tuple_t
{
  template< class... P >
  constexpr std::tuple< P&&... > operator ()( P&&... args ) const
  {
    return std::forward_as_tuple( ARGOT_FORWARD( P )( args )... );
  }
} inline constexpr forward_arguments_as_tuple{};

}  // namespace argot

#endif  // ARGOT_FORWARD_ARGUMENTS_AS_TUPLE_HPP_
