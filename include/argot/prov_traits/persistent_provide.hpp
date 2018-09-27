/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TRAITS_PERSISTENT_PROVIDE_HPP_
#define ARGOT_PROV_TRAITS_PERSISTENT_PROVIDE_HPP_

//[description
/*`
prov_traits::persistent_provide is a facility for passing the logical arguments
that a PersistentArgumentProvider object represents to an ArgumentReceiver's.

[note This /persistent/ form takes the ArgumentProvider as a `const` lvalue and
      leaves the ArgumentProvider in logically the same state as it was prior to
      the invocation. If you do not need the ArgumentProvider after this call,
      you should prefer to use prov_traits::destructive_provide instead, which
      in some cases may lead to more optimal execution (such as by passing
      rvalues in its represented argument list as opposed to lvalues).
]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider_to.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

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
  operator ()( Provider const& provider, Receiver&& receiver ) const//=;
  //<-
  {
    return access_raw_concept_map< PersistentArgumentProvider< Provider > >
    ::provide( provider, static_cast< Receiver&& >( receiver ) );
  } //->
} inline constexpr persistent_provide{};

template< class Provider, class Receiver >
using result_of_persistent_provide//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< persistent_provide_t const&, Provider&&, Receiver&& >; //->

template< class Provider, class Receiver >
using result_of_persistent_provide_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< persistent_provide_t const&, Provider&&, Receiver&& >; //->

} // namespace (argot::prov_traits)

//]

#endif  // ARGOT_PROV_TRAITS_PERSISTENT_PROVIDE_HPP_
