/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ACCESS_VARIANT_HPP_
#define ARGOT_PROV_ACCESS_VARIANT_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/default_.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/union_index.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/union_traits/natural_get.hpp>
#include <argot/variant_traits/index_type.hpp>

#include <type_traits>

namespace argot::prov {

struct access_variant_fn
{
  template< class Variant, class Index, class Def = default_unreachable_t
          , ARGOT_REQUIRES
            ( VariantLike< detail_argot::remove_cvref_t< Variant > > )
            ( Not< VolatileObject< std::remove_reference_t< Variant > > > )
            ( ConvertibleToTypeOrConstant
              < Index
              , variant_traits::index_type_t< detail_argot::remove_cvref_t< Variant > >
              >
            )
            ( Default< Def > )
            ()
          >
  [[nodiscard]] constexpr auto operator ()
  ( Variant&& variant_to_access, Index&& index, Def def = {} ) const
  {
    return prov::lift_call
    ( union_traits::natural_get
    , prov::reference_to( ARGOT_FORWARD( Variant )( variant_to_access ) )
    , prov::union_index< detail_argot::remove_cvref_t< Variant > >
      ( ARGOT_FORWARD( Index )( index ), ARGOT_MOVE( def ) )
    );
  }
} inline constexpr access_variant{};

template< class Variant, class Index, class Def = default_unreachable_t >
using result_of_access_variant
  = basic_result_of< access_variant_fn const&, Variant, Index, Def >;

template< class Variant, class Index, class Def = default_unreachable_t >
using result_of_access_variant_t
  = basic_result_of_t< access_variant_fn const&, Variant, Index, Def >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_ACCESS_VARIANT_HPP_
