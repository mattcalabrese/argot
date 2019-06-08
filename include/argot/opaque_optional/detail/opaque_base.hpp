/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPAQUE_OPTIONAL_OPAQUE_BASE_HPP_
#define ARGOT_OPAQUE_OPTIONAL_OPAQUE_BASE_HPP_

#include <argot/concepts/comparable.hpp>
#include <argot/concepts/constructible.hpp>
#include <argot/concepts/convertible.hpp>
#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/default_constructible.hpp>
#include <argot/concepts/equatable.hpp>
#include <argot/concepts/emplaceable_when_contained.hpp>
#include <argot/concepts/emplaceable_with_result_when_contained.hpp>
#include <argot/concepts/hashable.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/nothrow_constructible.hpp>
#include <argot/concepts/nothrow_convertible.hpp>
#include <argot/concepts/nothrow_copy_constructible.hpp>
#include <argot/concepts/nothrow_destructible.hpp>
#include <argot/concepts/nothrow_move_constructible.hpp>
#include <argot/concepts/nothrow_hashable.hpp>
#include <argot/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/constexpr_swap.hpp>
#include <argot/detail/regular_bases.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/in_place_default_init.hpp>
#include <argot/in_place_with_result.hpp>
#include <argot/move.hpp>
#include <argot/state_traits/equal_to.hpp>
#include <argot/state_traits/greater_equal.hpp>
#include <argot/state_traits/greater_than.hpp>
#include <argot/state_traits/hash_combine.hpp>
#include <argot/state_traits/less_equal.hpp>
#include <argot/state_traits/less_than.hpp>
#include <argot/state_traits/not_equal_to.hpp>

#include <boost/assert.hpp>

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <memory>

namespace argot::detail_opaque {

template< std::nullptr_t, class T >
struct nullptr_always
{
  using type = T;
};

template< std::nullptr_t nullptr_value, class T >
using nullptr_always_t = typename nullptr_always< nullptr_value, T >::type;

template< template< class > class Kind >
struct opaque_operator_base
{
  template< class T
          , ARGOT_REQUIRES( Equatable< T > )()
          >
  friend constexpr bool operator==( Kind<T> const& lhs, Kind<T> const& rhs )
  noexcept
  ( noexcept
    ( state_traits::equal_to< T >
      ( ARGOT_DECLVAL( T const& )
      , ARGOT_DECLVAL( T const& )
      )
    )
  )
  {
    return    lhs.has_value() == rhs.has_value()
           && ( !lhs.has_value() || state_traits::equal_to< T >( *lhs, *rhs ) );
  }

  template< class T
          , ARGOT_REQUIRES( Equatable< T > )()
          >
  friend constexpr bool operator!=( Kind<T> const& lhs, Kind<T> const& rhs )
  noexcept
  ( noexcept
    ( state_traits::not_equal_to< T >
      ( ARGOT_DECLVAL( T const& )
      , ARGOT_DECLVAL( T const& )
      )
    )
  )
  {
    return    lhs.has_value() != rhs.has_value()
           || (    lhs.has_value()
                && state_traits::not_equal_to< T >( *lhs, *rhs )
              );
  }

  template< class T
          , ARGOT_REQUIRES( Comparable< T > )()
          >
  friend constexpr bool operator<( Kind<T> const& lhs, Kind<T> const& rhs )
  noexcept
  ( noexcept
    ( state_traits::less_than< T >
      ( ARGOT_DECLVAL( T const& )
      , ARGOT_DECLVAL( T const& )
      )
    )
  )
  {
    return    ( !lhs.has_value() && rhs.has_value() )
           || (    lhs.has_value() && rhs.has_value()
                && state_traits::less_than< T >( *lhs, *rhs )
              );
  }

  template< class T
          , ARGOT_REQUIRES( Comparable< T > )()
          >
  friend constexpr bool operator<=( Kind<T> const& lhs, Kind<T> const& rhs )
  noexcept
  ( noexcept
    ( state_traits::less_equal< T >
      ( ARGOT_DECLVAL( T const& )
      , ARGOT_DECLVAL( T const& )
      )
    )
  )
  {
    return    !lhs.has_value()
           || (    rhs.has_value()
                && state_traits::less_equal< T >( *lhs, *rhs )
              );
  }

