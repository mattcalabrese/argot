/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_
#define ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_

#include <argot/impossible.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace switch_traits {
namespace argument_list_kinds_of_default_persistent_detail {

template< class Body, class ValueType >
using explicit_argument_list_kinds_of_t
  = typename access_raw_concept_map
    < PersistentSwitchBodyDefaultForType< Body, ValueType > >
    ::argument_list_kinds_of_default_persistent_t;

template< class Body, class ValueType >
struct explicit_argument_list_kinds_of
{
  using type = explicit_argument_list_kinds_of_t< Body, ValueType >;
};

template< class Body, class ValueType >
struct deduce_argument_list_kinds_of
{
 private:
  using detected_result_type
    = decltype
      ( access_raw_concept_map
        < PersistentSwitchBodyDefaultForType< Body, ValueType > >
        ::provide_isolated_default
        ( ARGOT_DECLVAL( Body const& )
        , ARGOT_DECLVAL( ValueType )
        , ARGOT_DECLVAL( receiver::result_of_return_argument_list_kinds_t )
        )
      );
 public:
  using type
    = typename argot_detail::conditional
      < std::is_same_v< detected_result_type, impossible > >
      ::template apply
      < receiver_traits::argument_list_kinds_t<>
      , detected_result_type
      >;
};

} // namespace
   // argot::switch_traits(::argument_list_kinds_of_default_persistent_detail)

template< class Body, class ValueType >
using argument_list_kinds_of_default_persistent_t
  = ARGOT_REQUIRES( PersistentSwitchBodyDefaultForType< Body, ValueType > )
    < typename argot_detail::conditional
      < call_detail::is_detected_v
        < argument_list_kinds_of_default_persistent_detail
          ::explicit_argument_list_kinds_of_t
        , Body
        , ValueType
        >
      >::template apply
      < argument_list_kinds_of_default_persistent_detail
        ::explicit_argument_list_kinds_of< Body, ValueType >
      , argument_list_kinds_of_default_persistent_detail
        ::deduce_argument_list_kinds_of< Body, ValueType >
      >::type
    >;

template< class Body >
using argument_list_kinds_of_default_persistent
  = call_detail::lazy_expand
    < argument_list_kinds_of_default_persistent_t, Body >;

// TODO(mattcalabrese) Pass ValueType
template< class Body, class ValueType >
argument_list_kinds_of_default_persistent_t< Body, ValueType > constexpr
argument_list_kinds_of_default_persistent_v{};

} // namespace argot(::switch_traits)

} // namespace argot

#endif  // ARGOT_SWITCH_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_
