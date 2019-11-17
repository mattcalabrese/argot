/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_
#define ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_

#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_swap.hpp>
#include <argot/detail/variadic_chunk.hpp>
#include <argot/detail/variadic_range.hpp>
#include <argot/in_place_with_result.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/same_type_or_fail.hpp>
#include <argot/reducer/to.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace argot {

namespace detail_struct {

// TODO(mattcalabrese) Make this intrinsic to struct_base
template< class... P >
constexpr auto make_argument_expander( P&&... args ) noexcept
{
  return [ & ]( auto&& fun ) -> decltype( auto )
  {
    // TODO(mattcalabrese) invoke
    return ARGOT_FORWARD( decltype( fun ) )( fun )
    ( ARGOT_FORWARD( P )( args )... );
  };
}

template< class T >
constexpr auto make_unpack_argument_expander( T&& sub_struct ) noexcept
{
  return sub_struct.unpack
  ( [ & ]( auto&&... elems )
    {
      return [ & ]( auto&& fun ) -> decltype( auto )
      {
        // TODO(mattcalabrese) invoke
        return ARGOT_FORWARD( decltype( fun ) )( fun )
        ( ARGOT_FORWARD( decltype( elems ) )( elems )... );
      };
    }
  , ARGOT_FORWARD( T )( sub_struct )
  );
}

template< class Expander0 >
constexpr Expander0 const&
combine_argument_expanders( Expander0 const& expander0 ) noexcept
{
  return expander0;
}

template< class Expander0, class Expander1, class... TailExpanders >
constexpr auto combine_argument_expanders
( Expander0 const& expander0
, Expander1 const& expander1
, TailExpanders const&... tail_expanders
) noexcept
{
  return ( combine_argument_expanders )
  ( expander0
    ( [ & ]( auto&&... args0 )
      {
        return expander1
        ( [ & ]( auto&&... args1 )
          {
            return [ & ]( auto&& fun ) -> decltype( auto )
            {
              // TODO(mattcalabrese) invoke
              return ARGOT_FORWARD( decltype( fun ) )( fun )
              ( ARGOT_FORWARD( decltype( args0 ) )( args0 )...
              , ARGOT_FORWARD( decltype( args1 ) )( args1 )...
              );
            };
          }
        );
      }
    )
  , tail_expanders...
  );
}

template< class... T >
struct struct_base;

template<>
struct struct_base<>
{
  static constexpr std::size_t num_members_v = 0;

  struct_base() = default;
  explicit constexpr struct_base( std::in_place_t ) noexcept {}
  explicit constexpr struct_base( in_place_with_result_t ) noexcept {}

  template< class Fun, class Self >
  static constexpr decltype( auto ) unpack( Fun&& fun, Self&& )
  {
    return ARGOT_FORWARD( Fun )( fun )();
  }

  friend constexpr bool
  operator ==( struct_base const&, struct_base const& ) noexcept
  {
    return true;
  }

  friend constexpr bool
  operator <( struct_base const&, struct_base const& ) noexcept
  {
    return false;
  }

  constexpr void swap( struct_base& ) noexcept {}
};

template< std::size_t Index >
struct struct_impl_preprocessed;

template< std::size_t Index >
struct struct_impl_variadic;

template< std::size_t NumElements, std::size_t Index >
using struct_impl
  = typename argot_detail::conditional
    < NumElements <= ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS >
    ::template meta_apply_values
    < struct_impl_preprocessed
    , struct_impl_variadic
    , Index
    >;

// TODO(mattcalabrese) Eliminate this form of memoization to increase throughput
template< class... T >
using sub_struct_base_t
  = detail_argot::variadic_chunk
    < ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS
    , struct_base, struct_base
    , T...
    >;

template< std::size_t Index >
struct struct_impl_variadic
{
  static constexpr std::size_t primary_index
    = Index / ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS;

  static constexpr std::size_t secondary_index
    = Index % ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS;

  template< class ElementType, class StructBase >
  static constexpr auto&& get( StructBase&& self ) noexcept
  {
    using primary_struct_base_impl
      = struct_impl
        < std::remove_reference_t< StructBase >::num_members_v
        , primary_index
        >;

    using qualified_alt
      = call_detail::give_qualifiers_to_t< StructBase&&, ElementType >;

    return static_cast< qualified_alt >
    ( struct_impl
      < std::remove_reference_t< StructBase >::num_members_v
      , secondary_index
      >::template get< ElementType >
      ( primary_struct_base_impl::template get
        < primary_struct_base_impl::template expand_members_t
          < primary_struct_base_impl::template member_type_t >
        >
        ( ARGOT_FORWARD( StructBase )( self ).sub_struct_base )
      )
    );
  }
};

struct make_struct_base_element_maker_with_result_fn
{
  template< class... Funs >
  constexpr auto operator ()( Funs&&... funs ) const noexcept
  {
    // TODO(mattcalabrese) conditional noexcept
    return [ & ]( auto* ptr_to_type )
    {
      return [ & ]
      {
        return std::remove_pointer_t< decltype( ptr_to_type ) >
        ( in_place_with_result, ARGOT_FORWARD( Funs )( funs )... );
      };
    };
  }
};

struct make_struct_base_element_maker_fn
{

