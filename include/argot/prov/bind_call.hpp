/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_BIND_CALL_HPP_
#define ARGOT_PROV_BIND_CALL_HPP_

//[description
/*`
prov::bind_call is an ArgumentProviderGenerator that takes an Invocable and a
series of ArgumentProviders, and provides the provision of the result of a call
to the Invocable with the expanded arguments. It captures the Invocable by
decay-copy and captures the ArgumentProviders by value.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_provider_generator_with_provision.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/higher_order_argument_provider.hpp>
#include <argot/concepts/invocable_object_with_provision.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/squash.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct bind_call_fn
{
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
                            ) const//=;
//<-
  {
    return prov::squash
    ( prov::lift_call
      ( call_detail::forward_and_decay_sink< ProviderGenerator >
        ( provider_generator )
      , call_detail::forward_and_sink< Providers >( providers )...
      )
    );
  } //->
} inline constexpr bind_call{};

template< class ProviderGenerator, class... Providers >
using result_of_bind_call//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< bind_call_fn const&, ProviderGenerator, Providers... >;
//->

template< class ProviderGenerator, class... Providers >
using result_of_bind_call_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< bind_call_fn const&, ProviderGenerator, Providers... >;
//->

} // namespace (argot::prov)

/*`
[element_spec_heading]

[table Requirements for `operator()`
 [[Element]                [Specification]]
 [[Effects_Equivalent_to_Provider ] [

```
return prov::squash
       ( prov::lift_call
         ( std::forward< ProviderGenerator >( provider_generator )
         , std::forward< Providers >( providers )...
         )
       );
```
 ]]
]
*/
//]

#endif  // ARGOT_PROV_BIND_CALL_HPP_
