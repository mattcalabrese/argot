/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_INDEX_OF_HPP_
#define ARGOT_VARIANT_TRAITS_INDEX_OF_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>

namespace argot::variant_traits {

struct index_of_t
{
  template< class Var
          , ARGOT_REQUIRES( VariantLike< Var > )
                          ( Not< VolatileObject< Var > > )
                          ()
          >
  constexpr auto operator ()( Var const& self ) const
  {
    return access_raw_concept_map< VariantLike< Var > >::index_of( self );
  }
} inline constexpr index_of{};

template< class Var >
using result_of_index_of_t = basic_result_of_t< index_of_t const&, Var >;

template< class Var >
using result_of_index_of = basic_result_of< index_of_t const&, Var >;

}  // namespace (argot::variant_traits)

#endif  // ARGOT_VARIANT_TRAITS_INDEX_OF_HPP_
