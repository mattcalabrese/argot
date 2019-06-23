/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TRAITS_DESTRUCTIVE_PROVIDE_HPP_
#define ARGOT_PROV_TRAITS_DESTRUCTIVE_PROVIDE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_provider_to.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot::prov_traits {

struct destructive_provide_t
{
  template
  < class Provider, class Receiver
  , ARGOT_REQUIRES( ArgumentProviderTo< Provider, Receiver > )()
  >
  constexpr decltype( auto )
  operator ()( Provider&& provider, Receiver&& rec ) const
  {
    return access_raw_concept_map< ArgumentProvider< Provider > >
    ::provide( ARGOT_MOVE( provider ), ARGOT_MOVE( rec ) );
  }
} inline constexpr destructive_provide{};

template< class Provider, class Receiver >
using result_of_destructive_provide
  = basic_result_of< destructive_provide_t const&, Provider, Receiver >;

template< class Provider, class Receiver >
using result_of_destructive_provide_t
  = basic_result_of_t< destructive_provide_t const&, Provider, Receiver >;

}  // namespace (argot::prov_traits)

#endif  // ARGOT_PROV_TRAITS_DESTRUCTIVE_PROVIDE_HPP_
