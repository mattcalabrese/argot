/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_EXIT_HPP_
#define ARGOT_PROV_EXIT_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/remove_cvref.hpp>

#include <cstdlib>

namespace argot {
namespace prov {

struct exit_fn
{
  struct impl
  {
    int exit_value;
  };

  constexpr auto operator()( int exit_value ) const
  {
    return impl{ exit_value };
  }
} inline constexpr exit{};

}  // namespace argot(::prov)

template<>
struct make_concept_map< ArgumentProvider< prov::exit_fn::impl > >
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible provide
  ( prov::prov::exit_fn::impl self, Receiver&& /*receiver*/ ) noexcept
  {
    std::exit( self.exit_value );
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< prov::exit_fn::impl > >
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible provide
  ( prov::prov::exit_fn::impl self, Receiver&& /*receiver*/ ) noexcept
  {
    std::exit( self.exit_value );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_EXIT_HPP_
