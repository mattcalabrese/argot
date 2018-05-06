/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_BLESS_RESULT_HPP_
#define ARGOT_BLESS_RESULT_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/conc/bless.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/gen/requires.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/remove_cvref.hpp>

namespace argot::conc {

struct bless_result_fn
{
  // TODO(mattcalabrese) Constrain to possibly callable.
  template
  < class Invocable, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Invocable&&, P&&... > )
    ( Future
      < remove_cvref_t
        < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... > >
      >
    )
    ( ArgumentProvider
      < fut_traits::value_type_t
        < remove_cvref_t
          < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... > >
        >
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
    return bless_fn::impl
    < remove_cvref_t
      < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... > >
    >
    { argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Invocable )( invocable ), ARGOT_FORWARD( P )( args )... )
    };
  }
} inline constexpr bless_result{};

template< class Invocable, class... P >
using result_of_bless_result_t
  = basic_result_of_t< bless_result_fn const&, Invocable, P... >;

template< class Invocable, class... P >
using result_of_bless_result
  = basic_result_of< bless_result_fn const&, Invocable, P... >;

} // namespace (argot::conc)

#endif  // ARGOT_BLESS_RESULT_HPP_
