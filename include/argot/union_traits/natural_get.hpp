/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_NATURAL_GET_HPP_
#define ARGOT_UNION_TRAITS_NATURAL_GET_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::union_traits {

struct natural_get_t
{
  // TODO(mattcalabrese) Constrain that the index is convertible to index type
  // TODO(mattcalabrese) Cast to the index type when calling get
  template< class Union, class Index
          , ARGOT_REQUIRES
            ( UnionLike< detail_argot::remove_cvref_t< Union > > )
            ( StdIntegralConstant< Index > )
            ( UnionIndex< detail_argot::remove_cvref_t< Union >, Index::value > )
            ()
          >
  constexpr decltype( auto ) operator ()( Union&& variant_like, Index ) const
  {
    return access_raw_concept_map< UnionLike< detail_argot::remove_cvref_t< Union > > >
    ::template get< Index::value >( ARGOT_FORWARD( Union )( variant_like ) );
  }
} inline constexpr natural_get{};

template< class Union, class Index >
using result_of_natural_get
  = basic_result_of< natural_get_t const&, Union, Index >;

template< class Union, class Index >
using result_of_natural_get_t
  = basic_result_of_t< natural_get_t const&, Union, Index >;

}  // namespace (argot::variant_traits)

#endif  // ARGOT_UNION_TRAITS_NATURAL_GET_HPP_
