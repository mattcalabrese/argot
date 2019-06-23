/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_0_CASES_HPP_
#define ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_0_CASES_HPP_

#include <argot/impossible.hpp>
#include <argot/concepts/switch_body_default.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/switch_/detail/switch_impl_fwd.hpp>
#include <argot/prov/switch_/detail/switch_provision_base.hpp>
#include <argot/prov/switch_/detail/switch_provision_fwd.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_persistent.hpp>
#include <argot/switch_traits/destructive_provide_default.hpp>
#include <argot/switch_traits/persistent_provide_default.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/unreachable_function.hpp>

namespace argot::prov::switch_detail {

// Terminal switch for 0 cases
template< provision_kind Kind >
struct switch_provision< 0, Kind >
  : switch_provision_base< Kind >
{
  using base_t = switch_provision_base< Kind >;

  template< class T >
  using with_qualifiers_t = typename base_t::template with_qualifiers_t< T >;

  using provide_default_t = typename base_t::provide_default_t;

  template< class Body, class ValueType >
  using argument_list_kinds_of_body_t
    = typename base_t
      ::template argument_list_kinds_of_body_t< Body, ValueType >;

  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES( ArgumentReceiver< Receiver > )()
  >
  static constexpr decltype( auto ) run
  ( with_qualifiers_t
    < prov::switch_detail::switch_impl< ValueType, Bodies... > > self
  , Receiver&& receiver
  )
  {
    using body_t
      = typename prov::switch_detail::switch_impl< ValueType, Bodies... >
        ::body_t;

    using qualified_body_t = with_qualifiers_t< body_t >;

    if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
      switch( self.value )
      {
       default:
        return provide_default_t()
        ( static_cast< qualified_body_t >( self.body ), self.value
        , ARGOT_FORWARD( Receiver )( receiver )
        );
      }
    else
    {
      switch( self.value ) {}
      return unreachable_function< impossible >();
    }
  }
};

}  // namespace (argot::prov::switch_detail)

#endif  // ARGOT_PROV_SWITCH_DETAIL_SWITCH_PROVISION_0_CASES_HPP_
