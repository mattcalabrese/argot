/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_WHEN_ANY_HPP_
#define ARGOT_FUT_WHEN_ANY_HPP_

#include <variant>

namespace argot::fut {

struct when_any_fn
{
  template< class... Futs >
  struct impl
  {
    ARGOT_ASSERT( Future< Futs > );
  };

  template< class... Futs
          , ARGOT_REQUIRES( Future< remove_cvref_t< Futs > > )
                          ( Sinkable< Futs&& > )
                          ()
          >
  constexpr // TODO(mattcalabrese) SFINAE
  operator()( Futs&&... futs )
  {

  }
} inline constexpr when_any{};

} // namespace argot::fut

#endif  // ARGOT_FUT_WHEN_ANY_HPP_
