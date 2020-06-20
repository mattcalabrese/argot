/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TUPLE_TRAITS_APPLY_HPP_
#define ARGOT_TUPLE_TRAITS_APPLY_HPP_

//[description
/*`
tuple_traits::apply is a utility for expanding a TupleLike type's elements into
arguments of an Invocable.
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

struct apply_fn
{
  // TODO(mattcalabrese) Constrain callability
  template< class Fun, class Tup
          , ARGOT_REQUIRES
            ( TupleLike< detail_argot::remove_cvref_t< Tup > > )
            ()
          >
  constexpr decltype( auto ) operator ()( Fun&& fun, Tup&& tup ) const//=;
  //<-
  {
    using raw_tup = detail_argot::remove_cvref_t< Tup >;
    using tuple_like_map = access_raw_concept_map< TupleLike< raw_tup > >;

    if constexpr( ARGOT_IS_MODELED( IntrinsicUnpackable< raw_tup > ) )
      return access_raw_concept_map< IntrinsicUnpackable< raw_tup > >
      ::apply( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( Tup )( tup ) );
    else
      return detail_intrinsic_unpackable::intrinsic_unpackable_impl
      < std::make_integer_sequence
        < typename tuple_like_map::index_type
        , tuple_like_map::num_elements
        >
      >::apply( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( Tup )( tup ) );
  } //->
} inline constexpr apply{};

template< class Fun, class Tup >
using result_of_apply//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< apply_fn const&, Fun, Tup >; //->

template< class Fun, class Tup >
using result_of_apply_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< apply_fn const&, Fun, Tup >; //->
} // namespace (argot::tuple_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Fun&& fun`]
  [An Invocable that is able to be invoked with an argument list consisting
   of all of the elements of `Tup`, in order
  ]
  [The Invocable to be called]
 ]
 [[`Tup&& tup`]
  [A reference to a TupleLike type]
  [The TupleLike type whose elements are to be passed as arguments to `fun`]
 ]
]
*/

//]

#endif  // ARGOT_TUPLE_TRAITS_APPLY_HPP_
