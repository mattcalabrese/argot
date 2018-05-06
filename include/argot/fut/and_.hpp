/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompalling
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_AND_HPP_
#define ARGOT_FUT_AND_HPP_

#include <tuple>

namespace argot {
namespace fut {

struct and_fn
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
  [[nodiscard]] constexpr // TODO(mattcalabrese) SFINAE
  operator()( Futs&&... futs )
  {
    return impl< remove_cvref_t< Futs >... >
    { ARGOT_FORWARD( Futs )( futs )... };
  }
} inline constexpr and_{};

} // namespace argot(::fut)

template< class... Futs >
struct make_concept_map< fut::and_< Futs... > >
{
  using destructive_value_type_t
    = std::tuple< fut_traits::value_type_t< Futs >... >;

  template< class Fun >
  static constexpr auto
  destructive_then( fut::and_< Futs... >&& self, Fun&& fun )
  {
    return std::make_tuple
  }
};

} // namespace argot

#endif  // ARGOT_FUT_AND_HPP_
