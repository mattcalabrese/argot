/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_LIFT_RESULT_HPP_
#define ARGOT_CONC_LIFT_RESULT_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/requires.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::conc {

struct lift_result_fn
{
  template
  < class Invocable, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Invocable&&, P&&... > )
    ( ArgumentProvider
      < remove_cvref_t
        < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... > >
      >
    )
    ( Sinkable // TODO(mattcalabrese) Only check if not returning a reference
      < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... >&& >
    )
    ()
  >
  [[nodiscard]] constexpr auto
  operator ()( Invocable&& invocable, P&&... args ) const
  {
    return lift_fn::impl
    < remove_cvref_t
      < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... > >
    >
    { argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Invocable )( invocable ), ARGOT_FORWARD( P )( args )... )
    };
  }
} inline constexpr lift_result{};

template< class Invocable, class... P >
using result_of_lift_result_t
  = basic_result_of_t< lift_result_fn const&, Invocable, P... >;

template< class Invocable, class... P >
using result_of_lift_result
  = basic_result_of< lift_result_fn const&, Invocable, P... >;

} // namespace (argot::conc)

#endif  // ARGOT_CONC_LIFT_RESULT_HPP_
