/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_TRAITS_AS_FUTURE_HPP_
#define ARGOT_CONC_TRAITS_AS_FUTURE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>

namespace argot::conc_traits {

struct as_future_fn
{
  template< class ConcProvider
          , ARGOT_REQUIRES( ConcurrentArgumentProvider< ConcProvider > )()
          >
  constexpr decltype( auto ) operator ()( ConcProvider&& self ) const
  {
    return access_raw_concept_map< ConcurrentArgumentProvider< ConcProvider > >
    ::as_future( ARGOT_MOVE( self ) );
  }
} inline constexpr as_future{};

template< class ConcProvider >
using result_of_as_future_t
  = basic_result_of_t< as_future_fn const&, ConcProvider >;

template< class ConcProvider >
using result_of_as_future
  = basic_result_of< as_future_fn const&, ConcProvider >;

}  // namespace (argot::conc_traits)

#endif  // ARGOT_CONC_TRAITS_AS_FUTURE_HPP_
