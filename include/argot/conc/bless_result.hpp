/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_BLESS_RESULT_HPP_
#define ARGOT_BLESS_RESULT_HPP_

//[description
/*`
conc::bless_result is a facility that
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/conc/bless.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

struct bless_result_fn
{
  template
  < class Invocable, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Invocable&&, P&&... > )
    ( Future
      < detail_argot::remove_cvref_t
        < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... > >
      >
    )
    ( ArgumentProvider
      < fut_traits::value_type_t
        < detail_argot::remove_cvref_t
          < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... > >
        >
      >
    )
    ( Sinkable // TODO(mattcalabrese) Only check if not returning a reference
      < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... >&& >
    )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Invocable&& invocable, P&&... args ) const//=;
  //<-
  {
    return bless_fn::impl
    < detail_argot::remove_cvref_t
      < argot_detail::result_of_constexpr_invoke_t< Invocable&&, P&&... > >
    >
    { argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Invocable )( invocable ), ARGOT_FORWARD( P )( args )... )
    };
  } //->
} inline constexpr bless_result{};

template< class Invocable, class... P >
using result_of_bless_result_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< bless_result_fn const&, Invocable, P... >; //->

template< class Invocable, class... P >
using result_of_bless_result//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< bless_result_fn const&, Invocable, P... >; //->

} // namespace (argot::conc)

//]

#endif  // ARGOT_BLESS_RESULT_HPP_
