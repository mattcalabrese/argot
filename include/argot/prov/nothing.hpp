/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_NOTHING_HPP_
#define ARGOT_PROV_NOTHING_HPP_

//[description
/*`
prov::nothing is a PersistentArgumentProvider of an empty argument list.

[global_object_designator]
*/
//]

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct nothing_t {} inline constexpr nothing{};

} // namespace (argot::prov)

/*`
[provider_properties_heading]

[table Provider
 [[Property][Description]]
 [[Logical Provision][Empty argument list]]
 [[Possible Argument Types]
  [[itemized_list [```()```]]]
 ]
]
*/

//]

namespace argot {

template<>
struct make_concept_map< ArgumentProvider< prov::nothing_t > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf< Receiver, receiver_traits::argument_types_t<> > )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::nothing_t /*self*/, Receiver&& receiver )
  {
    return receiver_traits::receive( ARGOT_MOVE( receiver ) );
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< prov::nothing_t > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf< Receiver, receiver_traits::argument_types_t<> > )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::nothing_t /*self*/, Receiver&& receiver )
  {
    return receiver_traits::receive( ARGOT_MOVE( receiver ) );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_NOTHING_HPP_
