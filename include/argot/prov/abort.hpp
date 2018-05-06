/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ABORT_HPP_
#define ARGOT_PROV_ABORT_HPP_

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

struct abort_t {} inline constexpr abort{};

}  // namespace argot(::prov)

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

}  // namespace argot

#endif  // ARGOT_PROV_ABORT_HPP_
