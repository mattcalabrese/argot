/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_INVOCABLE_REFERENCE_HPP_
#define ARGOT_INVOCABLE_REFERENCE_HPP_

//[description
/*`
argot::invocable_reference for capturing a PotentiallyInvocable object by
reference into a function object that perfect-forwards its arguments to that
PotentiallyInvocable object.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/potentially_invocable.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/contained.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

struct invocable_reference_fn
{
  //<-
  template< class InvocableReference >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Reference< InvocableReference > );
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocable< InvocableReference > );

    // Note:
    //   It is very intentional that only `const&` and and `&&` overloads exist.

    // TODO(mattcalabrese) conditional noexcept

    template< class... P
            , ARGOT_REQUIRES
              ( InvocableWith< InvocableReference&, P&&... > )
              ()
            >
    constexpr decltype( auto ) operator ()( P&&... args ) const &
    {
      return argot_detail::constexpr_invoke
      ( argot::access_contained( invocable )
      , ARGOT_FORWARD( P )( args )...
      );
    }

    template< class... P
            , ARGOT_REQUIRES
              ( InvocableWith< InvocableReference&&, P&&... > )
              ()
            >
    constexpr decltype( auto ) operator ()( P&&... args ) const &&
    {
      return argot_detail::constexpr_invoke
      ( argot::access_contained( ARGOT_MOVE( invocable ) )
      , ARGOT_FORWARD( P )( args )...
      );
    }

    contained< InvocableReference > invocable;
  };
public: //->
  template< class Invocable
          , ARGOT_REQUIRES
            ( PotentiallyInvocable< Invocable&& > )
            ()
          >
  [[nodiscard]] constexpr auto
  operator ()( Invocable&& provider ) const noexcept//=;
  //<-
  {
    return impl< Invocable&& >
    { argot::make_contained< Invocable&& >
      ( ARGOT_FORWARD( Invocable )( provider ) )
    };
  } //->
} inline constexpr invocable_reference{};

template< class Invocable >
using result_of_invocable_reference//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< invocable_reference_fn const&, Invocable >; //->

template< class Invocable >
using result_of_invocable_reference_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< invocable_reference_fn const&, Invocable >; //->

} // namespace argot

//]

#endif  // ARGOT_INVOCABLE_REFERENCE_HPP_
