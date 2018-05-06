/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_TRAITS_PROVIDE_HPP_
#define ARGOT_CONC_TRAITS_PROVIDE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
//#include <argot/concepts/concurrent_argument_provider_to.hpp>
#include <argot/concepts/persistent_concurrent_argument_provider.hpp>
//#include <argot/concepts/persistent_concurrent_argument_provider_to.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot::conc_traits {

struct then_provide_fn
{
  // TODO(mattcalabrese)
  //   Possibly check if we can even sinklike_cast.
  template
  < class Provider, class Receiver
  /*, ARGOT_REQUIRES
    ( typename argot_detail::conditional
      < std::is_rvalue_reference_v
        < call_detail::result_of_sinklike_cast_t< Provider&& > >
      >
      ::template meta_apply
      < ConcurrentArgumentProviderTo, PersistentConcurrentArgumentProviderTo
      , remove_cvref_t< Provider >, Receiver
      >
    )
    ()*/  // TODO(mattcalabrese) Constrain
  >
  constexpr decltype( auto )
  operator ()( Provider&& provider, Receiver&& receiver ) const
  {
    using RawProvider = remove_cvref_t< Provider >;

    using QualifiedProvider
      = call_detail::result_of_sinklike_cast_t< Provider&& >;

    if constexpr( std::is_rvalue_reference_v< QualifiedProvider > )
      return access_raw_concept_map< ConcurrentArgumentProvider< RawProvider > >
      ::then_provide( static_cast< QualifiedProvider >( provider )
                    , static_cast< Receiver&& >( receiver )
                    );
    else
      return access_raw_concept_map
      < PersistentConcurrentArgumentProvider< RawProvider > >
      ::then_provide( static_cast< QualifiedProvider >( provider )
                    , static_cast< Receiver&& >( receiver )
                    );
  }
} inline constexpr then_provide{};

template< class Provider, class Receiver >
using result_of_then_provide_t
  = basic_result_of_t< then_provide_fn const&, Provider, Receiver >;

template< class Provider, class Receiver >
using result_of_then_provide_
  = basic_result_of< then_provide_fn const&, Provider, Receiver >;

}  // namespace (argot::conc_traits)

#endif  // ARGOT_CONC_TRAITS_PROVIDE_HPP_
