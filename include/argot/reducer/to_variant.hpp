/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TO_VARIANT_HPP_
#define ARGOT_REDUCER_TO_VARIANT_HPP_

#include <argot/concepts/persistent_return_value_reducer.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/reducer_traits/return_types.hpp>

#include <type_traits>
#include <utility>
#include <variant>

namespace argot {
namespace reducer {

struct to_variant_t {} inline constexpr to_variant{};

}  // namespace argot::reducer

// TODO(mattcalabrese) Replace old-style SFINAE constraints.
template<>
struct make_concept_map< ReturnValueReducer< reducer::to_variant_t > >
{
  using is_homogeneous = std::false_type;

  // TODO(mattcalabrese) Replace enable_if with ARGOT_REQUIRES
  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr std::enable_if_t
  < std::is_move_constructible< std::invoke_result_t< Fun > >::value
  , std::variant
    < LeadingReturnTypes..., std::invoke_result_t< Fun >
    , TrailingReturnTypes...
    >
  >
  reduce
  ( reducer::to_variant_t
  , reducer_traits::return_types_t< LeadingReturnTypes... >
  , reducer_traits::return_types_t< TrailingReturnTypes... >
  , Fun&& fun
  )
  {
    return std::variant
    < LeadingReturnTypes..., std::invoke_result_t< Fun >
    , TrailingReturnTypes...
    >
    ( std::in_place_index< sizeof...( LeadingReturnTypes ) >
    , ARGOT_FORWARD( Fun )( fun )()
    );
  }
};

// TODO(mattcalabrese) Replace old-style SFINAE constraints.
template<>
struct make_concept_map< PersistentReturnValueReducer< reducer::to_variant_t > >
{
  using is_homogeneous = std::false_type;

  // TODO(mattcalabrese) Replace enable_if with ARGOT_REQUIRES
  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr std::enable_if_t
  < std::is_move_constructible< std::invoke_result_t< Fun > >::value
  , std::variant
    < LeadingReturnTypes..., std::invoke_result_t< Fun >
    , TrailingReturnTypes...
    >
  >
  reduce
  ( reducer::to_variant_t
  , reducer_traits::return_types_t< LeadingReturnTypes... >
  , reducer_traits::return_types_t< TrailingReturnTypes... >
  , Fun&& fun
  )
  {
    return std::variant
    < LeadingReturnTypes..., std::invoke_result_t< Fun >
    , TrailingReturnTypes...
    >
    ( std::in_place_index< sizeof...( LeadingReturnTypes ) >
    , ARGOT_FORWARD( Fun )( fun )()
    );
  }
};

}  // namespace argot

#endif  // ARGOT_REDUCER_TO_VARIANT_HPP_
