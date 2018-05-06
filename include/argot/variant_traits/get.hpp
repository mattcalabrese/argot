/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_GET_HPP_
#define ARGOT_VARIANT_TRAITS_GET_HPP_

#include <argot/concepts/union_like.hpp>
#include <argot/concepts/variant_index.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/remove_cvref.hpp>

namespace argot {
namespace variant_traits {

template< auto Index >
struct get_t
{
  template< class Variant
          , ARGOT_REQUIRES( VariantLike< remove_cvref_t< Variant > > )
                          ( VariantIndex< remove_cvref_t< Variant >, Index > )
                          ()
          >
  constexpr decltype( auto ) operator ()( Variant&& var ) const
  {
    return access_raw_concept_map< UnionLike< remove_cvref_t< Variant > > >
    ::template get< Index >( ARGOT_FORWARD( Variant )( var ) );
  }
};

template< auto Index, class Variant >
using result_of_get_t
  = decltype
    ( ARGOT_DECLVAL( get_t< Index > const& )( ARGOT_DECLVAL( Variant ) ) );

template< auto Index, class Union >
using result_of_get
  = call_detail::lazy_expand_get< result_of_get_t, Index, Union >;

template< auto Index >
get_t< Index > constexpr get{};

}  // namespace argot::variant_traits
}  // namespace argot

#endif  // ARGOT_VARIANT_TRAITS_GET_HPP_
