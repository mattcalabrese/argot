/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_CONSTRUCTIBLE_WITH_EACH_HPP_
#define ARGOT_CONCEPTS_CONSTRUCTIBLE_WITH_EACH_HPP_

#include <argot/concepts/argument_types.hpp>
#include <argot/concepts/constructible.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_types.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace constructible_with_each_detail {

template< class T, class ArgumentTypes >
struct constructible_with_argument_types {};

template< class T, class... P >
struct constructible_with_argument_types
< T
, receiver_traits::argument_types_t< P... >
>
{
  template< template< class... > class Req >
  using expand_requirements = Req< Constructible< T, P... > >;
};

template< class T, class... ArgumentListKinds >
struct constructible_with_each_impl
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < ArgumentTypes< ArgumentListKinds >...
      , TransparentRequirement
        < constructible_with_argument_types< T, ArgumentListKinds > >...
      >;
};

} // namespace argot(::constructible_with_each_detail)

template< class T, class... ArgumentListKinds >
using ConstructibleWithEach
  = TransparentRequirement
    < constructible_with_each_detail::constructible_with_each_impl
      < T, ArgumentListKinds... >
    >;

} // namespace argot

#endif  // ARGOT_CONCEPTS_CONSTRUCTIBLE_WITH_EACH_HPP_
