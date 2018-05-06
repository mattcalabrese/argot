/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_KINDS_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_KINDS_HPP_

#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_list_kinds.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace argument_receiver_of_kinds_detail {

template< class Receiver, class ArgListKinds >
struct argument_receiver_of_kinds_impl {};

template< class Receiver, class... ArgListKinds >
struct argument_receiver_of_kinds_impl
< Receiver, receiver_traits::argument_list_kinds_t< ArgListKinds... > >
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< ArgumentReceiverOf< Receiver, ArgListKinds... > >;
};

template< class Receiver, class ArgListKinds >
struct argument_receiver_of_kinds
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< ArgumentListKinds< ArgListKinds >
         , TransparentRequirement
           < argument_receiver_of_kinds_impl< Receiver, ArgListKinds > >
         >;
};

}  // namespace argot(::argument_receiver_of_kinds_detail)

template< class Receiver, class ArgListKinds >
using ArgumentReceiverOfKinds
  = TransparentRequirement
    < argument_receiver_of_kinds_detail
      ::argument_receiver_of_kinds< Receiver, ArgListKinds >
    >;

}  // namespace argot

#endif  // ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_KINDS_HPP_
