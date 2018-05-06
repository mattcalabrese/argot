/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPERATORS_HPP_
#define ARGOT_OPERATORS_HPP_

#include <argot/concepts/concurrent_expandable.hpp>
#include <argot/concepts/expandable.hpp>
#include <argot/concepts/higher_order_expandable.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/bind_transform/operator_pipe.hpp>
#include <argot/prov/expand/expansion_operator.hpp>

// TODO(mattcalabrese) Move these to their own header.
namespace argot {

namespace concurrent_expansion_operator {

template< class ConcExp
        , ARGOT_REQUIRES( ConcurrentExpandable< ConcExp&& > )()
        >
[[nodiscard]] constexpr auto operator ~( ConcExp&& conc_exp )
{
  return access_raw_concept_map< ConcurrentExpandable< ConcExp&& > >
  ::concurrent_expand( ARGOT_FORWARD( ConcExp )( conc_exp ) );
}

} // namespace argot(::concurrent_expansion_operator)

namespace operators {

using concurrent_expansion_operator::operator ~;

} // namespace argot(::operators)
} // namespace argot

#endif  // ARGOT_OPERATORS_HPP_
