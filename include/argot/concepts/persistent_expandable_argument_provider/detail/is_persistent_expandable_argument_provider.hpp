/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_OF_EXPANDABLES_DETAIL_IS_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_OF_EXPANDABLES_DETAIL_IS_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/expandable.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>

namespace argot {
namespace persistent_expandable_argument_provider_detail {

struct is_persistent_expandable_argument_provider_impl_t {}
inline constexpr is_persistent_expandable_argument_provider_impl{};

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

template< class T >
bool constexpr all_are_expandables_v
  = all_are_expandables_impl< T >::value;

template< class T >
using is_persistent_expandable_argument_provider_result
  = prov_traits
    ::result_of_provide_t
    < T, is_persistent_expandable_argument_provider_impl_t >;

template< class T >
using is_persistent_expandable_argument_provider_t
  = typename argot_detail::conditional
    < call_detail::is_detected_v
      < is_persistent_expandable_argument_provider_result, T >
    >::template apply
    < call_detail::lazy_expand
      < is_persistent_expandable_argument_provider_result, T >
    , std::false_type
    >::type;

template< class T >
struct is_persistent_expandable_argument_provider
  : is_persistent_expandable_argument_provider_t< T >{};

template< class T >
bool constexpr is_persistent_expandable_argument_provider_v
  = is_persistent_expandable_argument_provider_t< T >::value;

}  // namespace argot(::persistent_expandable_argument_provider_detail)

template<>
struct make_concept_map
< ArgumentReceiver
  < persistent_expandable_argument_provider_detail
    ::is_persistent_expandable_argument_provider_impl_t
  >
>
{
  template< class... LeadingArgumentListKinds
          , class... TrailingArgumentListKinds
          , class... P
          >
  static constexpr
  std::bool_constant
  <    (    persistent_expandable_argument_provider_detail
            ::all_are_expandables_v< LeadingArgumentListKinds >
         && ...
       )
    && (    persistent_expandable_argument_provider_detail
            ::all_are_expandables_v< TrailingArgumentListKinds >
         && ...
       )
    && (    is_modeled_v< Expandable< P&& > >
         && ...
       )
  >
  receive_branch
  ( persistent_expandable_argument_provider_detail
    ::is_persistent_expandable_argument_provider_impl_t
  , receiver_traits::argument_list_kinds_t< LeadingArgumentListKinds... >
  , receiver_traits::argument_list_kinds_t< TrailingArgumentListKinds... >
  , P&&...
  ) noexcept
  {
    return {};
  }
};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_ARGUMENT_PROVIDER_OF_EXPANDABLES_DETAIL_IS_HPP_
