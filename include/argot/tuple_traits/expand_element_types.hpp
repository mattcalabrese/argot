/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_EXPAND_ELEMENT_TYPES_HPP_
#define ARGOT_TUPLE_TRAITS_EXPAND_ELEMENT_TYPES_HPP_

//[description
/*`
tuple_traits::expand_element_types_t is a utility for accessing all of the
element types of a TupleLike type at once. It is for element types what
tuple_traits::apply or std::apply is to elements.
*/
//]

#include <argot/concepts/tuple_like.hpp>
#include <argot/concepts/intrinsic_unpackable.hpp>
#include <argot/detail/if_.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::tuple_traits {
//<-
namespace detail_expand_elements {

struct basic_impl
{
  template< class Tup, template< class... > class Result >
  using apply
    = typename detail_intrinsic_unpackable::intrinsic_unpackable_impl
      < std::make_integer_sequence
        < typename access_raw_concept_map< TupleLike< Tup > >::index_type
        , access_raw_concept_map< TupleLike< Tup > >::num_elements
        >
      >
      ::template expand_element_types_t< Tup, Result >;
};

struct intrinsic_impl
{
  template< class Tup, template< class... > class Result >
  using apply
    = typename access_raw_concept_map< IntrinsicUnpackable< Tup > >
      ::template expand_element_types_t< Result >;
};

template
< class Tup, template< class... > class Result
, class T
    = ARGOT_REQUIRES( TupleLike< Tup > )
      < typename detail_if_::if_
        < ARGOT_IS_MODELED( IntrinsicUnpackable< Tup > ) >
        ::then_else::template _
        < intrinsic_impl
        , basic_impl
        >::template apply< Tup, Result >
      >
>
using impl_t = T;

} // namespace argot::tuple_traits(::detail_expand_elements)
//->

template< class Tup, template< class... > class Result >
using expand_element_types_t
  = //=ARGOT_REQUIRES( TupleLike< Tup > )
    //=< ``[unspecified_type]`` >;
//<-
    detail_expand_elements::impl_t< Tup, Result >;
//->

} // namespace (argot::tuple_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`class Tup`]
  [A TupleLike type]
  [The type to introspect]
 ]
 [[`template< class... > class Result`]
  [A template whose declaration is able to be instantiated with the element
   types of `Tup`]
  [A template that is instantiated with the element types of `Tup`. This
   instantiation is the type that is produced from substitution into
   `expand_element_types_t`.
  ]
 ]
]
*/

//]

#endif  // ARGOT_TUPLE_TRAITS_EXPAND_ELEMENT_TYPES_HPP_
