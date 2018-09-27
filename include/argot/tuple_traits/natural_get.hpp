/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_NATURAL_GET_HPP_
#define ARGOT_TUPLE_TRAITS_NATURAL_GET_HPP_

//[description
/*`
tuple_traits::natural_get is a facility for obtaining a Reference to an element
of a TupleLike type.

[note This accessor takes the /index/ as a `std::integral_constant` function
parameter. For a similar facility that takes an Integral /index/ as an explicit
template parameter instead, use tuple_traits::get.
]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/tuple_index.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/tuple_traits/get.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::tuple_traits {

struct natural_get_t
{
  // TODO(mattcalabrese) Constrain that the index is convertible to the index type
  // TODO(mattcalabrese) Cast to the index type when calling get
  template< class Tuple, class Index
          , ARGOT_REQUIRES
            ( TupleLike< detail_argot::remove_cvref_t< Tuple > > )
            ( StdIntegralConstant< Index > )
            ( TupleIndex< detail_argot::remove_cvref_t< Tuple >, Index::value > )
            ()
          >
  constexpr
  decltype( auto ) operator ()( Tuple&& tuple_like, Index index ) const//=;
  //<-
  {
    return access_raw_concept_map
    < TupleLike< detail_argot::remove_cvref_t< Tuple > > >
    ::template get< Index::value >( ARGOT_FORWARD( Tuple )( tuple_like ) );
  } //->
} inline constexpr natural_get{};

template< class Tuple, class Index >
using result_of_natural_get//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< natural_get_t const&, Tuple, Index >; //->

template< class Tuple, class Index >
using result_of_natural_get_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< natural_get_t const&, Tuple, Index >; //->

} // namespace (argot::tuple_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Tup&& tup`]
  [A Reference to a possibly const-qualified TupleLike type]
  [The type to access]
 ]
 [[`Index`]
  [A `std::integral_constant` of an Integral whose value is in the range
   \[0, `tuple_traits::num_elements_v< detail_argot::remove_cvref_t< Tup > >` )
  ]
  [The /index/ value corresponding to the /element/ to access]
 ]
]
*/

//]

#endif  // ARGOT_TUPLE_TRAITS_NATURAL_GET_HPP_
