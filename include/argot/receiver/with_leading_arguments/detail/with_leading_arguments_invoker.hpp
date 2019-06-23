/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_WITH_LEADING_ARGUMENTS_DETAIL_INVOKER_HPP_
#define ARGOT_RECEIVER_WITH_LEADING_ARGUMENTS_DETAIL_INVOKER_HPP_

#include <argot/detail/concatenate.hpp>
#include <argot/detail/permute.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace receiver {
namespace with_leading_arguments_detail {

template
< class LeadingPossibilities, class TrailingPossibilities, class Ps >
using local_possibilities_t
  = call_detail::concatenate_t
    < LeadingPossibilities
    , receiver_traits::argument_list_kinds_t< Ps >
    , TrailingPossibilities
    >;

template
< class OLeadingPossibilities, class QualifiedOPs
, class LeadingPossibilities, class TrailingPossibilities, class Ps
>
using leading_possibilities_t
  = call_detail::concatenate_t
    < call_detail::permute_t
      < OLeadingPossibilities
      , local_possibilities_t
        < LeadingPossibilities
        , TrailingPossibilities
        , Ps
        >
      >
    , call_detail::permute_t
      < receiver_traits::argument_list_kinds_t< QualifiedOPs >
      , LeadingPossibilities
      >
    >;

template
< class OTrailingPossibilities, class QualifiedOPs
, class LeadingPossibilities, class TrailingPossibilities, class Ps
>
using trailing_possibilities_t
  = call_detail::concatenate_t
    < call_detail::permute_t
      < receiver_traits::argument_list_kinds_t< QualifiedOPs >
      , TrailingPossibilities
      >
    , call_detail::permute_t
      < OTrailingPossibilities
      , local_possibilities_t
        < LeadingPossibilities
        , TrailingPossibilities
        , Ps
        >
      >
    >;

template< bool ForwardIfTrue, class T >
using forward_if_t
  = std::conditional_t< ForwardIfTrue, T&&, T& >;

template< bool ForwardIfTrue, class... T >
using qualified_argument_types_t
  = receiver_traits::argument_types_t< forward_if_t< ForwardIfTrue, T >... >;

template
< class OLeadingPossibilities, class OTrailingPossibilities, class QualifiedOPs
, class LeadingPossibilities, class TrailingPossibilities, class Ps
>
using possibilities_t
  = call_detail::concatenate_t
    < leading_possibilities_t
      < OLeadingPossibilities, QualifiedOPs
      , LeadingPossibilities, TrailingPossibilities, Ps
      >
    , receiver_traits::argument_list_kinds_t
      < receiver_traits::combine_argument_types_t< QualifiedOPs, Ps > >
    , trailing_possibilities_t
      < OTrailingPossibilities, QualifiedOPs
      , LeadingPossibilities, TrailingPossibilities, Ps
      >
    >;

// GCC workaround
template<class T>
using ident = T;

template< class OLeadingPossibilities, class OTrailingPossibilities
        , class... OP
        >
constexpr auto make_receive_branch_invoker
( OLeadingPossibilities, OTrailingPossibilities, OP&&... args ) noexcept
{
  // TODO(mattcalabrese) Figure out why unbound_receive_branch doesn't work.
  return [ &args... ]
  ( auto as_rvalue
  , auto&& rec, auto leading, auto trailing, auto&&... trailing_args
  ) -> decltype( auto )
  {
    using qualified_ops
      = qualified_argument_types_t< decltype( as_rvalue )::value, OP... >;

    using local_argument_types
      = receiver_traits::argument_types_t
        < ident< decltype( trailing_args ) >... >;

    return receiver_traits::receive_branch
    ( ARGOT_MOVE( rec )
    , leading_possibilities_t
      < OLeadingPossibilities, qualified_ops
      , decltype( leading ), decltype( trailing ), local_argument_types
      >{}
    , trailing_possibilities_t
      < OTrailingPossibilities, qualified_ops
      , decltype( leading ), decltype( trailing ), local_argument_types
      >{}
    , static_cast< forward_if_t< decltype( as_rvalue )::value, OP > >( args )...
    , ARGOT_FORWARD( decltype( trailing_args ) )( trailing_args )...
    );
  };
}

}  // namespace argot::receiver::with_leading_arguments_detail
}  // namespace argot::receiver
}  // namespace argot

#endif  // ARGOT_RECEIVER_WITH_LEADING_ARGUMENTS_DETAIL_INVOKER_HPP_
