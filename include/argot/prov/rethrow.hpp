/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_RETHROW_HPP_
#define ARGOT_PROV_RETHROW_HPP_

//[description
/*`
prov::rethrow is an ExceptionalPersistentArgumentProvider that executes a
`throw` expression during provision to rethrow the current exception that is
being handled.

[global_object_designator]
*/
//]

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct rethrow_t {} inline constexpr rethrow{};

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

template< >
struct make_concept_map< ArgumentProvider< prov::rethrow_t > >
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver >
  [[noreturn]] static ARGOT_REQUIRES( ArgumentReceiver< Receiver > )
  < impossible > provide( prov::rethrow_t /*self*/, Receiver&& /*rec*/ )
  {
    throw;
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< prov::rethrow_t > >
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver >
  [[noreturn]] static ARGOT_REQUIRES( ArgumentReceiver< Receiver > )
  < impossible > provide( prov::rethrow_t /*self*/, Receiver&& /*rec*/ )
  {
    throw;
  }
};

} // namespace argot

#endif  // ARGOT_PROV_RETHROW_HPP_
