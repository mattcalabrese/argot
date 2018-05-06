/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompalling
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_WHEN_ALL_HPP_
#define ARGOT_FUT_WHEN_ALL_HPP_

#include <tuple>

namespace argot {
namespace fut {

struct when_all_fn
{
  template< class... Futs >
  struct impl
  {
    ARGOT_ASSERT( Future< Futs >... );

    // TODO(mattcalabrese) Don't use std::tuple, use more efficient tuple.
    std::tuple< Futs... > futs;
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
} inline constexpr when_all{};

} // namespace argot(::fut)
} // namespace argot

#endif  // ARGOT_FUT_WHEN_ALL_HPP_
