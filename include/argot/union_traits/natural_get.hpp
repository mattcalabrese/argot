/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_TRAITS_NATURAL_GET_HPP_
#define ARGOT_UNION_TRAITS_NATURAL_GET_HPP_

//[description
/*`
union_traits::natural_get is a facility for obtaining a Reference to an
/alternative/ of a UnionLike type.

[note This accessor takes the /index/ as a `std::integral_constant` function
parameter. For a similar facility that takes an Integral /index/ as an explicit
template parameter instead, use union_traits::get.
]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::union_traits {

struct natural_get_t
{
  // TODO(mattcalabrese) Constrain that the index is convertible to index type
  // TODO(mattcalabrese) Cast to the index type when calling get
  template< class Un, class Index
          , ARGOT_REQUIRES
            ( UnionLike< detail_argot::remove_cvref_t< Un > > )
            ( StdIntegralConstant< Index > )
            ( UnionIndex< detail_argot::remove_cvref_t< Un >, Index::value > )
            ()
          >
  constexpr
  decltype( auto ) operator ()( Un&& un, Index ) const//=;
  //<-
  {
    return access_raw_concept_map
    < UnionLike< detail_argot::remove_cvref_t< Un > > >
    ::template get< Index::value >( ARGOT_FORWARD( Un )( un ) );
  } //->
} inline constexpr natural_get{};

template< class Un, class Index >
using result_of_natural_get//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< natural_get_t const&, Un, Index >; //->

template< class Un, class Index >
using result_of_natural_get_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< natural_get_t const&, Un, Index >; //->

} // namespace (argot::union_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Un&& un`]
  [A Reference to a possibly const-qualified UnionLike type]
  [The type to access]
 ]
 [[`Index`]
  [A `std::integral_constant` of an Integral whose value is in the range
   \[0, `union_traits::num_alternatives_v< detail_argot::remove_cvref_t< Un > >` )
  ]
  [The /index/ value corresponding to the /alternative/ to access]
 ]
]
*/

//]

#endif  // ARGOT_UNION_TRAITS_NATURAL_GET_HPP_
