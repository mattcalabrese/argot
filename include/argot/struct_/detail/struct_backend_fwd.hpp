/*==============================================================================
  Copyright (c) 2019, 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_
#define ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_

#include <argot/contained.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/if_.hpp>
#include <argot/detail/preprocess.hpp>
#include <argot/in_place_index_with_result.hpp>
#include <argot/in_place_with_result.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace argot::detail_struct {

template< std::size_t S >
struct impl_of_size;

/*
TODO(mattcalabrese) Implement these instead of impl_of_size

template< std::size_t S >
struct internal_impl_of_size;

template< std::size_t S >
struct leaf_impl_of_size;
*/

template< class... T >
using struct_impl
  = typename impl_of_size< sizeof...( T ) >
    ::template impl< T... >;

template< std::size_t I >
struct member;

template< std::size_t NextDepth, class MemberType >
struct make_ith_member_fn
{
  template< class... P >
  constexpr auto operator()( P&&... args ) const
  {
    return MemberType
    ( std::in_place_index< NextDepth - 1 >
    , ARGOT_SIMPLE_FORWARD( args )...
    );
  }
};

template< std::size_t NextDepth, class MemberType >
struct make_ith_member_fun_fn
{
  template< class... F >
  constexpr auto operator()( F&&... f ) const
  {
    return MemberType
    ( in_place_index_with_result< NextDepth - 1 >
    , ARGOT_SIMPLE_FORWARD( f )...
    );
  }
};

struct member_type_of_tree_terminal
{
  template< std::size_t /*Depth*/, class Tree, std::size_t I >
  using apply = typename member< I >::template apply< Tree >;
};

struct member_type_of_tree_intermediate;

template< std::size_t Depth, class Tree, std::size_t I >
using member_type_of_tree
  = typename detail_if_::if_< Depth == 1 >::then_else::template _
    < member_type_of_tree_terminal, member_type_of_tree_intermediate >
    ::template apply< Depth, Tree, I >;

struct member_type_of_tree_intermediate
{
  template< std::size_t Depth, class Tree, std::size_t I >
  using apply
    = member_type_of_tree
      < Depth - 1
      , member_type_of_tree_terminal::apply
        < 1, Tree, I / detail_argot::amount_at_depth( Depth - 1 ) >
      , I % detail_argot::amount_at_depth( Depth - 1 )
      >;
};

struct member_type_of_tree_holder
{
  template< std::size_t Depth, class Tree, std::size_t I >
  using apply = member_type_of_tree< Depth, Tree, I >;
};

struct identity_holder
{
  template< std::size_t /*Depth = 0*/, class Tree, std::size_t /*I*/ >
  using apply = Tree;
};

template< std::size_t I, class Tree, std::size_t... Depths >
constexpr auto&
access_tree( Tree& tree, std::index_sequence< Depths... > ) noexcept
{
  return
    ( tree
      .* ...
      .*member
        <   (   I
              / detail_argot::amount_per_group_at_depth
                ( sizeof...( Depths ) - Depths )
            )
          % ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH()
        >::template pointer_v
        < typename detail_if_::if_< Depths == 0 >::then_else::template _
          < identity_holder, member_type_of_tree_holder >::template apply
          < Depths, Tree
          , I / detail_argot::amount_at_depth( sizeof...( Depths ) - Depths )
          >
        >
    );
}

// TODO(mattcalabrese) Conditional noexcept
template< class Fun, class Struct, std::size_t... Indices >
constexpr decltype( auto )
variadic_unpack( Fun&& fun, Struct&& self, std::index_sequence< Indices... > )
{
  return argot_detail::constexpr_invoke
  ( ARGOT_FORWARD( Fun )( fun )
  , ARGOT_FORWARD( Struct )( self ).template get< Indices >()...
  );
}

}  // namespace (argot::detail_struct)

#endif  // ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_
