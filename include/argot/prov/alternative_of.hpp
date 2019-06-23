/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ALTERNATIVE_OF_HPP_
#define ARGOT_PROV_ALTERNATIVE_OF_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/index_of.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/union_traits/natural_get.hpp>

#include <type_traits>
#include <utility>

namespace argot::prov {

struct alternative_of_fn
{
  template< class Var
          , ARGOT_REQUIRES
            ( VariantLike< detail_argot::remove_cvref_t< Var > > )
            ( Not< VolatileObject< std::remove_reference_t< Var > > > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Var&& var ) const
  {
    return prov::lift_call
    ( union_traits::natural_get
    , prov::reference_to( ARGOT_FORWARD( Var )( var ) )
    , prov::index_of( var )
    );
  }
} inline constexpr alternative_of{};

template< class Var >
using result_of_alternative_of
  = basic_result_of< alternative_of_fn const&, Var >;

template< class Var >
using result_of_alternative_of_t
  = basic_result_of_t< alternative_of_fn const&, Var >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_ALTERNATIVE_OF_HPP_
