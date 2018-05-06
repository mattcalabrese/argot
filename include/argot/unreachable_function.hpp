/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNREACHABLE_FUNCTION_HPP_
#define ARGOT_UNREACHABLE_FUNCTION_HPP_

#include <argot/detail/unreachable.hpp>

namespace argot {
namespace unreachable_function_detail {

struct unreachable_parameter_t {};

}  // namespace argot(::unreachable_function_detail)

template< class ReturnType >
struct unreachable_function_t
{
  // TODO(mattcalabrese)
  //   Possibly come up with a way to do the parameter trick without comma.
  [[noreturn]] constexpr ReturnType operator()
  ( unreachable_function_detail::unreachable_parameter_t
      = ( static_cast< void >( ARGOT_DETAIL_UNREACHABLE() )
        , unreachable_function_detail::unreachable_parameter_t{}
        )
  ) const noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template< class ReturnType >
unreachable_function_t< ReturnType > constexpr unreachable_function{};

}  // namespace argot

#endif  // ARGOT_UNREACHABLE_FUNCTION_HPP_
