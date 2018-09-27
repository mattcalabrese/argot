/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_TRAITS_INDEX_OF_HPP_
#define ARGOT_VARIANT_TRAITS_INDEX_OF_HPP_

//[description
/*`
variant_traits::index_of is a facility for obtaining the /active index/ of a
VariantLike type.

[note The VariantLike type must have one of its /alternatives/ active for a call
      to this facility. Most notably, it is invalid to pass a `std::variant` to
      variant_traits::index_of when it is in its /valueless by exception/ state.
]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::variant_traits {

struct index_of_t
{
  // Precondition: An alternative of `var` is active
  template< class Var
          , ARGOT_REQUIRES
            ( VariantLike< Var > )
            ( Not< VolatileObject< Var > > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Var const& var ) const//=;
  //<-
  {
    return access_raw_concept_map< VariantLike< Var > >::index_of( var );
  } //->
} inline constexpr index_of{};

template< class Var >
using result_of_index_of_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< index_of_t const&, Var >; //->

// TODO(mattcalabrese) Remove
template< class Var >
using result_of_index_of//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< index_of_t const&, Var >; //->

} // namespace (argot::variant_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Var const& var`]
  [A reference to a possibly-const instance of a VariantLike type]
  [The object from which to retrieve the value of the /active index/]
 ]
]
*/

//]

#endif  // ARGOT_VARIANT_TRAITS_INDEX_OF_HPP_
