/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_BOOST_ASSERT_HPP_
#define ARGOT_PROV_BOOST_ASSERT_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/remove_cvref.hpp>

#include <boost/assert.hpp>

namespace argot {
namespace prov {

struct boost_assert_t {} inline constexpr boost_assert{};

}  // namespace argot(::prov)

template<>
struct make_concept_map< ArgumentProvider< prov::boost_assert_t > >
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible
  provide( prov::boost_assert_t /*self*/, Receiver&& /*receiver*/ ) noexcept
  {
    BOOST_ASSERT( false );
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< prov::boost_assert_t > >
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver, ARGOT_REQUIRES( ArgumentReceiver< Receiver > )() >
  [[noreturn]] static impossible
  provide( prov::boost_assert_t /*self*/, Receiver&& /*receiver*/ ) noexcept
  {
    BOOST_ASSERT( false );
    ARGOT_DETAIL_UNREACHABLE();
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_BOOST_ASSERT_HPP_
