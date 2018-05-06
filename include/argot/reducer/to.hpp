/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TO_HPP_
#define ARGOT_REDUCER_TO_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/convertible.hpp>
#include <argot/concepts/persistent_return_value_reducer.hpp>
#include <argot/concepts/return_type.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/detail/detection.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/reducer_traits/return_types.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace reducer {

template< class ReturnType >
struct to_t
{
  ARGOT_CONCEPT_ASSERT( argot::ReturnType< ReturnType > );
};

template< class ReturnType >
ARGOT_REQUIRES( argot::ReturnType< ReturnType > )
< to_t< ReturnType > > constexpr to{};

namespace to_detail {

// TODO(mattcalabrese) Remove this base and old-style sfinae.
// TODO(mattcalabrese) If bool, use ContextuallyConvertibleToBool
template< class ReturnType, class /*Enabler*/ = void >
struct to_impl
{
  using is_homogeneous = std::true_type;

  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr ARGOT_REQUIRES
  ( argot::ReturnType< LeadingReturnTypes >... )
  ( argot::ReturnType< TrailingReturnTypes >... )
  ( BasicCallableWith< Fun&& > )
  ( Convertible< basic_result_of_t< Fun&& >, ReturnType > )
  < ReturnType >
  reduce( to_t< ReturnType > /*self*/
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    return ARGOT_FORWARD( Fun )( fun )();
  }
};

template< class ReturnType >
struct to_impl
< ReturnType
, call_detail::fast_enable_if_t< std::is_void_v< ReturnType > >
>
{
  using is_homogeneous = std::true_type;

  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr ARGOT_REQUIRES
  ( argot::ReturnType< LeadingReturnTypes >... )
  ( argot::ReturnType< TrailingReturnTypes >... )
  ( BasicCallableWith< Fun&& > )
  < void >
  reduce( to_t< ReturnType > /*self*/
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    ARGOT_FORWARD( Fun )( fun )();
  }
};

}  // namespace argot::reducer::to_detail
}  // namespace argot::reducer

template< class ReturnType >
struct make_concept_map< ReturnValueReducer< reducer::to_t< ReturnType > > >
  : reducer::to_detail::to_impl< ReturnType >{};

template< class ReturnType >
struct make_concept_map
< PersistentReturnValueReducer< reducer::to_t< ReturnType > > >
  : reducer::to_detail::to_impl< ReturnType >{};

}  // namespace argot

#endif  // ARGOT_REDUCER_TO_HPP_
