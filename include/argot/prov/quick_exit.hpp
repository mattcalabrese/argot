/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_QUICK_EXIT_HPP_
#define ARGOT_PROV_QUICK_EXIT_HPP_

//[description
/*`
prov::quick_exit is a function object that takes an `int` exit status as a
parameter and returns an ExceptionalPersistentArgumentProvider that calls
`std::quick_exit` with the exit status when provision takes place.

[global_function_object_designator]
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

struct quick_exit_fn
{
  //<-
  struct impl
  {
    int exit_code;
  };
  //->
  [[nodiscard]]
  constexpr auto operator()( int exit_code ) const noexcept//=;
  //<-
  {
    return impl{ exit_code };
  } //->
} inline constexpr quick_exit{};

using result_of_quick_exit//= = ``[see_prologue_result_of]``;
//<-
  = quick_exit_fn::impl; //->

using result_of_quick_exit_t//= = ``[see_prologue_result_of]``;
//<-
  = quick_exit_fn::impl; //->

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`int exit_code`][A valid exit status]
  [The value to be passed to `std::quick_exit` during provision]
 ]
]

[provider_properties_heading]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision][No provision]]
 [[Possible Argument Types][]]
]
*/

//]

namespace argot {

template<>
struct make_concept_map< ArgumentProvider< prov::quick_exit_fn::impl > >
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible provide
  ( prov::quick_exit_fn::impl self, Receiver&& /*receiver*/ ) noexcept
  {
    std::quick_exit( self.exit_code );
  }
};

template<>
struct make_concept_map
< PersistentArgumentProvider< prov::quick_exit_fn::impl > >
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible provide
  ( prov::quick_exit_fn::impl self, Receiver&& /*receiver*/ ) noexcept
  {
    std::quick_exit( self.exit_code );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_QUICK_EXIT_HPP_
