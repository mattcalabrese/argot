/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_DETAIL_UNION_BACKEND_FWD_HPP_
#define ARGOT_UNION_DETAIL_UNION_BACKEND_FWD_HPP_

#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/variadic_at.hpp>
#include <argot/detail/variadic_chunk.hpp>

#include <cstddef>
#include <utility>
#include <type_traits>

namespace argot {

template< class... T >
class union_;

// TODO(mattcalabrese) Move in_place_index_with_result_t to separate file.
template< std::size_t I >
struct in_place_index_with_result_t
{
  explicit in_place_index_with_result_t() = default;
};

template< std::size_t I >
constexpr in_place_index_with_result_t< I > in_place_index_with_result{};

namespace detail_union {

template< std::size_t Index >
struct union_impl_preprocessed;

template< std::size_t Index >
struct union_impl_variadic;

template< std::size_t NumAlternatives, std::size_t Index >
using union_impl
  = typename argot_detail::conditional
    < NumAlternatives <= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES >
    ::template meta_apply_values
    < union_impl_preprocessed
    , union_impl_variadic
    , Index
    >;

template< std::size_t Index >
struct union_impl_variadic
{
  static constexpr std::size_t primary_index
    = Index / ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES;

  static constexpr std::size_t secondary_index
    = Index % ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES;

  template< class AlternativeType, class UnionBase >
  static constexpr auto&& get( UnionBase&& self ) noexcept
  {
    using primary_union_base_impl
      = union_impl
        < std::remove_reference_t< UnionBase >::num_members_v
        , primary_index
        >;

    using qualified_alt
      = call_detail::give_qualifiers_to_t< UnionBase&&, AlternativeType >;

    return static_cast< qualified_alt >
    ( union_impl
      < std::remove_reference_t< UnionBase >::num_members_v
      , secondary_index
      >::template get< AlternativeType >
      ( primary_union_base_impl::template get
        < primary_union_base_impl::template expand_members_t
          < primary_union_base_impl::template member_type_t >
        >
        ( ARGOT_FORWARD( UnionBase )( self ).sub_union_base )
      )
    );
  }

  // TODO(mattcalabrese) Conditional noexcept?
  template< class UnionBase >
  static constexpr void destroy( UnionBase& self )
  {
    using primary_union_base_impl
      = union_impl
        < UnionBase::num_members_v
        , primary_index
        >;

    primary_union_base_impl::destroy( self.sub_union_base );
    self.sub_union_base.~UnionBase();
  }
};

template< class... T >
struct raw_struct;

template<>
struct raw_struct<> {};

template< class... T >
struct union_base_recursive;

namespace no_default_no_destructor {

template< class... T >
struct union_base;

template<>
struct union_base<> {};

} // namespace argot::detail_union(::no_default_no_destructor)

namespace no_default_has_destructor {

template< class... T >
struct union_base;

template<>
struct union_base<> {};

} // namespace argot::detail_union(::no_default_has_destructor)

namespace has_default_no_destructor {

template< class... T >
struct union_base;

template<>
struct union_base<> {};

} // namespace argot::detail_union(::has_default_no_destructor)

namespace has_default_has_destructor {

template< class... T >
struct union_base;

template<>
struct union_base<> {};

} // namespace argot::detail_union(::has_default_has_destructor)

template< class... T >
using destructor_check_when_has_default
  = typename argot_detail::conditional
    < std::is_trivially_destructible_v< raw_struct< T... > > >
    ::template meta_apply
    < has_default_has_destructor::union_base
    , has_default_no_destructor::union_base
    , T...
    >;

template< class... T >
using destructor_check_when_no_default
  = typename argot_detail::conditional
    < std::is_trivially_destructible_v< raw_struct< T... > > >
    ::template meta_apply
    < no_default_has_destructor::union_base
    , no_default_no_destructor::union_base
    , T...
    >;

template< class... T >
using union_base_preprocessed
  = typename argot_detail::conditional
    < std::is_trivially_default_constructible_v< raw_struct< T... > > >
    ::template meta_apply
    < destructor_check_when_has_default
    , destructor_check_when_no_default
    , T...
    >;

template< class... T >
using union_base_picker
  = typename argot_detail::conditional
    < sizeof...( T ) <= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES >
    ::template meta_apply
    < union_base_preprocessed
    , union_base_recursive
    , T...
    >;

template< class... T >
using sub_union_base_t
  = detail_argot::variadic_chunk
    < ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES
    , union_base_picker, union_base_picker
    , T...
    >;

template< class... T >
struct union_base_recursive
{
  using sub_union_base_impl_t = sub_union_base_t< T... >;

  static constexpr std::size_t num_members_v = sizeof...( T );

  template< template< class... > class Result >
  using expand_members_t = Result< T... >;

  union_base_recursive() = default;

  template< std::size_t I, class... P >
  explicit constexpr union_base_recursive
  ( std::in_place_index_t< I > const /*in_place_index*/
  , P&&... args
  ) // TODO(mattcalabrese) conditional noexcept
    : sub_union_base
      ( std::in_place_index< I / ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES >
      , []( auto&& nested_args )
        {
          return detail_argot::variadic_at
          < I, detail_forward::direct_identity_t, T... >
          ( std::in_place_index< I % ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES >
          , ARGOT_FORWARD( P )( nested_args )...
          );
        }
      , ARGOT_FORWARD( P )( args )...
      ) {}

  template< std::size_t I, class Fun, class... P >
  explicit constexpr union_base_recursive
  ( in_place_index_with_result_t< I >
      const /*in_place_index_with_result*/
  , Fun&& fun, P&&... args
  ) noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
    : sub_union_base
      ( in_place_index_with_result
        < I / ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES >
      , [ &fun ]( auto&& nested_args )
        {
          return detail_argot::variadic_at
          < I, detail_forward::direct_identity_t, T... >
          ( in_place_index_with_result
            < I % ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES >
          , ARGOT_FORWARD( Fun )( fun )
          , ARGOT_FORWARD( P )( nested_args )...
          );
        }
      , ARGOT_FORWARD( P )( args )... 
      ) {}

  ARGOT_NO_UNIQUE_ADDRESS sub_union_base_impl_t sub_union_base;
};

} // namespace argot(::detail_union)
} // namespace argot

#endif  // ARGOT_UNION_DETAIL_UNION_BACKEND_FWD_HPP_
