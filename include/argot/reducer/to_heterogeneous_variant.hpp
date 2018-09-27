/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TO_HETEROGENEOUS_VARIANT_HPP_
#define ARGOT_REDUCER_TO_HETEROGENEOUS_VARIANT_HPP_

#include <argot/basic_result_of.hpp>
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

struct to_heterogeneous_variant_t {} inline constexpr to_heterogeneous_variant
 {};

namespace to_heterogeneous_variant_detail {

template< class T >
struct make_variant_from_list;

template< class... T >
struct make_variant_from_list< reducer_traits::return_types_t< T... > >
{
  using type = std::variant< T... >;
};

template< class T >
using make_variant_from_list_t = typename make_variant_from_list< T >::type;

template< class Expected, class... T >
struct exists_in_list;

template< class Expected, class H, class... T >
struct exists_in_list< Expected, H, T... >
  : exists_in_list< Expected, T... >::type {};

template< class Expected, class... T >
struct exists_in_list< Expected, Expected, T... >
  : std::true_type {};

template< class Expected >
struct exists_in_list< Expected >
  : std::false_type {};

template< class Curr, class... T >
struct remove_duplicates_impl;

template< class Curr >
struct remove_duplicates_impl< Curr >
{
  using type = Curr;
};

template< class... Res, class H, class... T >
struct remove_duplicates_impl
< reducer_traits::return_types_t< Res... >, H, T... >
{
  using type
    = typename remove_duplicates_impl
      < typename argot_detail::conditional
        < exists_in_list< H, Res... >::value >
        ::template apply
        < reducer_traits::return_types_t< Res... >
        , reducer_traits::return_types_t< Res..., H >
        >
      , T...
      >::type;
};

template< class... T >
using remove_duplicates_t
  = typename remove_duplicates_impl
    < reducer_traits::return_types_t<>, T... >::type;

} // namespace argot::reducer::to_heterogeneous_variant_detail
} // namespace argot::reducer

template<>
struct make_concept_map
< ReturnValueReducer< reducer::to_heterogeneous_variant_t > >
{
  using is_homogeneous = std::false_type;

  // TODO(mattcalabrese) Proper constraints
  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr std::enable_if_t
  < std::is_move_constructible< std::invoke_result_t< Fun > >::value
  , reducer::to_heterogeneous_variant_detail::make_variant_from_list_t
    < reducer::to_heterogeneous_variant_detail::remove_duplicates_t
      < LeadingReturnTypes...
      , basic_result_of_t< Fun&& >, TrailingReturnTypes...
      >
    >
  >
  reduce
  ( reducer::to_heterogeneous_variant_t
  , reducer_traits::return_types_t< LeadingReturnTypes... >
  , reducer_traits::return_types_t< TrailingReturnTypes... >
  , Fun&& fun
  )
  {
    return reducer::to_heterogeneous_variant_detail::make_variant_from_list_t
    < reducer::to_heterogeneous_variant_detail::remove_duplicates_t
      < LeadingReturnTypes..., basic_result_of_t< Fun&& >
      , TrailingReturnTypes...
      >
    >
    ( std::in_place_type< basic_result_of_t< Fun&& > >
    , ARGOT_FORWARD( Fun )( fun )()
    );
  }
};

template<>
struct make_concept_map
< PersistentReturnValueReducer< reducer::to_heterogeneous_variant_t > >
{
  using is_homogeneous = std::false_type;

  // TODO(mattcalabrese) Proper constraints
  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr std::enable_if_t
  < std::is_move_constructible< std::invoke_result_t< Fun > >::value
  , reducer::to_heterogeneous_variant_detail::make_variant_from_list_t
    < reducer::to_heterogeneous_variant_detail::remove_duplicates_t
      < LeadingReturnTypes...
      , basic_result_of_t< Fun&& >, TrailingReturnTypes...
      >
    >
  >
  reduce
  ( reducer::to_heterogeneous_variant_t
  , reducer_traits::return_types_t< LeadingReturnTypes... >
  , reducer_traits::return_types_t< TrailingReturnTypes... >
  , Fun&& fun
  )
  {
    return reducer::to_heterogeneous_variant_detail::make_variant_from_list_t
    < reducer::to_heterogeneous_variant_detail::remove_duplicates_t
      < LeadingReturnTypes..., basic_result_of_t< Fun&& >
      , TrailingReturnTypes...
      >
    >
    ( std::in_place_type< basic_result_of_t< Fun&& > >
    , ARGOT_FORWARD( Fun )( fun )()
    );
  }
};

} // namespace argot

#endif  // ARGOT_REDUCER_TO_HETEROGENEOUS_VARIANT_HPP_
