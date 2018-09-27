/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_NATURAL_GET_HPP_
#define ARGOT_VARIANT_TRAITS_NATURAL_GET_HPP_

//[description
/*`
variant_traits::natural_get is a facility for obtaining a Reference to an
/alternative/ of a VariantLike type.

[note This accessor takes the /index/ as a `std::integral_constant` function
parameter. For a similar facility that takes an Integral /index/ as an explicit
template parameter instead, use variant_traits::get.
]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/variant_index.hpp>
#include <argot/concepts/variant_like.hpp>
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

struct natural_get_t
{
  // TODO(mattcalabrese) Constrain that the index is convertible to index type
  // TODO(mattcalabrese) Cast to the index type when calling get
  template< class Var, class Index
          , ARGOT_REQUIRES
            ( VariantLike< detail_argot::remove_cvref_t< Var > > )
            ( StdIntegralConstant< Index > )
            ( VariantIndex< detail_argot::remove_cvref_t< Var >, Index::value > )
            ()
          >
  constexpr decltype( auto )
  operator ()( Var&& var, Index ) const//=;
  //<-
  {
    BOOST_ASSERT( ( index_of )( var ) == Index::value );
    return access_raw_concept_map
    < UnionLike< detail_argot::remove_cvref_t< Var > > >
    ::template get< Index::value >( ARGOT_FORWARD( Var )( var ) );
  } //->
} inline constexpr natural_get{};

template< class Var, class Index >
using result_of_natural_get//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< natural_get_t const&, Var, Index >; //->

template< class Var, class Index >
using result_of_natural_get_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< natural_get_t const&, Var, Index >; //->

} // namespace (argot::variant_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Var&& var`]
  [A Reference to a possibly const-qualified VariantLike type]
  [The type to access]
 ]
 [[`Index`]
  [A `std::integral_constant` of an Integral whose value is in the range
   \[0, `variant_traits::num_alternatives_v< detail_argot::remove_cvref_t< Var > >` )
  ]
  [The /index/ value corresponding to the /alternative/ to access]
 ]
]
*/

//]

#endif  // ARGOT_VARIANT_TRAITS_NATURAL_GET_HPP_
