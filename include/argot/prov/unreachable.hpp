/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_UNREACHABLE_HPP_
#define ARGOT_PROV_UNREACHABLE_HPP_

//[description
/*`
prov::unreachable is an ExceptionalPersistentArgumentProvider for which it is
undefined behavior to undergo provision. Its primary use is when working with 
higher-order ArgumentProviders that branch and where one or more branches cannot
be logically reached, such as by precondition.

[note Prior to reaching an operation whose execution would be undefined, this
      facility expands `BOOST_ASSERT( false )`. For users who wish to avoid any
      chance of undefined behavior by way of prov::unreachable, make sure that
      `BOOST_ASSERT` is setup appropriately.
]

[global_object_designator]
*/
//]

#include <argot/impossible.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/rvalue_reference.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct unreachable_t {} inline constexpr unreachable{};

} // namespace (argot::prov)

/*`
[provider_properties_heading]

[table Provider
 [[Property][Description]]
 [[Logical Provision][No provision]]
 [[Possible Argument Types][]]
]
*/

//]

namespace argot {

template<>
struct make_concept_map< ArgumentProvider< prov::unreachable_t > >
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver >
  [[noreturn]]
  static ARGOT_REQUIRES( ArgumentReceiver< Receiver > )
  < impossible > constexpr provide
  ( prov::unreachable_t /*self*/, Receiver&& receiver )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< prov::unreachable_t > >
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver >
  [[noreturn]]
  static ARGOT_REQUIRES( ArgumentReceiver< Receiver > )
  < impossible > constexpr provide
  ( prov::unreachable_t /*self*/, Receiver&& receiver )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

} // namespace argot

#endif  // ARGOT_PROV_UNREACHABLE_HPP_
