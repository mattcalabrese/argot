/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TRANSFORM_HPP_
#define ARGOT_REDUCER_TRANSFORM_HPP_

#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/concepts/persistent_return_value_reducer.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace reducer {

struct transform_t
{
  template< class Conversion >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Conversion > );

    Conversion conversion;
  };

  template< class Conversion, ARGOT_REQUIRES( Sinkable< Conversion&& > )() >
  [[nodiscard]] constexpr auto operator ()( Conversion&& conversion ) const
  {
    return impl< detail_argot::remove_cvref_t< Conversion > >
    { ARGOT_FORWARD( Conversion )( conversion ) };
  }
} inline constexpr transform{};

// TODO(mattcalabrese) use constexpr_invoke
template< class Conversion >
using result_of_transform
  = std::invoke_result< transform_t const&, Conversion&& >;

template< class Conversion >
using result_of_result_of_transform_t
  = std::invoke_result_t< transform_t const&, Conversion&& >;

} // namespace argot::reducer

template< class Conversion >
struct make_concept_map
< ReturnValueReducer< reducer::transform_t::impl< Conversion > > >
{
  using is_homogeneous = std::true_type;

  template
  < class Self
  , class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun
  >
  static constexpr std::invoke_result_t
  < call_detail::give_qualifiers_to_t< Self&&, Conversion >
  , std::invoke_result_t< Fun >&&
  >
  reduce( Self&& self
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    return ARGOT_FORWARD( Self )( self ).conversion
    ( ARGOT_FORWARD( Fun )( fun )() );
  }
};

template< class Conversion >
struct make_concept_map
< PersistentReturnValueReducer< reducer::transform_t::impl< Conversion > > >
{
  using is_homogeneous = std::true_type;

  template
  < class Self
  , class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun
  >
  static constexpr std::invoke_result_t
  < call_detail::give_qualifiers_to_t< Self&&, Conversion >
  , std::invoke_result_t< Fun >&&
  >
  reduce( Self const& self
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    return ARGOT_FORWARD( Self )( self ).conversion
    ( ARGOT_FORWARD( Fun )( fun )() );
  }
};

} // namespace argot

#endif  // ARGOT_REDUCER_TRANSFORM_HPP_
