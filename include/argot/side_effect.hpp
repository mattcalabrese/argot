/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SIDE_EFFECT_HPP_
#define ARGOT_SIDE_EFFECT_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/if_.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/do_nothing.hpp>

#include <type_traits>

namespace argot {

struct side_effect_fn
{
  // TODO(mattcalabrese) Make a concept for the check below.
  template
  < class... Providers
  , ARGOT_REQUIRES
    ( typename argot_detail::conditional
      < std::is_rvalue_reference_v
        < call_detail::result_of_sinklike_cast_t< Providers&& > >
      >
      ::template meta_apply
      < ArgumentProvider, PersistentArgumentProvider
      , detail_argot::remove_cvref_t< Providers >
      >...
    )
    ()
  >
  constexpr void operator ()( Providers&&... providers ) const
  {
    ( static_cast< void >
      ( prov_traits::provide
        ( ARGOT_FORWARD( Providers )( providers ), receiver::do_nothing() )
      )
    , ...
    );
  }
} inline constexpr side_effect{};

template< class... P >
using result_of_side_effect_t
  = basic_result_of_t< side_effect_fn const&, P... >;

template< class... P >
using result_of_side_effect
  = basic_result_of< side_effect_fn const&, P... >;

}  // namespace argot

#endif // ARGOT_SIDE_EFFECT_HPP_
