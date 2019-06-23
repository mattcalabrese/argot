/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_ALTERNATIVE_OF_BY_VALUE_HPP_
#define ARGOT_CONC_ALTERNATIVE_OF_BY_VALUE_HPP_

#include <argot/conc/lift_result.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/sink.hpp>
#include <argot/prov/alternative_of_by_value.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::conc {

struct alternative_of_by_value_fn
{
  // TODO(mattcalabrese) Define by lifting the result.
  template< class Var
          , ARGOT_REQUIRES( VariantLike< detail_argot::remove_cvref_t< Var > > )
                          ( Sinkable< Var&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator ()( Var&& tup ) const
  {
    return conc::lift_result
    ( prov::alternative_of_by_value
    , call_detail::forward_and_sink< Var >( tup )
    );
  }
} inline constexpr alternative_of_by_value{};

template< class Var >
using result_of_alternative_of_by_value
  = basic_result_of< alternative_of_by_value_fn const&, Var >;

template< class Var >
using result_of_alternative_of_by_value_t
  = basic_result_of_t< alternative_of_by_value_fn const&, Var >;

}  // namespace (argot::conc)

#endif  // ARGOT_CONC_ALTERNATIVE_OF_BY_VALUE_HPP_
