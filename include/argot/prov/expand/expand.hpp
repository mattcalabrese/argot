/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_EXPAND_EXPAND_HPP_
#define ARGOT_PROV_EXPAND_EXPAND_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/expandable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot::prov {

struct expand_fn
{
  template< class Exp
          , ARGOT_REQUIRES( Expandable< Exp&& > )()
          >
  [[nodiscard]] constexpr auto operator ()( Exp&& exp ) const
  {
    return access_raw_concept_map< Expandable< Exp&& > >
    ::expand( ARGOT_FORWARD( Exp )( exp ) );
  }
} inline constexpr expand{};

template< class Exp >
using result_of_expand = basic_result_of< expand_fn const&, Exp >;

template< class Exp >
using result_of_expand_t = basic_result_of_t< expand_fn const&, Exp >;

} // namespace (argot::prov)

#endif  // ARGOT_PROV_EXPAND_EXPAND_HPP_
