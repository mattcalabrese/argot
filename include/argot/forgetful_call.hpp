/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FORGETFUL_CALL_HPP_
#define ARGOT_FORGETFUL_CALL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argot_invocable_before_reduction.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/requires.hpp>
#include <argot/invocable_reference.hpp>
#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/forgetful_invoke.hpp>

#include <type_traits>

namespace argot {

struct forgetful_call_fn
{
  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( ArgotInvocableBeforeReduction< std::decay_t< Fun >&&, P&&... > )
    ()
  >
  constexpr void operator ()( Fun&& fun, P&&... args ) const
  {
    prov_traits::destructive_provide
    ( prov::default_to_reference_to( ARGOT_FORWARD( P )( args )... )
    , receiver::forgetful_invoke
      ( argot::invocable_reference( ARGOT_FORWARD( Fun )( fun ) ) )
    );
  }
} inline constexpr forgetful_call{};

template< class Fun, class... P >
using result_of_forgetful_call_t
  = basic_result_of_t< forgetful_call_fn const&, Fun, P... >;

template< class Fun, class... P >
using result_of_forgetful_call
  = basic_result_of< forgetful_call_fn const&, Fun, P... >;

} // namespace argot

#endif // ARGOT_FORGETFUL_CALL_HPP_
