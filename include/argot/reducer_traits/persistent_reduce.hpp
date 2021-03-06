/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TRAITS_PERSISTENT_REDUCE_HPP_
#define ARGOT_REDUCER_TRAITS_PERSISTENT_REDUCE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/persistent_return_value_reducer_of.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/transparent_requirement.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot::reducer_traits {
namespace persistent_reduce_detail {

template
< class Reducer
, class LeadingReturnTypes, class TrailingReturnTypes, class Fun
>
struct persistent_return_value_reducer_of {};

template
< class Reducer
, class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun
>
struct persistent_return_value_reducer_of
< Reducer
, return_types_t< LeadingReturnTypes... >
, return_types_t< TrailingReturnTypes... >
, Fun
>
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < PersistentReturnValueReducerOf
        < Reducer
        , LeadingReturnTypes...
        , basic_result_of_t< Fun&& >
        , TrailingReturnTypes...
        >
      >;
};

} // namespace argot::reducer_traits(::persistent_reduce_detail)

struct persistent_reduce_t
{
  // Note: The ReturnValueReducer constrain is redundant with the
  //       ReturnValueReducerOf constraint, but it is explicit in the requires
  //       list so that it is the failure that is reported if the caller does
  //       not pass in a ReturnValueReducer as the first argument.
  template
  < class Reducer
  , class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun
  , ARGOT_REQUIRES
    ( PersistentReturnValueReducer< Reducer > )
    ( BasicCallableWith< Fun&& > )
    ( TransparentRequirement  // NOTE: This doesn't need TransparentRequirement
      < persistent_reduce_detail::persistent_return_value_reducer_of
        < Reducer
        , return_types_t< LeadingReturnTypes... >
        , return_types_t< TrailingReturnTypes... >
        , Fun&&
        >
      >
    )
    ()
  >
  constexpr decltype( auto )
  operator ()( Reducer const& reducer
             , return_types_t< LeadingReturnTypes... >
             , return_types_t< TrailingReturnTypes... >
             , Fun&& fun
             ) const
  {
    return access_raw_concept_map< PersistentReturnValueReducer< Reducer > >
    ::reduce
    ( reducer
    , return_types< LeadingReturnTypes... >
    , return_types< TrailingReturnTypes... >
    , ARGOT_FORWARD( Fun )( fun )
    );
  }
} inline constexpr persistent_reduce{};

template
< class Reducer
, class LeadingReturnTypes, class TrailingReturnTypes, class Fun
>
using result_of_persistent_reduce
  = basic_result_of
    < persistent_reduce_t const&
    , Reducer&&, LeadingReturnTypes&&, TrailingReturnTypes&&, Fun&&
    >;

template
< class Reducer
, class LeadingReturnTypes, class TrailingReturnTypes, class Fun
>
using result_of_persistent_reduce_t
  = basic_result_of_t
    < persistent_reduce_t const&
    , Reducer&&, LeadingReturnTypes&&, TrailingReturnTypes&&, Fun&&
    >;

// TODO(mattcalabrese) Make a result of unbound reduce.

} // namespace (argot::reducer_traits)

#endif  // ARGOT_REDUCER_TRAITS_PERSISTENT_REDUCE_HPP_
