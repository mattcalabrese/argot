/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_GET_HPP_
#define ARGOT_TUPLE_TRAITS_GET_HPP_

//[description
/*`
tuple_traits::get is a facility for obtaining a Reference to an element of a
TupleLike type.

[note This accessor takes the /index/ as an explicit template parameter. For a
similar facility that takes a `std::integral_constant` /index/ as a function
parameter instead, use tuple_traits::natural_get.
]
*/
//]

#include <argot/concepts/tuple_index.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::tuple_traits {

template< auto Index >
struct get_fn
{
  template< class Tup
          , ARGOT_REQUIRES
            ( TupleLike< detail_argot::remove_cvref_t< Tup > > )
            ( TupleIndex< detail_argot::remove_cvref_t< Tup >, Index > )
            ()
          >
  constexpr decltype( auto ) operator ()( Tup&& tup ) const//=;
  //<-
  {
    return access_raw_concept_map
    < TupleLike< detail_argot::remove_cvref_t< Tup > > >
    ::template get< Index >( ARGOT_FORWARD( Tup )( tup ) );
  } //->
};

template< auto Index >
get_fn< Index > constexpr get{};

template< auto Index, class Tup >
using result_of_get_t//= = ``[see_prologue_result_of]``;
//<-
  = decltype
    ( ARGOT_DECLVAL( get_fn< Index > const& )( ARGOT_DECLVAL( Tup ) ) ); //->

// TODO(mattcalabrese) Remove
template< auto Index, class Tup >
using result_of_get//= = ``[see_prologue_result_of]``;
//<-
 = call_detail::lazy_expand_get< result_of_get_t, Index, Tup >; //->

} // namespace (argot::tuple_traits)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`auto Index`]
  [An Integral value in the range
   \[0, `tuple_traits::num_elements_v< detail_argot::remove_cvref_t< Tup > >` )
  ]
  [The /index/ value corresponding to the /element/ of the tuple to access]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`Tup&& tup`]
  [A Reference to a possibly const-qualified TupleLike type]
  [The type to access]
 ]
]
*/

//]

#endif  // ARGOT_TUPLE_TRAITS_GET_HPP_
