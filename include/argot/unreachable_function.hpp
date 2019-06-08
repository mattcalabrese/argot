/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNREACHABLE_FUNCTION_HPP_
#define ARGOT_UNREACHABLE_FUNCTION_HPP_

#include <argot/detail/unreachable.hpp>

#include <boost/config.hpp>

namespace argot {

template< class ReturnType >
struct unreachable_function_fn
{
  [[noreturn]] BOOST_FORCEINLINE constexpr ReturnType operator()() const
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template< class ReturnType >
unreachable_function_fn< ReturnType > constexpr unreachable_function{};

}  // namespace argot

#endif  // ARGOT_UNREACHABLE_FUNCTION_HPP_
