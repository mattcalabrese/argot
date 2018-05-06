/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_HIGHER_ORDER_EXPANDABLE_DETAIL_IS_HPP_
#define ARGOT_CONCEPTS_HIGHER_ORDER_EXPANDABLE_DETAIL_IS_HPP_

#include <argot/concepts/expandable.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>

namespace argot {
namespace higher_order_expandable_detail {

struct is_higher_order_expandable_impl_t {}
inline constexpr is_higher_order_expandable_impl{};

template< class T >
struct all_are_expandables_impl;

// TODO(mattcalabrese) Just check callability of prov_traits::provide
template< class... T >
struct all_are_expandables_impl
< receiver_traits::argument_types_t< T... > >
{
  static bool constexpr value
    = ( is_modeled_v< Expandable< T&& > > && ... );
};

// TODO(mattcalabrese) Do without type dispatch
template< class T >
bool constexpr all_are_expandables_v
  = all_are_expandables_impl< T >::value;

template< class T >
using is_higher_order_expandable_result
  = prov_traits::result_of_provide_t
    < decltype
      ( access_raw_concept_map< Expandable< T&& > >
        ::expand( ARGOT_DECLVAL( T&& ) )
      )
    , is_higher_order_expandable_impl_t
    >;

// TODO(mattcalabrese) First require that the top level is expandable
template< class T >
using is_higher_order_expandable_t
  = typename argot_detail::conditional
    < call_detail::is_detected_v
      < is_higher_order_expandable_result, T >
    >::template apply
    < call_detail::lazy_expand< is_higher_order_expandable_result, T >
    , std::false_type
    >::type;

template< class T >
struct is_higher_order_expandable
  : is_higher_order_expandable_t< T >{};

template< class T >
bool constexpr is_higher_order_expandable_v
  = is_higher_order_expandable_t< T >::value;

}  // namespace argot(::higher_order_expandable_detail)

template<>
struct make_concept_map
< ArgumentReceiver
  < higher_order_expandable_detail
    ::is_higher_order_expandable_impl_t
  >
>
{
  template< class... LeadingArgumentListKinds
          , class... TrailingArgumentListKinds
          , class... P
          >
  static constexpr
  std::bool_constant
  <    (    higher_order_expandable_detail
            ::all_are_expandables_v< LeadingArgumentListKinds >
         && ...
       )
    && (    higher_order_expandable_detail
            ::all_are_expandables_v< TrailingArgumentListKinds >
         && ...
       )
    && (    is_modeled_v< Expandable< P&& > >
         && ...
       )
  >
  receive_branch
  ( higher_order_expandable_detail
    ::is_higher_order_expandable_impl_t
  , receiver_traits::argument_list_kinds_t< LeadingArgumentListKinds... >
  , receiver_traits::argument_list_kinds_t< TrailingArgumentListKinds... >
  , P&&...
  ) noexcept
  {
    return {};
  }
};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_HIGHER_ORDER_EXPANDABLE_DETAIL_IS_HPP_
