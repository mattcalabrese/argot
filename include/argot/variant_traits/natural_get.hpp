/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_NATURAL_GET_HPP_
#define ARGOT_VARIANT_TRAITS_NATURAL_GET_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/variant_index.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::variant_traits {

struct natural_get_t
{
  // TODO(mattcalabrese) Constrain that the index is convertible to the index type
  // TODO(mattcalabrese) Cast to the index type when calling get
  template< class Variant, class Index
          , ARGOT_REQUIRES
            ( VariantLike< remove_cvref_t< Variant > > )
            ( StdIntegralConstant< Index > )
            ( VariantIndex< remove_cvref_t< Variant >, Index::value > )
            ()
          >
  constexpr decltype( auto )
  operator ()( Variant&& variant_like, Index ) const
  {
    return access_raw_concept_map< UnionLike< remove_cvref_t< Variant > > >
    ::template get< Index::value >( ARGOT_FORWARD( Variant )( variant_like ) );
  }
} inline constexpr natural_get{};

template< class Variant, class Index >
using result_of_natural_get
  = basic_result_of< natural_get_t const&, Variant, Index >;

template< class Variant, class Index >
using result_of_natural_get_t
  = basic_result_of_t< natural_get_t const&, Variant, Index >;

}  // namespace (argot::variant_traits)

#endif  // ARGOT_VARIANT_TRAITS_NATURAL_GET_HPP_
