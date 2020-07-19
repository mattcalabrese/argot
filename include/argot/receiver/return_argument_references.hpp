/*==============================================================================
  Copyright (c) 2017, 2018, 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_RETURN_ARGUMENT_REFERENCES_HPP_
#define ARGOT_RECEIVER_RETURN_ARGUMENT_REFERENCES_HPP_

#include <argot/concepts/argument_receiver.hpp>
#include <argot/detail/forward.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/struct_.hpp>

#include <utility>

namespace argot {
namespace receiver {

struct return_argument_references_t
{
  struct impl {};

  constexpr impl operator()() const { return {}; }
} inline constexpr return_argument_references{};

using result_of_return_argument_references_t
  = return_argument_references_t::impl;

struct result_of_return_argument_references
{
  using type = result_of_return_argument_references_t;
};

namespace return_argument_references_detail {

template< class ArgumentTypes >
struct argument_types_to_tuple{};

template< class... T >
struct argument_types_to_tuple< receiver_traits::argument_types_t< T... > >
{
  using type = struct_< T... >;
};

template< class ArgumentTypes >
using argument_types_to_tuple_t
  = typename argument_types_to_tuple< ArgumentTypes >::type;

} // namespace argot::receiver::return_argument_references_detail
} // namespace argot::receiver

template<>
struct make_concept_map
< ArgumentReceiver< receiver::return_argument_references_t::impl > >
{
  template< class... LeadingPs, class... TrailingPs, class... P >
  static constexpr discriminated_union
  < receiver::return_argument_references_detail::argument_types_to_tuple_t
    < LeadingPs >...
  , struct_< P&&... >
  , receiver::return_argument_references_detail::argument_types_to_tuple_t
    < TrailingPs >...
  >
  receive_branch
  ( receiver::return_argument_references_t::impl
  , receiver_traits::argument_list_kinds_t< LeadingPs... >
  , receiver_traits::argument_list_kinds_t< TrailingPs... >
  , P&&... args
  )
  {
    return discriminated_union
    < receiver::return_argument_references_detail::argument_types_to_tuple_t
      < LeadingPs >...
    , struct_< P&&... >
    , receiver::return_argument_references_detail::argument_types_to_tuple_t
      < TrailingPs >...
    >( std::in_place_index< sizeof...( LeadingPs ) >
     , std::in_place
     , ARGOT_FORWARD( P )( args )...
     );
  }
};

} // namespace argot

#endif  // ARGOT_RECEIVER_RETURN_ARGUMENT_REFERENCES_HPP_
