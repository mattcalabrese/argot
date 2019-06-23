/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_GET_HPP_
#define ARGOT_TUPLE_TRAITS_GET_HPP_

#include <argot/concepts/tuple_index.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::tuple_traits {

template< auto Index >
struct get_t
{
  template< class Tuple
          , ARGOT_REQUIRES( TupleLike< detail_argot::remove_cvref_t< Tuple > > )
                          ( TupleIndex< detail_argot::remove_cvref_t< Tuple >, Index > )
                          ()
          >
  constexpr decltype( auto ) operator ()( Tuple&& tup ) const
  {
    return access_raw_concept_map< TupleLike< detail_argot::remove_cvref_t< Tuple > > >
    ::template get< Index >( ARGOT_FORWARD( Tuple )( tup ) );
  }
};

template< auto Index, class Tuple >
using result_of_get_t
  = decltype
    ( ARGOT_DECLVAL( get_t< Index > const& )( ARGOT_DECLVAL( Tuple ) ) );

template< auto Index, class Tuple >
using result_of_get
  = call_detail::lazy_expand_get< result_of_get_t, Index, Tuple >;

template< auto Index >
get_t< Index > constexpr get{};

}  // namespace (argot::tuple_traits)

#endif  // ARGOT_TUPLE_TRAITS_GET_HPP_
