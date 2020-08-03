/*==============================================================================
  Copyright (c) 2018, 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_DETAIL_UNION_BACKEND_HPP_
#define ARGOT_UNION_DETAIL_UNION_BACKEND_HPP_

#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/addressof.hpp>
#include <argot/detail/preprocess.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/detail/variadic_at.hpp>
#include <argot/detail/variadic_chunk.hpp>
#include <argot/in_place_index_with_result.hpp>

#include <cstddef>
#include <utility>
#include <type_traits>

namespace argot {

template< class... T >
class union_;

namespace detail_union {

namespace no_default_no_destructor {

template< class... T >
union union_impl;

} // namespace argot::detail_union(::no_default_no_destructor)

namespace no_default_has_destructor {

template< class... T >
union union_impl;

} // namespace argot::detail_union(::no_default_has_destructor)

namespace has_default_no_destructor {

template< class... T >
union union_impl;

} // namespace argot::detail_union(::has_default_no_destructor)

namespace has_default_has_destructor {

template< class... T >
union union_impl;

} // namespace argot::detail_union(::has_default_has_destructor)

template< class... T >
using union_impl_has_default
  = typename argot_detail::conditional
    < (    (    std::is_trivially_destructible_v< T >
             && std::is_destructible_v< T >
           )
        && ...
      )
    >
    ::template meta_apply
    < has_default_has_destructor::union_impl
    , has_default_no_destructor::union_impl
    , T...
    >;

template< class... T >
using union_impl_no_default
  = typename argot_detail::conditional
    < (    (    std::is_trivially_destructible_v< T >
             && std::is_destructible_v< T >
           )
        && ...
      )
    >
    ::template meta_apply
    < no_default_has_destructor::union_impl
    , no_default_no_destructor::union_impl
    , T...
    >;

template< class... T >
using union_impl
  = typename argot_detail::conditional
    < (    (    std::is_trivially_default_constructible_v< T >
             && std::is_default_constructible_v< T >
           )
        && ...
      )
    >
    ::template meta_apply
    < union_impl_has_default
    , union_impl_no_default
    , T...
    >;

struct empty_member {};

struct member_type_or_empty_impl_empty
{
  template< std::size_t /*I*/, class... /*T*/ >
  using apply = empty_member;
};

#define ARGOT_DETAIL_TEMPLATE_PARAM( i, data ) class T ## i,

struct member_type_or_empty_impl_nonempty
{
  template
  < std::size_t I
#ifndef __clang__
  , std::nullptr_t = nullptr
#endif
  >
  struct applier;

#ifdef __clang__
#define ARGOT_DETAIL_MEMBER_APPLIER_SPEC_PARAM()
#define ARGOT_DETAIL_MEMBER_APPLIER_SPEC_TRAILING_ARG()
#else
#define ARGOT_DETAIL_MEMBER_APPLIER_SPEC_PARAM() std::nullptr_t NullPtrP
#define ARGOT_DETAIL_MEMBER_APPLIER_SPEC_TRAILING_ARG() , NullPtrP
#endif

#define ARGOT_DETAIL_MEMBER_TYPE_OR_EMPTY_APPLIER_SPEC( n, data )              \
  template< ARGOT_DETAIL_MEMBER_APPLIER_SPEC_PARAM() >                         \
  struct applier                                                               \
  < n                                                                          \
    ARGOT_DETAIL_MEMBER_APPLIER_SPEC_TRAILING_ARG()                            \
  >                                                                            \
  {                                                                            \
    template< ARGOT_DETAIL_EXPAND_N_TIMES( ARGOT_DETAIL_TEMPLATE_PARAM, n, ~ ) \
              class MemberType, class... /*Tail*/                              \
            >                                                                  \
    using apply = MemberType;                                                  \
  };

  ARGOT_DETAIL_EXPAND_MAX_UNROLL_DEPTH
  ( ARGOT_DETAIL_MEMBER_TYPE_OR_EMPTY_APPLIER_SPEC, ~ )

#undef ARGOT_DETAIL_MEMBER_APPLIER_SPEC_TRAILING_ARG
#undef ARGOT_DETAIL_MEMBER_APPLIER_SPEC_PARAM

  template< std::size_t I, class... T >
  using apply = detail_argot::expand< applier< I >::template apply, T... >;
};

template< std::size_t I, class... T >
using member_type_or_empty
  = typename detail_if_::if_< ( I < sizeof...( T ) ) >::then_else::template _
    < member_type_or_empty_impl_nonempty, member_type_or_empty_impl_empty >
    ::template apply< I, T... >;

