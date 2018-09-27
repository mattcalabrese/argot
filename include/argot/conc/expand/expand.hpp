/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_EXPAND_EXPAND_HPP_
#define ARGOT_CONC_EXPAND_EXPAND_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/concurrent_expandable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot::conc {

struct expand_fn
{
  template< class Exp
          , ARGOT_REQUIRES( ConcurrentExpandable< Exp&& > )()
          >
  [[nodiscard]] constexpr auto operator ()( Exp&& exp ) const
  {
    return access_raw_concept_map< ConcurrentExpandable< Exp&& > >
    ::expand( ARGOT_FORWARD( Exp )( exp ) );
  }
} inline constexpr expand{};

template< class Exp >
using result_of_expand = basic_result_of< expand_fn const&, Exp >;

template< class Exp >
using result_of_expand_t = basic_result_of_t< expand_fn const&, Exp >;

} // namespace (argot::conc)

#endif  // ARGOT_CONC_EXPAND_EXPAND_HPP_
