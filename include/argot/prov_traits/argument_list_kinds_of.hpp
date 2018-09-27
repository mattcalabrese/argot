/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_HPP_
#define ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>

#include <type_traits>

namespace argot::prov_traits {

// TODO(mattcalabrese) Possibly handle const rvalues as persistent
template< class Provider >
using argument_list_kinds_of_t
  = ARGOT_REQUIRES
    ( typename argot_detail::conditional
      < std::is_rvalue_reference_v< Provider&& > >
      ::template apply
      < ArgumentProvider< std::remove_reference_t< Provider > >
      , PersistentArgumentProvider
        < std::remove_const_t< std::remove_reference_t< Provider > > >
      >
    )
    < typename argot_detail::conditional
      < std::is_rvalue_reference_v< Provider&& > >
      ::template apply
      < argument_list_kinds_of_destructive
        < std::remove_reference_t< Provider > >
      , argument_list_kinds_of_persistent
        < std::remove_const_t< std::remove_reference_t< Provider > > >
      >::type
    >;

template< class Provider >
using argument_list_kinds_of
  = call_detail::lazy_expand< argument_list_kinds_of_t, Provider >;

template< class Provider >
argument_list_kinds_of_t< Provider > constexpr
argument_list_kinds_of_v{};

} // namespace (argot::prov_traits)

#endif  // ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_HPP_