// TODO(mattcalabrese) conditional noexcept
#define ARGOT_DETAIL_UNION_IMPL_BODY_DECLS( i, ClassName )                     \
 template< class... P >                                                        \
 explicit constexpr ClassName                                                  \
 ( std::in_place_index_t< 0 > /*next_depth*/                                   \
 , std::in_place_index_t< i > /*primary_index*/                                \
 , std::in_place_index_t< 0 > /*secondary_index*/                              \
 , P&&... args                                                                 \
 ) : member ## i ( static_cast< P&& >( args )... ) {}                          \
                                                                               \
 template< class F, class... P >                                               \
 explicit constexpr ClassName                                                  \
 ( in_place_index_with_result_t< 0 > /*next_depth*/                            \
 , std::in_place_index_t< i > /*primary_index*/                                \
 , std::in_place_index_t< 0 > /*secondary_index*/                              \
 , F&& f, P&&... args                                                          \
 ) : member ## i                                                               \
     ( argot_detail::constexpr_invoke( static_cast< F&& >( f )                 \
                                     , static_cast< P&& >( args )...           \
                                     )                                         \
     ) {}                                                                      \
                                                                               \
 template< std::size_t NextDepth, std::size_t SecondaryIndex, class... P >     \
 explicit constexpr ClassName                                                  \
 ( std::in_place_index_t< NextDepth > /*next_depth*/                           \
 , std::in_place_index_t< i > /*primary_index*/                                \
 , std::in_place_index_t< SecondaryIndex > /*secondary_index*/                 \
 , P&&... args                                                                 \
 ) : member ## i                                                               \
     ( std::in_place_index< NextDepth - 1 >                                    \
     , std::in_place_index                                                     \
       < SecondaryIndex / detail_argot::amount_at_depth( NextDepth - 1 ) >     \
     , std::in_place_index                                                     \
       < SecondaryIndex % detail_argot::amount_at_depth( NextDepth - 1 ) >     \
     , static_cast< P&& >( args )...                                           \
     ) {}                                                                      \
                                                                               \
 template< std::size_t NextDepth, std::size_t SecondaryIndex                   \
         , class F, class... P                                                 \
         >                                                                     \
 explicit constexpr ClassName                                                  \
 ( in_place_index_with_result_t< NextDepth > /*next_depth*/                    \
 , std::in_place_index_t< i > /*primary_index*/                                \
 , std::in_place_index_t< SecondaryIndex > /*secondary_index*/                 \
 , F&& f, P&&... args                                                          \
 ) : member ## i                                                               \
     ( in_place_index_with_result< NextDepth - 1 >                             \
     , std::in_place_index                                                     \
       < SecondaryIndex / detail_argot::amount_at_depth( NextDepth - 1 ) >     \
     , std::in_place_index                                                     \
       < SecondaryIndex % detail_argot::amount_at_depth( NextDepth - 1 ) >     \
     , static_cast< F&& >( f ), static_cast< P&& >( args )...                  \
     ) {}                                                                      \
                                                                               \
  using member ## i ## _t = member_type_or_empty< i, T... >;                   \
  ARGOT_NO_UNIQUE_ADDRESS member ## i ## _t member ## i;

#define ARGOT_DETAIL_UNION_IMPL_BODY( ClassName )                              \
  static constexpr std::size_t num_members_v = sizeof...( T );                 \
                                                                               \
  static_assert( num_members_v <= ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH() );       \
                                                                               \
  ARGOT_DETAIL_EXPAND_MAX_UNROLL_DEPTH                                         \
  ( ARGOT_DETAIL_UNION_IMPL_BODY_DECLS, ClassName )

template< std::size_t I >
struct member;

#define ARGOT_DETAIL_UNION_IMPL_MEMBER( i, data )                              \
  template<>                                                                   \
  struct member< i >                                                           \
  {                                                                            \
    template< class Un >                                                       \
    using apply = typename Un::member ## i ## _t;                              \
                                                                               \
    template< class Un >                                                       \
    static constexpr auto pointer_v = &Un::member ## i;                        \
  };

ARGOT_DETAIL_EXPAND_MAX_UNROLL_DEPTH( ARGOT_DETAIL_UNION_IMPL_MEMBER, ~ )

// TODO(mattcalabrese) conditional noexcept
template< std::size_t NextDepth
        , std::size_t PrimaryIndex, std::size_t SecondaryIndex
        , class Un, class... P
        >
