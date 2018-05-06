/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_INDEX_OF_HPP_
#define ARGOT_PROV_INDEX_OF_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/variant_index.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/variant_traits/index_of.hpp>

namespace argot::prov {

struct index_of_fn
{
  template< class Variant
          , ARGOT_REQUIRES( VariantLike< remove_cvref_t< Variant > > )()
          >
  [[nodiscard]] constexpr auto operator ()( Variant const& variant_like ) const
  {
    return variant_index< remove_cvref_t< Variant > >
    ( variant_traits::index_of( variant_like ) );
  }
} inline constexpr index_of{};

template< class Variant >
using result_of_index_of = basic_result_of< index_of_fn const&, Variant >;

template< class Variant >
using result_of_index_of_t = basic_result_of_t< index_of_fn const&, Variant >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_INDEX_OF_HPP_
