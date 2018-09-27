/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_GET_HPP_
#define ARGOT_VARIANT_TRAITS_GET_HPP_

//[description
/*`
variant_traits::get is a facility for obtaining a Reference to an /alternative/
of a VariantLike type.

[note This accessor takes the /index/ as an explicit template parameter. For a
      similar facility that takes a `std::integral_constant` /index/ as a
      function parameter instead, use variant_traits::natural_get.
]
*/
//]

#include <argot/concepts/union_like.hpp>
#include <argot/concepts/variant_index.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <boost/assert.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::variant_traits {

template< auto Index >
struct get_t
{
  template< class Var
          , ARGOT_REQUIRES
            ( VariantLike< detail_argot::remove_cvref_t< Var > > )
            ( VariantIndex< detail_argot::remove_cvref_t< Var >, Index > )
            ()
          >
  constexpr decltype( auto ) operator ()( Var&& var ) const//=;
//<-
  {
    BOOST_ASSERT( ( index_of )( var ) == Index );
    return access_raw_concept_map
    < UnionLike< detail_argot::remove_cvref_t< Var > > >
    ::template get< Index >( ARGOT_FORWARD( Var )( var ) );
  } //->
};

template< auto Index >
get_t< Index > constexpr get{};

template< auto Index, class Var >
using result_of_get_t//= = ``[see_prologue_result_of]``;
//<-
  = decltype
    ( ARGOT_DECLVAL( get_t< Index > const& )( ARGOT_DECLVAL( Var ) ) ); //->

template< auto Index, class Var >
using result_of_get//= = ``[see_prologue_result_of]``;
//<-
  = call_detail::lazy_expand_get< result_of_get_t, Index, Var >; //->

} // namespace (argot::variant_traits)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`auto Index`]
  [An Integral value in the range
   \[0, `variant_traits::num_alternatives_v< detail_argot::remove_cvref_t< Var > >` )
  ]
  [The /index/ value corresponding to the /alternative/ of the VariantLike to access]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`Var&& var`]
  [A Reference to a possibly const-qualified VariantLike type]
  [The object to access]
 ]
]
*/

//]

#endif  // ARGOT_VARIANT_TRAITS_GET_HPP_
