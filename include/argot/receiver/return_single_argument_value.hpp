/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_RETURN_SINGLE_ARGUMENT_VALUE_HPP_
#define ARGOT_RECEIVER_RETURN_SINGLE_ARGUMENT_VALUE_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/sink.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>
#include <utility>
#include <variant>

namespace argot {
namespace receiver {

struct return_single_argument_value_t
{
  struct impl {};

  constexpr impl operator()() const { return {}; }
} inline constexpr return_single_argument_value{};

using result_of_return_single_argument_value_t
  = return_single_argument_value_t::impl;

struct result_of_return_single_argument_value
{
  using type = result_of_return_single_argument_value_t;
};

}  // namespace argot::receiver

template<>
struct make_concept_map
< ArgumentReceiver< receiver::return_single_argument_value_t::impl > >
{
  template< class... LeadingPs, class... TrailingPs, class P
          , ARGOT_REQUIRES
            ( Sinkable< LeadingPs&& >... )
            ( Sinkable< P&& > )
            ( Sinkable< TrailingPs&& >... )
            ()
          >
  static constexpr decltype( auto )
  receive_branch
  ( receiver::return_single_argument_value_t::impl
  , receiver_traits::argument_list_kinds_t
    < receiver_traits::argument_types_t< LeadingPs >... >
  , receiver_traits::argument_list_kinds_t
    < receiver_traits::argument_types_t< TrailingPs >... >
  , P&& arg
  )
  {
    return std::variant
    < detail_argot::remove_cvref_t< LeadingPs >...
    , detail_argot::remove_cvref_t< P >
    , detail_argot::remove_cvref_t< TrailingPs >...
    >( std::in_place_index< sizeof...( LeadingPs ) >
     , call_detail::forward_and_sink< P >( arg )
     );
  }
};

}  // namespace argot

#endif  // ARGOT_RECEIVER_RETURN_SINGLE_ARGUMENT_VALUE_HPP_
