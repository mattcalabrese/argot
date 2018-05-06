/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_GET_HPP_
#define ARGOT_UNION_TRAITS_GET_HPP_

#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/union_traits/num_alternatives.hpp>

namespace argot::union_traits {

template< auto Index >
struct get_t
{
  template< class Union
          , ARGOT_REQUIRES( UnionLike< remove_cvref_t< Union > > )
                          ( UnionIndex< remove_cvref_t< Union >, Index > )
                          ()
          >
  constexpr decltype( auto ) operator ()( Union&& union_like ) const
  {
    return access_raw_concept_map< UnionLike< remove_cvref_t< Union > > >
    ::template get< Index >( ARGOT_FORWARD( Union )( union_like ) );
  }
};

template< auto Index, class Union >
using result_of_get_t
  = decltype
    ( ARGOT_DECLVAL( get_t< Index > const& )( ARGOT_DECLVAL( Union ) ) );

template< auto Index, class Union >
using result_of_get
  = call_detail::lazy_expand_get< result_of_get_t, Index, Union >;

template< auto Index >
get_t< Index > constexpr get{};

}  // namespace (argot::union_traits)

#endif  // ARGOT_UNION_TRAITS_GET_HPP_
