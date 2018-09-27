/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_TRAITS_PROVIDER_TYPES_HPP_
#define ARGOT_RECEIVER_TRAITS_PROVIDER_TYPES_HPP_

#include <argot/detail/concatenate.hpp>
#include <argot/prov_traits/argument_list_kinds_of.hpp>

namespace argot {
namespace receiver_traits {

// TODO(mattcalabrese) SFINAE for providers only.
template< class... Providers >
struct provider_types_t {};

template< class... Providers >
inline provider_types_t< Providers... > constexpr provider_types{};

template< class... ProviderTypeLists >
struct combine_provider_types;

template<>
struct combine_provider_types<>
{
  using type = provider_types_t<>;
};

template< class... ProviderTypes >
struct combine_provider_types< provider_types_t< ProviderTypes... > >
{
  using type = provider_types_t< ProviderTypes... >;
};

template< class... FirstProviderTypes, class... NextProviderTypes
        , class... TrailingProviderTypeLists
        >
struct combine_provider_types
< provider_types_t< FirstProviderTypes... >
, provider_types_t< NextProviderTypes... >
, TrailingProviderTypeLists...
>
{
  using type
    = typename combine_provider_types
      < provider_types_t< FirstProviderTypes..., NextProviderTypes... >
      , TrailingProviderTypeLists...
      >::type;
};

template< class... ProviderTypeLists >
using combine_provider_types_t
  = typename combine_provider_types< ProviderTypeLists... >::type;

template< class T >
struct argument_list_kinds_of_provider_types {};

template< class... Providers >
struct argument_list_kinds_of_provider_types< provider_types_t< Providers... > >
{
  using type
    = call_detail::concatenate_t
      < prov_traits::argument_list_kinds_of_t< Providers >... >;
};

template< class T >
using argument_list_kinds_of_provider_types_t
  = typename argument_list_kinds_of_provider_types< T >::type;

} // namespace argot::receiver_traits
} // namespace argot

#endif  // ARGOT_RECEIVER_TRAITS_PROVIDER_TYPES_HPP_
