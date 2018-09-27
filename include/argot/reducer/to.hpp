/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TO_HPP_
#define ARGOT_REDUCER_TO_HPP_

//[description
/*`
reducer::to is a facility for specifying a ReturnValueReducer that converts to
a user-specified type. Each possible return type must be implicitly convertible
to the user-specified type, otherwise substitution will fail when reduction is
to take place.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/convertible.hpp>
#include <argot/concepts/persistent_return_value_reducer.hpp>
#include <argot/concepts/return_type.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/reducer_traits/return_types.hpp>

#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::reducer {

template< class Ret >
struct to_t//= {};
//<-
{
  ARGOT_CONCEPT_ASSERT( ReturnType< Ret > );
}; //->

template< class Ret >
ARGOT_REQUIRES( ReturnType< Ret > )
< to_t< Ret > > constexpr to{};

//<-
namespace to_detail {

// TODO(mattcalabrese) Remove this base and old-style sfinae.
// TODO(mattcalabrese) If bool, use ContextuallyConvertibleToBool
template< class Ret, class /*Enabler*/ = void >
struct to_impl
{
  using is_homogeneous = std::true_type;

  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr ARGOT_REQUIRES
  ( ReturnType< LeadingReturnTypes >... )
  ( ReturnType< TrailingReturnTypes >... )
  ( BasicCallableWith< Fun&& > )
  ( Convertible< basic_result_of_t< Fun&& >, Ret > )
  < Ret >
  reduce( to_t< Ret > /*self*/
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    return ARGOT_FORWARD( Fun )( fun )();
  }
};

template< class Ret >
struct to_impl
< Ret
, call_detail::fast_enable_if_t< std::is_void_v< Ret > >
>
{
  using is_homogeneous = std::true_type;

  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr ARGOT_REQUIRES
  ( ReturnType< LeadingReturnTypes >... )
  ( ReturnType< TrailingReturnTypes >... )
  ( BasicCallableWith< Fun&& > )
  < void >
  reduce( to_t< Ret > /*self*/
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    ARGOT_FORWARD( Fun )( fun )();
  }
};

} // namespace argot::reducer::to_detail
//->
} // namespace (argot::reducer)

//]

namespace argot {

template< class Ret >
struct make_concept_map< ReturnValueReducer< reducer::to_t< Ret > > >
  : reducer::to_detail::to_impl< Ret >{};

template< class Ret >
struct make_concept_map
< PersistentReturnValueReducer< reducer::to_t< Ret > > >
  : reducer::to_detail::to_impl< Ret >{};

} // namespace argot

#endif  // ARGOT_REDUCER_TO_HPP_
