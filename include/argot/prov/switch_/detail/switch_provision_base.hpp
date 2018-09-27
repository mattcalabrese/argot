/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_BASE_HPP_
#define ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_BASE_HPP_

#include <argot/prov/switch_/detail/provision_kind.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_persistent.hpp>
#include <argot/switch_traits/destructive_provide_case.hpp>
#include <argot/switch_traits/destructive_provide_default.hpp>
#include <argot/switch_traits/persistent_provide_case.hpp>
#include <argot/switch_traits/persistent_provide_default.hpp>

namespace argot::prov::switch_detail {

template< provision_kind Kind >
struct switch_provision_base;

template<>
struct switch_provision_base< provision_kind::destructive >
{
  template< class T >
  using with_qualifiers_t = T&&;

  template< auto V >
  using provide_case_t = switch_traits::destructive_provide_case_t< V >;

  using provide_default_t = switch_traits::destructive_provide_default_t;

  template< class Body, class ValueType >
  using argument_list_kinds_of_body_t
    = switch_traits::argument_list_kinds_of_body_destructive_t
      < Body, ValueType >;
};

template<>
struct switch_provision_base< provision_kind::persistent >
{
  template< class T >
  using with_qualifiers_t = T const&;

  template< auto V >
  using provide_case_t = switch_traits::persistent_provide_case_t< V >;

  using provide_default_t = switch_traits::persistent_provide_default_t;

  template< class Body, class ValueType >
  using argument_list_kinds_of_body_t
    = switch_traits::argument_list_kinds_of_body_persistent_t
      < Body, ValueType >;
};

} // namespace (argot::prov::switch_detail)

#endif  // ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_BASE_HPP_
