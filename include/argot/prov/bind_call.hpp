/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_BIND_CALL_HPP_
#define ARGOT_PROV_BIND_CALL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_provider_generator_with_provision.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/squash.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot::prov {

struct bind_call_fn
{
  // TODO(mattcalabrese) Fully constrain
  template< class ProviderGenerator, class... Providers
          , ARGOT_REQUIRES
            ( ArgumentProviderGeneratorWithProvision
              < std::decay_t< ProviderGenerator >
              , detail_argot::remove_cvref_t< Providers >...
              >
            )
            ( DecaySinkable< ProviderGenerator&& > )
            ( Sinkable< Providers&& >... )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( ProviderGenerator&& provider_generator
                            , Providers&&... providers
                            ) const
  {
    return prov::squash
    ( prov::lift_call
      ( call_detail::forward_and_decay_sink< ProviderGenerator >
        ( provider_generator )
      , call_detail::forward_and_sink< Providers >( providers )...
      )
    );
  }
} inline constexpr bind_call{};

template< class ProviderGenerator, class... Providers >
using result_of_bind_call
  = basic_result_of< bind_call_fn const&, ProviderGenerator, Providers... >;

template< class ProviderGenerator, class... Providers >
using result_of_bind_call_t
  = basic_result_of_t< bind_call_fn const&, ProviderGenerator, Providers... >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_BIND_CALL_HPP_
