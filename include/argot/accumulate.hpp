/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_ACCUMULATE_HPP_
#define ARGOT_ACCUMULATE_HPP_

//[description
/*`
argot::accumulate is a facility that reduces arguments down to a single result
through the successive application of a binary function object on an object and
each logical argument.

[note
 This algorithm puts ArgumentProviders through provision, and perfect-forwards
 each argument that is not an ArgumentProvider.
]
*/
//]

#include <argot/concepts/can_default_to_reference_to.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/forgetful_invoke.hpp>
#include <argot/reducer/to.hpp>

#include <memory>
#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {
//<-
namespace detail_accumulate {

// A function object that outputs any number of arguments to a stream.
template< class Inv, class State >
struct impl_fn
{
  template< class... P >
  constexpr void operator()( P&&... arg ) const
  {
    ( static_cast< void >
      ( argot_detail::constexpr_invoke
        ( *inv, *state, ARGOT_FORWARD( P )( arg ) )
      )
    , ...
    );
  }

  Inv* inv;
  State* state;
};

} // namespace argot(::detail_output)
//->

struct accumulate_fn
{
  // TODO(mattcalabrese) Write the invocability requirement for each element.
  template< class Inv, class State, class... P
          , ARGOT_REQUIRES
            ( CanDefaultToReferenceTo< P >... )
            ( MoveConstructible< detail_argot::remove_cvref_t< State > > )
            ( Sinkable< State&& > )
            ()
          >
  constexpr auto operator()( Inv&& inv, State&& state, P&&... args ) const//=;
  //<-
  {
    auto result = call_detail::forward_and_sink< State >( state );

    ( prov_traits::provide
      ( prov::default_to_reference_to( ARGOT_FORWARD( P )( args ) )
      , receiver::forgetful_invoke
        ( detail_accumulate::impl_fn
          < std::remove_reference_t< Inv >
          , detail_argot::remove_cvref_t< State >
          >
          { std::addressof( inv )
          , std::addressof( result )
          }
        )
      )
    , ...
    );

    return result;
  } //->
} inline constexpr accumulate{};

// TODO(mattcalabrese) Result of calculators

} // namespace argot

// TODO(mattcalabrese) Complete the docs

//]

#endif  // ARGOT_OUTPUT_HPP_
