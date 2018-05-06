/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_LIST_KINDS_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_LIST_KINDS_HPP_

#include <argot/concepts/argument_types.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/instantiation_of.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_list_kinds.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace argument_list_kinds_concept_detail {

template< class Kinds >
struct valid_kinds {};

template< class... Kinds >
struct valid_kinds< receiver_traits::argument_list_kinds_t< Kinds... > >
{
  template< template< class... > class Req >
  using expand_requirements = Req< ArgumentTypes< Kinds >... >;
};

template< class Kinds >
struct argument_list_kinds_impl
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< InstantiationOf< receiver_traits::argument_list_kinds_t, Kinds >
         , TransparentRequirement< valid_kinds< Kinds > >
         >;
};

}  // namespace argot(::argument_list_kinds_concept_detail)

template< class Kinds >
using ArgumentListKinds
  = TransparentRequirement
    < argument_list_kinds_concept_detail::argument_list_kinds_impl< Kinds > >;

}  // namespace argot

#endif  // ARGOT_CONCEPTS_ARGUMENT_LIST_KINDS_HPP_
