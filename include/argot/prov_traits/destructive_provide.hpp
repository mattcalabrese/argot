/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TRAITS_DESTRUCTIVE_PROVIDE_HPP_
#define ARGOT_PROV_TRAITS_DESTRUCTIVE_PROVIDE_HPP_

//[description
/*`
prov_traits::destructive_provide is a facility for passing the logical arguments
that an ArgumentProvider object represents to an ArgumentReceiver's.

[note This /destructive/ form takes the ArgumentProvider as an rvalue and may
      put the ArgumentProvider into a valid-but-unspecified state. If the
      ArgumentProvider is a PersistentArgumentProvider and you wish you use
      provision of a form that keeps the ArgumentProvider in the same state, use
      prov_traits::persistent_provide instead.
]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_provider_to.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov_traits {

struct destructive_provide_fn
{
  template
  < class Provider, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentProviderTo< Provider, Receiver > )
    ()
  >
  constexpr decltype( auto )
  operator ()( Provider&& provider, Receiver&& rec ) const//=;
  //<-
  {
    return access_raw_concept_map< ArgumentProvider< Provider > >
    ::provide( ARGOT_MOVE( provider ), ARGOT_MOVE( rec ) );
  } //->
} inline constexpr destructive_provide{};

template< class Provider, class Receiver >
using result_of_destructive_provide//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< destructive_provide_fn const&, Provider, Receiver >; //->

template< class Provider, class Receiver >
using result_of_destructive_provide_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< destructive_provide_fn const&, Provider, Receiver >; //->

} // namespace (argot::prov_traits)

//]

#endif  // ARGOT_PROV_TRAITS_DESTRUCTIVE_PROVIDE_HPP_
