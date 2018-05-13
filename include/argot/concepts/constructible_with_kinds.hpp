/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_CONSTRUCTIBLE_WITH_KINDS_HPP_
#define ARGOT_CONCEPTS_CONSTRUCTIBLE_WITH_KINDS_HPP_

#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/constructible_with_each.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_list_kinds.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace constructible_with_kinds_detail {

template< class T, class Kinds >
struct constructible_with_kinds_impl_impl {};

template< class T, class... Kinds >
struct constructible_with_kinds_impl_impl
< T
, receiver_traits::argument_list_kinds_t< Kinds... >
>
{
  template< template< class... > class Req >
  using expand_requirements = Req< ConstructibleWithEach< T, Kinds... > >;
};

template< class T, class Kinds >
struct constructible_with_kinds_impl
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < ArgumentListKinds< Kinds >
      , TransparentRequirement
        < constructible_with_kinds_impl_impl< T, Kinds > >
      >;
};

}  // namespace argot(::constructible_with_kinds_detail)

template< class T, class Kinds >
using ConstructibleWithKinds
  = TransparentRequirement
    < constructible_with_kinds_detail
      ::constructible_with_kinds_impl< T, Kinds >
    >;

}  // namespace argot

#endif  // ARGOT_CONCEPTS_CONSTRUCTIBLE_WITH_KINDS_HPP_