  template< class... P >
  constexpr auto operator ()( P&&... args ) const noexcept
  {
    // TODO(mattcalabrese) conditional noexcept
    return [ & ]( auto* ptr_to_type )
    {
      return [ & ]
      {
        return std::remove_pointer_t< decltype( ptr_to_type ) >
        ( std::in_place, ARGOT_FORWARD( P )( args )... );
      };
    };
  }
};

template< class... T >
struct make_struct_base_element_fn
{
  template< class Maker >
  constexpr decltype( auto ) operator ()( Maker const& maker ) const
  {
    return maker( static_cast< struct_base< T... >* >( nullptr ) );
  }
};

template< class ChunkIndices, class... T >
struct make_struct_base_in_place_fn;

template< std::size_t... ChunkIndices, class... T >
struct make_struct_base_in_place_fn
< std::index_sequence< ChunkIndices... >, T... >
{
  // TODO(mattcalabrese) conditional noexcept
  template< class... Makers >
  constexpr auto operator ()( Makers const&... makers ) const
  {
    constexpr bool final_chunk_is_partial
      = sizeof...( T ) % ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS != 0;

    return sub_struct_base_t< T... >
    ( in_place_with_result
    , detail_argot::variadic_sized_range
      < ChunkIndices * ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS
      ,      final_chunk_is_partial
          && ChunkIndices == sizeof...( ChunkIndices ) - 1
        ? sizeof...( T ) % ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS
        : ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS
      , make_struct_base_element_fn
      , T...
      >()( makers )...
    );
  }
};

template< class... T >
struct struct_base
{
  using sub_struct_base_impl_t = sub_struct_base_t< T... >;

  static constexpr std::size_t num_members_v = sizeof...( T );

  template< template< class... > class Result >
  using expand_members_t = Result< T... >;

  struct_base() = default;

  // TODO(mattcalabrese) Conditional noexcept
  template< class... P >
  explicit constexpr struct_base( std::in_place_t, P&&... args )
    : sub_struct_base
      ( detail_argot::variadic_chunk_impl
        < std::make_index_sequence
          < sizeof...( T ) / ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS >
        , sizeof...( T ) % ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS != 0
        >::template run< ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS >
        ( make_struct_base_element_maker_fn()
        , make_struct_base_in_place_fn
          < std::make_index_sequence
            <   sizeof...( T ) / ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS
              + (   sizeof...( T ) % ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS == 0
                  ? 0
                  : 1
                )
            >
          , T...
          >()
        , ARGOT_FORWARD( P )( args )...
        )
      )
  {}

  // TODO(mattcalabrese) Conditional noexcept
  template< class... Funs >
  explicit constexpr struct_base( in_place_with_result_t, Funs&&... funs )
    : sub_struct_base
      ( detail_argot::variadic_chunk_impl
        < std::make_index_sequence
          < sizeof...( T ) / ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS >
        , sizeof...( T ) % ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS != 0
        >::template run< ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS >
        ( make_struct_base_element_maker_with_result_fn()
        , make_struct_base_in_place_fn
          < std::make_index_sequence
            <   sizeof...( T ) / ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS
              + (   sizeof...( T ) % ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS == 0
                  ? 0
                  : 1
                )
            >
          , T...
          >()
        , ARGOT_FORWARD( Funs )( funs )...
        )
      )
  {}

  // TODO(mattcalabrese) conditional noexcept
  template< class Fun, class Self >
  static constexpr decltype( auto ) unpack( Fun&& fun, Self&& self )
  {
    return sub_struct_base_impl_t::unpack
    ( [ & ]( auto&&... subs ) -> decltype( auto )
      {
        return ( combine_argument_expanders )
        ( ( make_unpack_argument_expander )
          ( ARGOT_FORWARD( decltype( subs ) )( subs ) )...
        )
        ( ARGOT_FORWARD( Fun )( fun ) );
      }
    , ARGOT_FORWARD( Self )( self ).sub_struct_base
    );
  }

  // TODO(mattcalabrese) Noexcept
  friend
  constexpr bool operator ==( struct_base const& lhs, struct_base const& rhs )
  {
    return lhs.sub_struct_base == rhs.sub_struct_base;
  }

  // TODO(mattcalabrese) Noexcept
  friend
  constexpr bool operator <( struct_base const& lhs, struct_base const& rhs )
  {
    return lhs.sub_struct_base < rhs.sub_struct_base;
  }

  // TODO(mattcalabrese) Noexcept
  constexpr void swap( struct_base& other )
  {
    return sub_struct_base.swap( other.sub_struct_base );
  }

  ARGOT_NO_UNIQUE_ADDRESS sub_struct_base_impl_t sub_struct_base;
};

}  // namespace argot(::detail_struct)
}  // namespace argot

#endif  // ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_
