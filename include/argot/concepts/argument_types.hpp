/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_TYPES_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_TYPES_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/instantiation_of.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_types.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace argument_types_concept_detail {

template< class ArgTypes >
struct valid_argument_types {};

template< class... P >
struct valid_argument_types< receiver_traits::argument_types_t< P... > >
{
  template< template< class... > class Req >
  using expand_requirements = Req< Reference< P >... >;
};

template< class ArgTypes >
struct argument_types_impl
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< InstantiationOf< receiver_traits::argument_types_t, ArgTypes >
         , TransparentRequirement< valid_argument_types< ArgTypes > >
         >;
};

} // namespace argot(::argument_types_concept_detail)

template< class ArgTypes >
using ArgumentTypes
  = TransparentRequirement
    < argument_types_concept_detail::argument_types_impl< ArgTypes > >;

} // namespace argot

#endif  // ARGOT_CONCEPTS_ARGUMENT_TYPES_HPP_
