/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPT_TRAITS_GET_HPP_
#define ARGOT_OPT_TRAITS_GET_HPP_

//[description
/*`
opt_traits::get is a facility for obtaining a reference to the /element/ of
an instance of an OptionalLike type. 
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/opt_traits/has_value.hpp>

#include <boost/assert.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::opt_traits {

struct get_fn
{
  // Precondition: opt is engaged
  // TODO(mattcalabrese) Make sure a reference is returned.
  template< class Opt
          , ARGOT_REQUIRES
            ( OptionalLike< detail_argot::remove_cvref_t< Opt > > )
            ( Not< VolatileObject< detail_argot::remove_cvref_t< Opt > > > )
            ()
          >
  constexpr decltype( auto ) operator ()( Opt&& opt ) const//=;
  //<-
  noexcept
  ( noexcept
    (
      access_raw_concept_map
      < OptionalLike< detail_argot::remove_cvref_t< Opt > > >
      ::get( ARGOT_FORWARD( Opt )( opt ) )
    )
  )
  {
    BOOST_ASSERT( ( has_value )( opt ) );
    return access_raw_concept_map< OptionalLike< detail_argot::remove_cvref_t< Opt > > >
    ::get( ARGOT_FORWARD( Opt )( opt ) );
  } //->
} inline constexpr get{};

template< class Opt >
using result_of_get_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< get_fn const&, Opt >; //->

template< class Opt >
using result_of_get//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< get_fn const&, Opt >; //->

} // namespace (argot::opt_traits)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Opt&& opt`]
  [A Reference to a possibly const-qualified OptionalLike type]
  [The object to access]
 ]
]
*/

//]

#endif  // ARGOT_OPT_TRAITS_GET_HPP_
