/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_RETURN_ARGUMENT_LIST_KINDS_HPP_
#define ARGOT_RECEIVER_RETURN_ARGUMENT_LIST_KINDS_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

namespace argot {
namespace receiver {

struct return_argument_list_kinds_t
{
  struct impl {};

  constexpr impl operator ()() const { return {}; }
} inline constexpr return_argument_list_kinds{};

using result_of_return_argument_list_kinds_t
  = return_argument_list_kinds_t::impl;

struct result_of_return_argument_list_kinds
{
  using type = result_of_return_argument_list_kinds_t;
};

} // namespace argot(::receiver)

template <>
struct make_concept_map
< ArgumentReceiver< receiver::return_argument_list_kinds_t::impl > >
{
  // TODO(mattcalabrese) Constrain
  template< class... LeadingArgumentLists
          , class... TrailingArgumentLists
          , class... P
          >
  static constexpr receiver_traits::argument_list_kinds_t
  < LeadingArgumentLists...
  , receiver_traits::argument_types_t< P&&... >
  , TrailingArgumentLists...
  >
  receive_branch
  ( receiver::return_argument_list_kinds_t::impl
  , receiver_traits::argument_list_kinds_t< LeadingArgumentLists... >
  , receiver_traits::argument_list_kinds_t< TrailingArgumentLists... >
  , P&&...
  )
  {
    return {};
  }
};

} // namespace argot

#endif  // ARGOT_RECEIVER_RETURN_ARGUMENT_LIST_KINDS_HPP_
