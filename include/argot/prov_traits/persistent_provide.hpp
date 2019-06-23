/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TRAITS_PERSISTENT_PROVIDE_HPP_
#define ARGOT_PROV_TRAITS_PERSISTENT_PROVIDE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider_to.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::prov_traits {

struct persistent_provide_t
{
  template
  < class Provider, class Receiver
  , ARGOT_REQUIRES
    ( PersistentArgumentProviderTo
      < std::remove_const_t< std::remove_reference_t< Provider > >
      , Receiver
      >
    )()
  >
  constexpr decltype( auto )
  operator ()( Provider const& provider, Receiver&& receiver ) const
  {
    return access_raw_concept_map< PersistentArgumentProvider< Provider > >
    ::provide( provider, static_cast< Receiver&& >( receiver ) );
  }
} inline constexpr persistent_provide{};

template< class Provider, class Receiver >
using result_of_persistent_provide
  = basic_result_of< persistent_provide_t const&, Provider&&, Receiver&& >;

template< class Provider, class Receiver >
using result_of_persistent_provide_t
  = basic_result_of_t< persistent_provide_t const&, Provider&&, Receiver&& >;

}  // namespace (argot::prov_traits)

#endif  // ARGOT_PROV_TRAITS_PERSISTENT_PROVIDE_HPP_
