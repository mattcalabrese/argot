/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TRAITS_REDUCE_HPP_
#define ARGOT_REDUCER_TRAITS_REDUCE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/persistent_return_value_reducer.hpp>
#include <argot/concepts/persistent_return_value_reducer_of.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/return_value_reducer_of.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot::reducer_traits {

struct reduce_t
{
  // Note: The ReturnValueReducer constrain is redundant with the
  //       ReturnValueReducerOf constraint, but it is explicit in the requires
  //       list so that it is the failure that is reported if the caller does
  //       not pass in a ReturnValueReducer as the first argument.
  template
  < class Reducer
  , class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun
  , ARGOT_REQUIRES
    ( BasicCallableWith< Fun&& > )
    ( typename argot_detail::conditional
      < std::is_rvalue_reference_v
        < call_detail::result_of_sinklike_cast_t< Reducer&& > >
      >
      ::template meta_apply
      < ReturnValueReducerOf, PersistentReturnValueReducerOf
      , remove_cvref_t< Reducer >
      , LeadingReturnTypes...
      , basic_result_of_t< Fun&& >
      , TrailingReturnTypes...
      >
    )
    ()
  >
  constexpr decltype( auto )
  operator ()( Reducer&& reducer
             , return_types_t< LeadingReturnTypes... >
             , return_types_t< TrailingReturnTypes... >
             , Fun&& fun
             ) const
  {
    using RawReducer = remove_cvref_t< Reducer >;

    using QualifiedReducer
      = call_detail::result_of_sinklike_cast_t< Reducer&& >;

    if constexpr( std::is_rvalue_reference_v< QualifiedReducer > )
      return access_raw_concept_map
      < ReturnValueReducer< RawReducer > >::reduce
      ( static_cast< QualifiedReducer >( reducer )
      , return_types< LeadingReturnTypes... >
      , return_types< TrailingReturnTypes... >
      , ARGOT_FORWARD( Fun )( fun )
      );
    else
      return access_raw_concept_map
      < PersistentReturnValueReducer< RawReducer > >::reduce
      ( static_cast< QualifiedReducer >( reducer )
      , return_types< LeadingReturnTypes... >
      , return_types< TrailingReturnTypes... >
      , ARGOT_FORWARD( Fun )( fun )
      );
  }
} inline constexpr reduce{};

template
< class Reducer
, class LeadingReturnTypes, class TrailingReturnTypes, class Fun
>
using result_of_reduce_t
  = basic_result_of_t
    < reduce_t const&
    , Reducer, LeadingReturnTypes, TrailingReturnTypes, Fun
    >;

template
< class Reducer
, class LeadingReturnTypes, class TrailingReturnTypes, class Fun
>
using result_of_reduce
  = basic_result_of
    < reduce_t const&
    , Reducer, LeadingReturnTypes, TrailingReturnTypes, Fun
    >;

// TODO(mattcalabrese) Make a result of unbound reduce.

}  // namespace (argot::reducer_traits)

#endif  // ARGOT_REDUCER_TRAITS_REDUCE_HPP_
