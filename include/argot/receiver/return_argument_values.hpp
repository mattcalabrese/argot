/*==============================================================================
  Copyright (c) 2017, 2018, 2019, 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_RETURN_ARGUMENT_VALUES_HPP_
#define ARGOT_RECEIVER_RETURN_ARGUMENT_VALUES_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/gen/transparent_requirement.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/struct_.hpp>

#include <utility>

namespace argot {
namespace receiver {

struct return_argument_values_t
{
  struct impl {};

  constexpr impl operator()() const { return {}; }
} inline constexpr return_argument_values{};

using result_of_return_argument_values_t = return_argument_values_t::impl;

struct result_of_return_argument_values
{
  using type = result_of_return_argument_values_t;
};

namespace return_argument_values_detail {

template< class ArgumentTypes >
struct argument_types_to_struct {};

template< class... T >
struct argument_types_to_struct< receiver_traits::argument_types_t< T... > >
{
  using type = struct_< detail_argot::remove_cvref_t< T >... >;
};

template< class ArgumentTypes >
using argument_types_to_struct_t
  = typename argument_types_to_struct< ArgumentTypes >::type;

template< class ArgumentTypes >
struct argument_types_are_sinkable {};

template< class... P >
struct argument_types_are_sinkable< receiver_traits::argument_types_t< P... > >
{
  template< template< class... > class Req >
  using expand_requirements = Req< Sinkable< P&& >... >;
};

} // namespace argot::receiver::return_argument_values_detail
} // namespace argot::receiver

template<>
struct make_concept_map
< ArgumentReceiver< receiver::return_argument_values_t::impl > >
{
  template< class... LeadingPs, class... TrailingPs, class... P
          , ARGOT_REQUIRES
            ( TransparentRequirement
              < receiver::return_argument_values_detail
                ::argument_types_are_sinkable< LeadingPs >
              >...
            )
            ( Sinkable< P&& >... )
            ( TransparentRequirement
              < receiver::return_argument_values_detail
                ::argument_types_are_sinkable< TrailingPs >
              >...
            )
            ()
          >
  static constexpr auto
  receive_branch
  ( receiver::return_argument_values_t::impl
  , receiver_traits::argument_list_kinds_t< LeadingPs... >
  , receiver_traits::argument_list_kinds_t< TrailingPs... >
  , P&&... args
  )
  {
    return discriminated_union
    < receiver::return_argument_values_detail::argument_types_to_struct_t
      < LeadingPs >...
    , struct_< detail_argot::remove_cvref_t< P >... >
    , receiver::return_argument_values_detail::argument_types_to_struct_t
      < TrailingPs >...
    >( std::in_place_index< sizeof...( LeadingPs ) >
     , std::in_place
     , call_detail::forward_and_sink< P >( args )...
     );
  }
};

} // namespace argot

#endif  // ARGOT_RECEIVER_RETURN_ARGUMENT_VALUES_HPP_
