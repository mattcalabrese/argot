/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_EXPAND_EXPANSION_OPERATOR_HPP_
#define ARGOT_PROV_EXPAND_EXPANSION_OPERATOR_HPP_

#include <argot/concepts/expandable.hpp>
#include <argot/concepts/higher_order_expandable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot::expansion_operator {

template< class Exp
        , ARGOT_REQUIRES( Expandable< Exp&& > )()
        >
[[nodiscard]]
constexpr auto operator +( Exp&& exp )//=;
//<-
{
  return access_raw_concept_map< Expandable< Exp&& > >
  ::expand( ARGOT_FORWARD( Exp )( exp ) );
} //->

template< class Exp
        , ARGOT_REQUIRES( HigherOrderExpandable< Exp&& > )()
        >
[[nodiscard]]
constexpr auto operator ++( Exp&& exp )//=;
//<-
{
  using secondary_expandable_t
    = decltype( access_raw_concept_map< Expandable< Exp&& > >
                ::expand( ARGOT_FORWARD( Exp )( exp ) )
              );

  return access_raw_concept_map< Expandable< secondary_expandable_t&& > >
  ::expand( access_raw_concept_map< Expandable< Exp&& > >
            ::expand( ARGOT_FORWARD( Exp )( exp ) )
          );
} //->

} // namespace (argot::expansion_operator)

namespace argot::operators {

using expansion_operator::operator +;
using expansion_operator::operator ++;

} // namespace (argot::operators)

#endif  // ARGOT_PROV_EXPAND_EXPANSION_OPERATOR_HPP_
