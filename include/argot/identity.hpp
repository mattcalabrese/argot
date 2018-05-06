/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_IDENTITY_HPP_
#define ARGOT_IDENTITY_HPP_

#include <argot/basic_result_of.hpp>

namespace argot {

// TODO(mattcalabrese) Probably should return by value
struct identity_t
{
  template< class P >
  constexpr P&& operator()( P&& arg ) const noexcept
  {
    return static_cast< P&& >( arg );
  }
} inline constexpr identity{};

template< class T >
using result_of_identity = basic_result_of< identity_t const&, T >;

template< class T >
using result_of_identity_t = basic_result_of_t< identity_t const&, T >;

}  // namespace argot

#endif  // ARGOT_IDENTITY_HPP_
