/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_GET_HPP_
#define ARGOT_UNION_TRAITS_GET_HPP_

//[description
/*`
union_traits::get is a facility for obtaining a Reference to an /alternative/ of
a UnionLike type.

[note This accessor takes the /index/ as an explicit template parameter. For a
similar facility that takes a `std::integral_constant` /index/ as a function
parameter instead, use union_traits::natural_get.
]
*/
//]

#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/union_traits/num_alternatives.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::union_traits {

template< auto Index >
struct get_fn
{
  template< class Un
          , ARGOT_REQUIRES
            ( UnionLike< detail_argot::remove_cvref_t< Un > > )
            ( UnionIndex< detail_argot::remove_cvref_t< Un >, Index > )
            ()
          >
  constexpr decltype( auto ) operator ()( Un&& un ) const//=;
//<-
  {
    return access_raw_concept_map
    < UnionLike< detail_argot::remove_cvref_t< Un > > >
    ::template get< Index >( ARGOT_FORWARD( Un )( un ) );
  } //->
};

template< auto Index >
get_fn< Index > constexpr get{};

template< auto Index, class Un >
using result_of_get_t//= = ``[see_prologue_result_of]``;
//<-
  = decltype
    ( ARGOT_DECLVAL( get_fn< Index > const& )( ARGOT_DECLVAL( Un ) ) ); //->

template< auto Index, class Un >
using result_of_get//= = ``[see_prologue_result_of]``;
//<-
  = call_detail::lazy_expand_get< result_of_get_t, Index, Un >; //->

} // namespace (argot::union_traits)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`auto Index`]
  [An Integral value in the range
   \[0, `union_traits::num_alternatives_v< detail_argot::remove_cvref_t< Un > >` )
  ]
  [The /index/ value corresponding to the /alternative/ of the UnionLike to access]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`Un&& un`]
  [A Reference to a possibly const-qualified UnionLike type]
  [The type to access]
 ]
]
*/

//]

#endif  // ARGOT_UNION_TRAITS_GET_HPP_
