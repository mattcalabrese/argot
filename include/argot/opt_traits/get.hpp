/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPT_TRAITS_GET_HPP_
#define ARGOT_OPT_TRAITS_GET_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/opt_traits/has_value.hpp>
#include <argot/remove_cvref.hpp>

#include <boost/assert.hpp>

namespace argot::opt_traits {

struct get_fn
{
  // TODO(mattcalabrese) Make sure a reference is returned.
  template< class Opt
          , ARGOT_REQUIRES( OptionalLike< remove_cvref_t< Opt > > )
                          ( Not< VolatileObject< remove_cvref_t< Opt > > > )
                          ()
          >
  constexpr decltype( auto ) operator ()( Opt&& opt ) const
  noexcept
  ( noexcept
    (
      access_raw_concept_map< OptionalLike< remove_cvref_t< Opt > > >
      ::get( ARGOT_FORWARD( Opt )( opt ) )
    )
  )
  {
    BOOST_ASSERT( ( has_value )( opt ) );
    return access_raw_concept_map< OptionalLike< remove_cvref_t< Opt > > >
    ::get( ARGOT_FORWARD( Opt )( opt ) );
  }
} inline constexpr get{};

template< class Opt >
using result_of_get_t = basic_result_of_t< get_fn const&, Opt >;

template< class Opt >
using result_of_get = basic_result_of< get_fn const&, Opt >;

}  // namespace (argot::opt_traits)

#endif  // ARGOT_OPT_TRAITS_GET_HPP_
