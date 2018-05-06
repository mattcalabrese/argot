/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_TRAITS_ARGUMENT_LIST_KINDS_HPP_
#define ARGOT_RECEIVER_TRAITS_ARGUMENT_LIST_KINDS_HPP_

#include <argot/concepts/argument_types.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver_traits/argument_types.hpp>

namespace argot {
namespace receiver_traits {

template< class... P >
struct argument_list_kinds_t
{
  ARGOT_CONCEPT_ASSERT( ArgumentTypes< P >... );
};

// TODO(mattcalabrese) Use
template< class... P >
constexpr
ARGOT_REQUIRES( ArgumentTypes< P >... )
< argument_list_kinds_t< P... > >
argument_list_kinds( P... ) noexcept { return {}; };

// TODO(mattcalabrese) Constrain these.

template< class... TypeLists >
struct concatenate_argument_list_kinds;

template< class... TypeLists >
using concatenate_argument_list_kinds_t
  = typename concatenate_argument_list_kinds< TypeLists... >::type;

template<>
struct concatenate_argument_list_kinds<>
{
  using type = argument_list_kinds_t<>;
};

template< class... T >
struct concatenate_argument_list_kinds< argument_list_kinds_t< T... > >
{
  using type = argument_list_kinds_t< T... >;
};

template< class... FirstTypes, class...SecondTypes
        , class... TailTypeLists
        >
struct concatenate_argument_list_kinds
       < argument_list_kinds_t< FirstTypes... >
       , argument_list_kinds_t< SecondTypes... >
       , TailTypeLists...
       >
{
  using type
    = typename concatenate_argument_list_kinds
      < argument_list_kinds_t< FirstTypes..., SecondTypes... >
      , TailTypeLists...
      >::type;
};

}  // namespace argot::receiver_traits
}  // namespace argot

#endif  // ARGOT_RECEIVER_TRAITS_ARGUMENT_LIST_KINDS_HPP_
