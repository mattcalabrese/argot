/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_NATURAL_GET_HPP_
#define ARGOT_TUPLE_TRAITS_NATURAL_GET_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/tuple_index.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/tuple_traits/get.hpp>

namespace argot::tuple_traits {

struct natural_get_t
{
  // TODO(mattcalabrese) Constrain that the index is convertible to the index type
  // TODO(mattcalabrese) Cast to the index type when calling get
  template< class Tuple, class Index
          , ARGOT_REQUIRES
            ( TupleLike< detail_argot::remove_cvref_t< Tuple > > )
            ( StdIntegralConstant< Index > )
            ( TupleIndex< detail_argot::remove_cvref_t< Tuple >, Index::value > )
            ()
          >
  constexpr decltype( auto ) operator ()( Tuple&& tuple_like, Index ) const
  {
    return access_raw_concept_map< TupleLike< detail_argot::remove_cvref_t< Tuple > > >
    ::template get< Index::value >( ARGOT_FORWARD( Tuple )( tuple_like ) );
  }
} inline constexpr natural_get{};

template< class Tuple, class Index >
using result_of_natural_get
  = basic_result_of< natural_get_t const&, Tuple, Index >;

template< class Tuple, class Index >
using result_of_natural_get_t
  = basic_result_of_t< natural_get_t const&, Tuple, Index >;

}  // namespace (argot::tuple_traits)

#endif  // ARGOT_TUPLE_TRAITS_NATURAL_GET_HPP_
