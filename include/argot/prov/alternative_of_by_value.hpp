/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ALTERNATIVE_OF_BY_VALUE_HPP_
#define ARGOT_PROV_ALTERNATIVE_OF_BY_VALUE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/index_of.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/union_traits/natural_get.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::prov {

struct alternative_of_by_value_fn
{
  template< class Var
          , ARGOT_REQUIRES( VariantLike< detail_argot::remove_cvref_t< Var > > )
                          ( Sinkable< Var&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator ()( Var&& var ) const
  {
    return prov::lift_call
    ( union_traits::natural_get
    , prov::value_of( call_detail::forward_and_sink< Var >( var ) )
    , prov::index_of( var )
    );
  }
} inline constexpr alternative_of_by_value{};

template< class Var >
using result_of_alternative_of_by_value
  = basic_result_of< alternative_of_by_value_fn const&, Var >;

template< class Var >
using result_of_alternative_of_by_value_t
  = basic_result_of_t< alternative_of_by_value_fn const&, Var >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_ALTERNATIVE_OF_BY_VALUE_HPP_
