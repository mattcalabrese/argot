/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_EXPAND_EXPANSION_OPERATOR_HPP_
#define ARGOT_CONC_EXPAND_EXPANSION_OPERATOR_HPP_

#include <argot/concepts/concurrent_expandable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot {
namespace concurrent_expansion_operator {

template< class Exp
        , ARGOT_REQUIRES( ConcurrentExpandable< Exp&& > )()
        >
[[nodiscard]] constexpr auto operator ~( Exp&& exp )
{
  return access_raw_concept_map< ConcurrentExpandable< Exp&& > >
  ::expand( ARGOT_FORWARD( Exp )( exp ) );
}

} // namespace argot(::concurrent_expansion_operator)

namespace operators {

using concurrent_expansion_operator::operator ~;

} // namespace argot(::operators)

} // namespace argot

#endif  // ARGOT_CONC_EXPAND_EXPANSION_OPERATOR_HPP_
