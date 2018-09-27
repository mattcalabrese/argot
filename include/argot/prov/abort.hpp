/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ABORT_HPP_
#define ARGOT_PROV_ABORT_HPP_

//[description
/*`
prov::abort is an ExceptionalPersistentArgumentProvider that calls `std::abort`
when provision takes place. One potential use is in an argot::default_ argument
of a call to prov::switch_.

[global_object_designator]
*/
//]

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <cstdlib>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct abort_t {} inline constexpr abort{};

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
struct make_concept_map< ArgumentProvider< prov::abort_t > >
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible
  provide( prov::abort_t /*self*/, Receiver&& /*receiver*/ ) noexcept
  {
    std::abort();
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< prov::abort_t > >
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible
  provide( prov::abort_t /*self*/, Receiver&& /*receiver*/ ) noexcept
  {
    std::abort();
  }
};

} // namespace argot

#endif  // ARGOT_PROV_ABORT_HPP_
