/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_HPP_
#define ARGOT_PROV_SWITCH_HPP_

//[description
/*`
prov::switch_ is a facility for expressing switch-like control flow during
argument provision.

[global_function_object_designator]
*/
//]

// TODO(mattcalabrese) Remove unnecessary includes.
#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/persistent_switch_body_for_type.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switchable.hpp>
#include <argot/concepts/unhandled_switchable_value.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/switch_/detail/provision_kind.hpp>
#include <argot/prov/switch_/detail/switch_impl_fwd.hpp>
#include <argot/prov/switch_/detail/switch_provision.hpp>
#include <argot/prov/unreachable.hpp>
#include <argot/switch_traits/combine.hpp>
#include <argot/switch_traits/num_cases.hpp>
#include <argot/switch_traits/provider_of_isolated.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {
//<-
namespace switch_detail {

template< class ValueType, class... Bodies >
struct switch_impl
{
  ARGOT_CONCEPT_ASSERT( Switchable< ValueType, Bodies... > );

  using body_t = switch_traits::result_of_combine_t< Bodies... >;

  ARGOT_NO_UNIQUE_ADDRESS ValueType value;
  ARGOT_NO_UNIQUE_ADDRESS body_t body;
};

} // namespace argot::prov(::switch_detail)
//->

struct switch_fn
{
  // TODO(mattcalabrese) Special-case the simple cases, like with group.
  template< class ValueType, class... Bodies
          , ARGOT_REQUIRES
            ( Switchable
              < ValueType, detail_argot::remove_cvref_t< Bodies >... >
            )
            ( Sinkable< Bodies&& >... )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( ValueType const value, Bodies&&... bodies ) const//=;
  //<-
  {
    if constexpr( is_modeled_v< StdIntegralConstant< ValueType > > )
    {
      bool constexpr is_unhandled_case_with_no_default
        = is_modeled_v
          < UnhandledSwitchableValue
            < ValueType::value, detail_argot::remove_cvref_t< Bodies >... >
          >;

      if constexpr( is_unhandled_case_with_no_default )
        return switch_on_std_integral_constant_reaches_implicit_default
        < is_unhandled_case_with_no_default >();
      else
        return unhandled_switchable_value_detail
        ::nary_provider_of_isolated< ValueType::value >
        ( unhandled_switchable_value_detail
          ::unhandled_with_no_explicit_default_t()
        , call_detail::forward_and_sink< Bodies >( bodies )...
        );
    }
    else
      return switch_detail::switch_impl
      < ValueType, detail_argot::remove_cvref_t< Bodies >... >
      { value
      , switch_traits::combine
        ( call_detail::forward_and_sink< Bodies >( bodies )... )
      };
  }
 private:
  template< bool /*ForceDependence*/ >
  [[deprecated
    ( "argot::prov::switch_ was called with a std::integral_constant of a "
      "value that does not match any case labels. Since the corresponding "
      "SwitchBody does not have an explicit default, this call returns a "
      "provider for which provision is unreachable. If that behavior is "
      "intended, prefer explicitly specifying 'argot::default_.unreachable' as "
      "an argument to argot::prov::switch_."
    )
  ]]
  static constexpr prov::unreachable_t
  switch_on_std_integral_constant_reaches_implicit_default()
  {
    return prov::unreachable;
  } //->
} inline constexpr switch_{};

template< class ValueType, class... Bodies >
using result_of_switch//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< switch_fn const&, ValueType, Bodies... >; //->

template< class ValueType, class... Bodies >
using result_of_switch_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< switch_fn const&, ValueType, Bodies... >; //->

} // namespace (argot::prov)

//]

namespace argot {

template< class ValueType, class... Bodies >
struct make_concept_map
< ArgumentProvider
  < prov::switch_detail::switch_impl< ValueType, Bodies... > >
>
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , switch_traits::argument_list_kinds_of_body_destructive_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
  static constexpr decltype( auto ) provide
  ( prov::switch_detail::switch_impl< ValueType, Bodies... >&& self
  , Receiver&& receiver
  )
  {
    return prov::switch_detail::switch_provision
    < (   switch_traits::num_cases_v< detail_argot::remove_cvref_t< Bodies > >
        + ...
        + std::size_t{ 0 }
      )
    , prov::switch_detail::provision_kind::destructive
    >::run( ARGOT_MOVE( self ), ARGOT_FORWARD( Receiver )( receiver ) );
  }
};

template< class ValueType, class... Bodies >
struct make_concept_map
< PersistentArgumentProvider
  < prov::switch_detail::switch_impl< ValueType, Bodies... > >
, ARGOT_REQUIRES( PersistentSwitchBodyForType< Bodies, ValueType >... )<>
>
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , switch_traits::argument_list_kinds_of_body_persistent_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
  static constexpr decltype( auto ) provide
  ( prov::switch_detail::switch_impl< ValueType, Bodies... > const& self
  , Receiver&& receiver
  )
  {
    return prov::switch_detail::switch_provision
    < (   switch_traits::num_cases_v< detail_argot::remove_cvref_t< Bodies > >
        + ...
        + std::size_t{ 0 }
      )
    , prov::switch_detail::provision_kind::persistent
    >::run( self, ARGOT_FORWARD( Receiver )( receiver ) );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_SWITCH_HPP_
