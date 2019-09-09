/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_TRAITS_ARGUMENT_TYPES_HPP_
#define ARGOT_RECEIVER_TRAITS_ARGUMENT_TYPES_HPP_

#include <cstddef>
#include <type_traits>

namespace argot {
namespace receiver_traits {

template< class... Arguments >
struct argument_types_t
{
  static_assert( ( std::is_reference_v< Arguments > && ... ) );

  static constexpr std::size_t length_v = sizeof...( Arguments );
};

template< class... Arguments >
argument_types_t< Arguments... > constexpr argument_types{};

// TODO(mattcalabrese) Possibly remove these (are they used?)
template< class... ArgumentTypeLists >
struct combine_argument_types;

template<>
struct combine_argument_types<>
{
  using type = argument_types_t<>;
};

template< class... ArgumentTypes >
struct combine_argument_types< argument_types_t< ArgumentTypes... > >
{
  using type = argument_types_t< ArgumentTypes... >;
};

template< class... FirstArgumentTypes, class... NextArgumentTypes
        , class... TrailingArgumentTypeLists
        >
struct combine_argument_types
< argument_types_t< FirstArgumentTypes... >
, argument_types_t< NextArgumentTypes... >
, TrailingArgumentTypeLists...
>
{
  using type
    = typename combine_argument_types
      < argument_types_t< FirstArgumentTypes..., NextArgumentTypes... >
      , TrailingArgumentTypeLists...
      >::type;
};

template< class... ArgumentTypeLists >
using combine_argument_types_t
  = typename combine_argument_types< ArgumentTypeLists... >::type;

} // namespace argot::receiver_traits
} // namespace argot

#endif  // ARGOT_RECEIVER_TRAITS_ARGUMENT_TYPES_HPP_
