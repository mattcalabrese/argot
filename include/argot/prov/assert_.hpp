/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ASSERT_HPP_
#define ARGOT_PROV_ASSERT_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <cassert>

namespace argot {
namespace prov {

struct assert_t {} inline constexpr assert_{};

}  // namespace argot(::prov)

template<>
struct make_concept_map< ArgumentProvider< prov::assert_t > >
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible
  provide( prov::assert_t /*self*/, Receiver&& /*receiver*/ ) noexcept
  {
    assert( false );
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< prov::assert_t > >
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible
  provide( prov::assert_t /*self*/, Receiver&& /*receiver*/ ) noexcept
  {
    assert( false );
    ARGOT_DETAIL_UNREACHABLE();
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_ASSERT_HPP_
