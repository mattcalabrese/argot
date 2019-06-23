/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_INVOCABLE_REFERENCE_HPP_
#define ARGOT_INVOCABLE_REFERENCE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/potentially_invocable.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/contained.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>

namespace argot {

struct invocable_reference_t
{
 public:
  template< class InvocableReference >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Reference< InvocableReference > );
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocable< InvocableReference > );

    // TODO(mattcalabrese) conditional noexcept

    template< class... P
            , ARGOT_REQUIRES( InvocableWith< InvocableReference&, P&&... > )()
            >
    constexpr decltype( auto ) operator ()( P&&... args ) const &
    {
      return argot_detail::constexpr_invoke
      ( argot::access_contained( invocable )
      , ARGOT_FORWARD( P )( args )...
      );
    }

    template< class... P
            , ARGOT_REQUIRES( InvocableWith< InvocableReference&&, P&&... > )()
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
public:
  // TODO(mattcalabrese) Constrain to be possibly invocable
  template< class Invocable
          , ARGOT_REQUIRES( PotentiallyInvocable< Invocable&& > )()
          >
  [[nodiscard]] constexpr auto
  operator ()( Invocable&& provider ) const noexcept
  {
    return impl< Invocable&& >
    { argot::make_contained< Invocable&& >
      ( ARGOT_FORWARD( Invocable )( provider ) )
    };
  }
} inline constexpr invocable_reference{};

template< class Invocable >
using result_of_invocable_reference
  = basic_result_of< invocable_reference_t const&, Invocable >;

template< class Invocable >
using result_of_invocable_reference_t
  = basic_result_of_t< invocable_reference_t const&, Invocable >;

}  // namespace argot

#endif  // ARGOT_INVOCABLE_REFERENCE_HPP_
