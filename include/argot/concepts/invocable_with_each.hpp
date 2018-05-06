/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_INVOCABLE_WITH_EACH_HPP_
#define ARGOT_CONCEPTS_INVOCABLE_WITH_EACH_HPP_

#include <argot/concepts/argument_types.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_types.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace invocable_with_each_detail {

template< class Invocable, class ArgumentTypes >
struct invocable_with_argument_types {};

template< class Invocable, class... P >
struct invocable_with_argument_types
< Invocable
, receiver_traits::argument_types_t< P... >
>
{
  template< template< class... > class Req >
  using expand_requirements = Req< InvocableWith< Invocable, P... > >;
};

template< class Invocable, class... ArgumentListKinds >
struct invocable_with_each_impl
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < ArgumentTypes< ArgumentListKinds >...
      , TransparentRequirement
        < invocable_with_argument_types< Invocable, ArgumentListKinds > >...
      >;
};

}  // namespace argot(::invocable_with_each_detail)

template< class Invocable, class... ArgumentListKinds >
using InvocableWithEach
  = TransparentRequirement
    < invocable_with_each_detail::invocable_with_each_impl
      < Invocable, ArgumentListKinds... >
    >;

}  // namespace argot

#endif  // ARGOT_CONCEPTS_INVOCABLE_WITH_EACH_HPP_