inline auto& emplace_union_tree( Un& un, P&&... args )
{
  static_assert( PrimaryIndex < ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH() );

  using type_to_emplace = typename member< PrimaryIndex >::template apply< Un >;
  
  constexpr auto member_to_emplace
    = member< PrimaryIndex >::template pointer_v< Un >;

  if constexpr( NextDepth == 0 )
    return
      *::new
       ( static_cast< void* >
         ( ARGOT_ADDRESSOF( un.*member_to_emplace ) )
       ) type_to_emplace( static_cast< P&& >( args )... );
  else
  {
    constexpr std::size_t next_next_depth = NextDepth - 1;

    constexpr std::size_t next_amount_at_depth
      = detail_argot::amount_at_depth( next_next_depth );

    constexpr std::size_t next_primary_index
      = SecondaryIndex / next_amount_at_depth;

    constexpr std::size_t next_secondary_index
      = SecondaryIndex % next_amount_at_depth;

    return
      *::new
       ( static_cast< void* >
         ( ARGOT_ADDRESSOF( un.*member_to_emplace ) )
       ) type_to_emplace( std::in_place_index< next_next_depth >
                        , std::in_place_index< next_primary_index >
                        , std::in_place_index< next_secondary_index >
                        , static_cast< P&& >( args )...
                        );
  }
}

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
    ( ( *ARGOT_LAUNDER( ARGOT_ADDRESSOF( tree ) ) )
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

#define ARGOT_DETAIL_VISIT_UNION_TREE_CASE( n, data )                          \
  case n:                                                                      \
    if constexpr( n < num_members )                                            \
    {                                                                          \
      if constexpr( Depth == 1 )                                               \
        return std::invoke( static_cast< Fun&& >( fun )                        \
                          , static_cast< Un&& >( un ).member ## n              \
                          );                                                   \
      else                                                                     \
        return ( visit_union_tree< Depth - 1 > )                               \
               ( static_cast< Un&& >( un ).member ## n                         \
               , static_cast< Fun&& >( fun )                                   \
               , index % amount_per_group                                      \
               );                                                              \
    }                                                                          \
    [[fallthrough]];

#define ARGOT_DETAIL_VISIT_UNION_SWITCH_BODY()                                 \
  ARGOT_DETAIL_EXPAND_MAX_UNROLL_DEPTH( ARGOT_DETAIL_VISIT_UNION_TREE_CASE, ~ )

// TODO(mattcalabrese) Make one that works for 2 levels deep.
template< std::size_t Depth, class Un, class Fun >
constexpr decltype( auto )
visit_union_tree( Un&& un, Fun&& fun, std::size_t const index ) noexcept
{
  using nonref_union = std::remove_reference_t< Un >;

  constexpr std::size_t num_members = nonref_union::num_members_v;
  constexpr std::size_t amount_per_group
    = detail_argot::amount_per_group_at_depth( Depth );

  switch( index / amount_per_group )
  {
    ARGOT_DETAIL_VISIT_UNION_SWITCH_BODY();
    default:
      ARGOT_DETAIL_UNREACHABLE();
  }
}

namespace no_default_no_destructor {

template< class... T >
union union_impl
{
  constexpr union_impl() noexcept : dummy() {}
  ~union_impl() noexcept {} // TODO(mattcalabrese) constexpr in C++20

  ARGOT_NO_UNIQUE_ADDRESS empty_member dummy;
  ARGOT_DETAIL_UNION_IMPL_BODY( union_impl )
};

} // namespace argot::detail_union(::no_default_no_destructor)

namespace no_default_has_destructor {

template< class... T >
union union_impl
{
  constexpr union_impl() noexcept : dummy() {}
  ~union_impl() = default;

  ARGOT_NO_UNIQUE_ADDRESS empty_member dummy;
  ARGOT_DETAIL_UNION_IMPL_BODY( union_impl )
};

} // namespace argot::detail_union(::no_default_has_destructor)

namespace has_default_no_destructor {

template< class... T >
union union_impl
{
  union_impl() = default;
  ~union_impl() noexcept {} // TODO(mattcalabrese) constexpr in C++20

  ARGOT_DETAIL_UNION_IMPL_BODY( union_impl )
};

} // namespace argot::detail_union(::has_default_no_destructor)

namespace has_default_has_destructor {

template< class... T >
union union_impl
{
  union_impl() = default;
  ~union_impl() = default;

  ARGOT_DETAIL_UNION_IMPL_BODY( union_impl )
};

} // namespace argot::detail_union(::has_default_has_destructor)

template< class... T >
using form_union_tree = detail_argot::form_tree< union_impl, T... >;

template< class... T >
using form_pure_union = union_< contained< T >... >;

} // namespace argot(::detail_union)
} // namespace argot

#endif  // ARGOT_UNION_DETAIL_UNION_BACKEND_HPP_
