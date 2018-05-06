/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_MAKE_RETURN_VALUE_REDUCER_HPP_
#define ARGOT_REDUCER_MAKE_RETURN_VALUE_REDUCER_HPP_

#if 0

#include <argot/gen/make_concept_map.hpp>
#include <argot/detail/auto_function.hpp>
#include <argot/detail/impl_holder.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/concepts/return_value_reducer.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace reducer {
namespace make_return_value_reducer_detail {

template< class Reducer, class /*Enabler*/ = void >
struct homogeneity_of
{
  using type = std::false_type;
};

template< class Reducer >
struct homogeneity_of
< Reducer, std::enable_if_t< Reducer::is_homogeneous::value > >
{
  using type = std::true_type;
};

}  // namespace argot::reducer::make_return_value_reducer_detail

template< class Impl >
struct return_value_reducer
  : public call_detail::impl_holder< return_value_reducer, Impl >
{
 public:
  return_value_reducer() = default;
  constexpr Impl const& state() const
  {
    return call_detail::impl_holder< return_value_reducer, Impl >::impl;
  }
 public:
  friend call_detail::impl_holder< return_value_reducer, Impl >;

  using base_type = call_detail::impl_holder< return_value_reducer, Impl >;
  using base_type::base_type;
  using base_type::impl;
};

// TODO(mattcalabrese) More fully concept constrain.
struct make_return_value_reducer_t
{
  // TODO(mattcalabrese) Don't use the macro here
  template< class Impl >
  constexpr
  ARGOT_DETAIL_AUTO_FUNCTION( operator ()( Impl&& impl ) const )
  (
    return call_detail::deduced_make_impl_holder< return_value_reducer >
    ( std::forward< Impl >( impl ) )
  )
} inline constexpr make_return_value_reducer{};

}  // namespace argot::reducer

template< class Impl >
struct make_concept_map
< ReturnValueReducer< reducer::return_value_reducer< Impl > > >
{
  using is_homogeneous
    = typename reducer::make_return_value_reducer_detail::homogeneity_of< Impl >
      ::type;

  template< class Self
          , class... LeadingReturnTypes, class Fun, class... TrailingReturnTypes
          >
  static constexpr ARGOT_DETAIL_AUTO_FUNCTION
  ( reduce( Self&& self
          , reducer_traits::return_types_t< LeadingReturnTypes... >
          , Fun&& fun
          , reducer_traits::return_types_t< TrailingReturnTypes... >
          )
  )
  (
    return Impl::reduce
    ( std::forward< Self >( self ).impl
    , reducer_traits::return_types< LeadingReturnTypes... >
    , std::forward< Fun >( fun )
    , reducer_traits::return_types< TrailingReturnTypes... >
    )
  )
};

}  // namespace argot

#endif

#endif  // ARGOT_REDUCER_MAKE_RETURN_VALUE_REDUCER_HPP_
