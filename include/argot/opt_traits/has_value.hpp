/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPT_TRAITS_HAS_VALUE_HPP_
#define ARGOT_OPT_TRAITS_HAS_VALUE_HPP_

//[description
/*`
opt_traits::has_value is a facility that takes an instance of an OptionalLike
type and returns `true` if the OptionalLike is `engaged`, otherwise it returns
`false`.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot::opt_traits {

//[docs
/*`
[synopsis_heading]
*/

struct has_value_fn
{
  template< class Opt, ARGOT_REQUIRES( OptionalLike< Opt > )() >
  constexpr bool operator ()( Opt const& opt ) const//=;
  //<-
  noexcept
  ( noexcept
    (   access_raw_concept_map
        < OptionalLike< detail_argot::remove_cvref_t< Opt > > >
        ::has_value( opt )
      ? true
      : false
    )
  )
  {
    return access_raw_concept_map
    < OptionalLike< detail_argot::remove_cvref_t< Opt > > >
    ::has_value( opt );
  } //->
} inline constexpr has_value{};

template< class Opt >
using result_of_has_value_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< has_value_fn const&, Opt >; //->

template< class Opt >
using result_of_has_value//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< has_value_fn const&, Opt >; //->

} // namespace (argot::opt_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Opt const& opt`]
  [A Reference to a possibly-const-qualified OptionalLike type]
  [The object to access]
 ]
]
*/

//]

#endif  // ARGOT_OPT_TRAITS_HAS_VALUE_HPP_
