/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_SAME_TYPE_OR_FAIL_HPP_
#define ARGOT_REDUCER_SAME_TYPE_OR_FAIL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/persistent_return_value_reducer.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/reducer_traits/return_types.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace reducer {

struct same_type_or_fail_t {} inline constexpr same_type_or_fail{};

}  // namespace argot(::reducer)

template<>
struct make_concept_map
< ReturnValueReducer< reducer::same_type_or_fail_t > >
{
  using is_homogeneous = std::true_type;

  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun
  , ARGOT_REQUIRES
    ( BasicCallableWith< Fun&& > )
    ( SameType
      < LeadingReturnTypes...
      , basic_result_of_t< Fun&& >
      , TrailingReturnTypes...
      >
    )()
  >
  static constexpr decltype( auto )
  reduce( reducer::same_type_or_fail_t /*self*/
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    return ARGOT_FORWARD( Fun )( fun )();
  }
};

template<>
struct make_concept_map
< PersistentReturnValueReducer< reducer::same_type_or_fail_t > >
{
  using is_homogeneous = std::true_type;

  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun
  , ARGOT_REQUIRES
    ( BasicCallableWith< Fun&& > )
    ( SameType
      < LeadingReturnTypes...
      , basic_result_of_t< Fun&& >
      , TrailingReturnTypes...
      >
    )()
  >
  static constexpr decltype( auto )
  reduce( reducer::same_type_or_fail_t /*self*/
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    return ARGOT_FORWARD( Fun )( fun )();
  }
};

}  // namespace argot

#endif  // ARGOT_REDUCER_SAME_TYPE_OR_FAIL_HPP_
