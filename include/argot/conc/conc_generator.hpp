/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_GENERATOR_HPP_
#define ARGOT_CONC_GENERATOR_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/conc/lift.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/persistent_invocable_object_with.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>

#include <type_traits>

namespace argot::conc {

struct conc_generator_fn
{
  template< class Generator >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Generator > );

    // TODO(mattcalabrese) Rvalue overload?
    template
    < class... P
    , ARGOT_REQUIRES( PersistentInvocableObjectWith< Generator, P&&... > )()
    >
    constexpr decltype( auto ) operator ()( P&&... args ) const
    {
      return conc::lift( generator( ARGOT_FORWARD( P )( args )... ) );
    }

    ARGOT_NO_UNIQUE_ADDRESS Generator generator;
  };

  template
  < class Generator
  , ARGOT_REQUIRES( PotentiallyInvocableObject< std::decay_t< Generator > > )
                  ( DecaySinkable< Generator&& > )
                  ()
  >
  constexpr auto operator ()( Generator&& gen ) const
  {
    return impl< std::decay_t< Generator > >
    { call_detail::forward_and_decay_sink< Generator >( gen ) };
  }

} inline constexpr conc_generator{};

template< class Generator >
using result_of_conc_generator_t
  = basic_result_of_t< conc_generator_fn const&, Generator >;

template< class Generator >
using result_of_conc_generator
  = basic_result_of< conc_generator_fn const&, Generator >;

} // namespace (argot::conc)

#endif  // ARGOT_CONC_GENERATOR_HPP_