  template< class T
          , ARGOT_REQUIRES( Comparable< T > )()
          >
  friend constexpr bool operator>=( Kind<T> const& lhs, Kind<T> const& rhs )
  noexcept
  ( noexcept
    ( state_traits::greater_equal< T >
      ( ARGOT_DECLVAL( T const& )
      , ARGOT_DECLVAL( T const& )
      )
    )
  )
  {
    return    !rhs.has_value()
           || (    lhs.has_value()
                && state_traits::greater_equal< T >( *lhs, *rhs )
              );
  }

  template< class T
          , ARGOT_REQUIRES( Comparable< T > )()
          >
  friend constexpr bool operator>( Kind<T> const& lhs, Kind<T> const& rhs )
  noexcept
  ( noexcept
    ( state_traits::greater_than< T >
      ( ARGOT_DECLVAL( T const& )
      , ARGOT_DECLVAL( T const& )
      )
    )
  )
  {
    return    ( lhs.has_value() && !rhs.has_value() )
           || (    lhs.has_value() && rhs.has_value()
                && state_traits::greater_than< T >( *lhs, *rhs )
              );
  }

  template< class T >
  friend constexpr void swap( Kind<T>& lhs, Kind<T>& rhs ) noexcept
  {
    lhs.swap( rhs );
  }
};

// TODO(mattcalabrese) Allocator support
template< template< class > class Kind, class T >
class opaque_base
  : opaque_operator_base< Kind >
{
  ARGOT_CONCEPT_ASSERT( DecayedType< T > );
 public:
  static
  Kind< T >& detail_move_assign( Kind< T >& lhs, Kind< T >&& rhs ) noexcept
  {
    if constexpr( std::is_nothrow_move_assignable_v< T > )
      if( lhs.has_value() && rhs.has_value() )
      {
        *lhs.target = ARGOT_MOVE( *rhs );
        return lhs;
      }

    lhs.reset();
    lhs.target = rhs.target;
    rhs.target = nullptr;
    return lhs;
  }

  static Kind< T >& detail_copy_assign( Kind< T >& lhs, Kind< T > const& rhs )
  {
    if constexpr( !std::is_copy_constructible_v< T > )
      static_assert( std::is_copy_constructible_v< T > );
    else
      if( lhs.has_value() )
        if( rhs.has_value() )
          if constexpr( std::is_copy_assignable_v< T > )
            *lhs.target = *rhs;
          else
          {
            if( std::addressof( lhs ) != std::addressof( rhs ) )
            {
              lhs.reset();
              lhs.target = ::new T( *rhs );
            }
          }
        else
          lhs.reset();
      else
        if( rhs.has_value() )
        {
          lhs.reset();
          lhs.target = ::new T( *rhs );
        }

    return lhs;
  }

  template< std::nullptr_t nullptr_value = nullptr
          , ARGOT_REQUIRES
            ( MoveConstructible< nullptr_always_t< nullptr_value, T > > )
            ()
          >
  T& assign( nullptr_always_t< nullptr_value, T >&& rhs )
  {
    if constexpr( std::is_move_assignable_v< T > )
      if( has_value() )
      {
        **this = ARGOT_MOVE( rhs );
        return **this;
      }

    static_cast< Kind< T >& >( *this )
      = Kind< T >( std::in_place, ARGOT_MOVE( rhs ) );

    return **this;
  }

  template< std::nullptr_t nullptr_value = nullptr
          , ARGOT_REQUIRES
            ( CopyConstructible< nullptr_always_t< nullptr_value, T > > )
            ()
          >
  T& assign( nullptr_always_t< nullptr_value, T > const& rhs )
  {
    if constexpr( std::is_copy_assignable_v< T > )
      if( has_value() )
      {
        **this = rhs;
        return **this;
      }

    static_cast< Kind< T >& >( *this ) = Kind< T >( std::in_place, rhs );

    return **this;
  }

  constexpr bool has_value() const noexcept
  {
    return static_cast< Kind< T > const& >( *this ).target != nullptr;
  }

  void reset() noexcept
  {
    static_assert
    ( sizeof( T ) != 0
    , "T must be complete when calling .reset()."
    );

    ARGOT_CONCEPT_ASSERT( NothrowDestructible< T > );

    T*& target = static_cast< Kind< T >& >( *this ).target;

    delete target;
    target = nullptr;
  }

  template< class... P
          , ARGOT_REQUIRES( Constructible< T, P&&... > )()
          >
  T& emplace( P&&... args )
  {
    static_cast< Kind< T >& >( *this )
      = Kind< T >( std::in_place, ARGOT_FORWARD( P )( args )... );

    return **this;
  }

  template
  < class U, class... P
  , ARGOT_REQUIRES( Constructible< T, std::initializer_list< U >&, P&&... > )()
  >
  T& emplace( std::initializer_list< U > ilist, P&&... args )
  {
    static_cast< Kind< T >& >( *this )
      = Kind< T >( std::in_place, ilist, ARGOT_FORWARD( P )( args )... );

    return **this;
  }

  template< class Fun, class... P
          , ARGOT_REQUIRES
            ( EmplaceableWithResultWhenContained< T, Fun&&, P&&... > )()
          >
  T& emplace_with_result( Fun&& fun, P&&... args )
  {
    static_cast< Kind< T >& >( *this )
      = Kind< T >( in_place_with_result
                 , ARGOT_FORWARD( Fun )( fun )
                 , ARGOT_FORWARD( P )( args )...
                 );

    return **this;
  }

  // TODO(calabrese) Check default init insead of value init.
  template< std::nullptr_t nullptr_value = nullptr
          , ARGOT_REQUIRES
            ( DefaultConstructible< nullptr_always_t< nullptr_value, T > > )()
          >
  T& emplace_default_init()
  {
    static_cast< Kind< T >& >( *this ) = Kind< T >( in_place_default_init );
    return **this;
  }

  constexpr T& operator*()& noexcept
  {
    BOOST_ASSERT( has_value() );
    return *static_cast< Kind< T >& >( *this ).target;
  }

  constexpr T const& operator*() const& noexcept
  {
    BOOST_ASSERT( has_value() );
    return *static_cast< Kind< T > const& >( *this ).target;
  }

  constexpr T&& operator*()&& noexcept
  {
    BOOST_ASSERT( has_value() );
    return ARGOT_MOVE( *static_cast< Kind< T >& >( *this ).target );
  }

  constexpr T const&& operator*() const&& noexcept
  {
    BOOST_ASSERT( has_value() );
    return ARGOT_MOVE( *static_cast< Kind< T > const& >( *this ).target );
  }

  constexpr T* operator->() noexcept
  {
    BOOST_ASSERT( has_value() );
    return static_cast< Kind< T >& >( *this ).target;
  }

  constexpr T const* operator->() const noexcept
  {
    BOOST_ASSERT( has_value() );
    return static_cast< Kind< T > const& >( *this ).target;
  }

  constexpr void swap( Kind< T >& other ) noexcept
  {
    detail_argot_swap::constexpr_swap
    ( static_cast< Kind< T >& >( *this ).target, other.target );
  }
};

template< class T >
struct hash_base_impl
{
  constexpr std::size_t operator()( T const& self ) const
  noexcept(    ARGOT_IS_MODELED( NothrowHashable< bool > )
            && ARGOT_IS_MODELED( NothrowHashable< typename T::element_type > )
          )
  {
    bool const has_value = self.has_value();
    std::size_t hash_value = std::hash< bool >()( has_value );

    if( has_value )
      state_traits::hash_combine< typename T::element_type >
      ( hash_value, *self );

    return hash_value;
  }
};

template< class T >
struct hash_base
  : argot_detail::conditional
    < ARGOT_IS_MODELED( Hashable< typename T::element_type > ) >
    ::template half_meta_apply
    < hash_base_impl
    , detail_regular_bases::tainted_hash
    , T
    > {};

} // namespace (argot::detail_opaque)

#endif // ARGOT_OPAQUE_OPTIONAL_OPAQUE_BASE_HPP_
