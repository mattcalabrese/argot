/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_HOLDER_HPP_
#define ARGOT_DETAIL_HOLDER_HPP_

#include <argot/concepts/assignable.hpp>
#include <argot/concepts/constructible.hpp>
#include <argot/concepts/convertible.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/rvalue_reference.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/requires.hpp>
#include <argot/identity.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/void_.hpp>

#include <functional>
#include <memory>
#include <type_traits>

namespace argot {
namespace call_detail {

template< class T > struct state_impl;
template< class T > struct access_impl;
template< class T > struct assign_holder_fn;

struct make_holder_type_tag {};

struct make_holder_type_with_result_tag {};

template< class T >
struct holder_type;

// TODO(mattcalabrese) Properly handle cv-qualified void.
template< class T >
struct holder_impl
{
  // TODO(mattcalabrese) Optimize the disjunction.
  using type
    = typename argot_detail::conditional
      < std::is_const_v< T > || std::is_reference_v< T > >
      ::template meta_apply< holder_type, void_to_regular_void_t, T >;
};

template< class T >
using holder = typename holder_impl< T >::type;

template< class T >
struct holder_type;

// TODO(mattcalabrese) Conversion operator to underlying type.
template< class T >
struct holder_type< T const >
{
  friend access_impl< holder_type >;
  friend state_impl< holder_type >;
  friend assign_holder_fn< T const >;
  static_assert( std::is_object_v< T > );

  using state_type = T const;

  holder_type() = default;

  template< class LazyT = T, class... P >
  constexpr holder_type( make_holder_type_tag, P&&... args )
    noexcept( std::is_nothrow_constructible_v< LazyT, P&&... > )
    : v( ARGOT_FORWARD( P )( args )... ) {}

  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Fun&&, P&&... > )
    ( SameType
      < std::remove_cv_t
        < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... > >
      , std::remove_cv_t< T >
      >
    )
    ()
  >
  constexpr holder_type
  ( make_holder_type_with_result_tag, Fun&& fun, P&&... args )
    noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
    : v( argot_detail::constexpr_invoke
         ( ARGOT_FORWARD( Fun )( fun )
         , ARGOT_FORWARD( P )( args )...
         )
       ) {}

  template< class LazyT = T, class Source >
  constexpr holder_type& operator =( Source&& source )
    noexcept( std::is_nothrow_assignable_v< LazyT, Source&& > )
  {
    v = ARGOT_FORWARD( Source )( source );
    return *this;
  }

  template< class LazyT = T, class Source >
  constexpr void reset( Source&& source )
    noexcept( std::is_nothrow_assignable_v< LazyT, Source > )
  {
    v = ARGOT_FORWARD( Source )( source );
  }
 private:
  ARGOT_NO_UNIQUE_ADDRESS T v;
};

// TODO(mattcalabrese) Trivial default-constructor
// TODO(mattcalabrese) Conversion operator to reference
template< class T >
struct holder_type< T& >
{
  friend access_impl< holder_type >;
  friend state_impl< holder_type >;
  friend assign_holder_fn< T& >;
  static_assert( std::is_object_v< T > );

  using state_type = T*;

  constexpr explicit holder_type( make_holder_type_tag, T& v ) noexcept
    : v( std::addressof( v ) ) {}

  constexpr holder_type& operator =( T& other ) noexcept
  {
    v = std::addressof( other );
    return *this;
  }

  constexpr void reset( T& other ) noexcept { v = std::addressof( other ); }
 private:
  T* v;
};

// TODO(mattcalabrese) Trivial default-constructor
// TODO(mattcalabrese) Conversion operator to reference
template< class T >
struct holder_type< T&& >
{
  friend access_impl< holder_type >;
  friend state_impl< holder_type >;
  friend assign_holder_fn< T&& >;
  static_assert( std::is_object_v< T > );

  using state_type = T*;

  constexpr explicit holder_type( make_holder_type_tag, T&& v ) noexcept
    : v( std::addressof( v ) ) {}

  holder_type( holder_type&& ) = default;
  holder_type& operator =( holder_type&& ) = default;

  constexpr holder_type& operator =( T&& other ) noexcept
  {
    v = std::addressof( other );
    return *this;
  }

  constexpr void reset( T&& other ) noexcept { v = std::addressof( other ); }
 private:
  T* v;
};

template< class T >
struct make_holder_type_t
{
  // TODO(mattcalabrese) Constrain.
  template< class Self >
  constexpr holder< T > operator ()( Self&& self ) const
  {
    if constexpr( std::is_reference_v< T > )
      return holder_type< T >( make_holder_type_tag()
                             , ARGOT_FORWARD( Self )( self )
                             );
    else
      if constexpr( std::is_void_v< T > )
        return void_();
      else
        if constexpr( std::is_const_v< T > )
          // TODO(mattcalabrese) use forward_and_sink
          return holder_type< T >
          ( make_holder_type_tag()
          , call_detail::sink( ARGOT_FORWARD( Self )( self ) )
          );
        else
          // TODO(mattcalabrese) use forward_and_sink
          return call_detail::sink( ARGOT_FORWARD( Self )( self ) );
  }
};

template< class T >
inline make_holder_type_t< T > constexpr make_holder{};

template< class T >
struct assign_holder_fn
{
  // TODO(mattcalabrese) noexcept
  template< class Rhs
          , ARGOT_REQUIRES( Assignable< T, Rhs&& > )()
          >
  constexpr T& operator ()( T& lhs, Rhs&& rhs ) const
  {
    lhs = ARGOT_FORWARD( Rhs )( rhs );
    return lhs;
  }
};

template<>
struct assign_holder_fn< void >
{
  constexpr
  holder< void >& operator ()( holder< void >& lhs, void_ /*rhs*/ ) const
  noexcept
  {
    return lhs;
  }
};

template<>
struct assign_holder_fn< void const >
{
  constexpr holder< void const >&
  operator ()( holder< void const >& lhs, void_ /*rhs*/ ) const noexcept
  {
    return lhs;
  }
};

template<>
struct assign_holder_fn< void volatile >
{
  constexpr holder< void volatile >&
  operator ()( holder< void volatile >& lhs, void_ /*rhs*/ ) const noexcept
  {
    return lhs;
  }
};

template<>
struct assign_holder_fn< void const volatile >
{
  constexpr holder< void const volatile >&
  operator ()( holder< void const volatile >& lhs, void_ /*rhs*/ ) const
  noexcept
  {
    return lhs;
  }
};

template< class T >
struct assign_holder_fn< T const >
{
  // TODO(mattcalabrese) noexcept
  template< class Rhs
          , ARGOT_REQUIRES( Assignable< T, Rhs&& > )()
          >
  constexpr T const& operator ()( holder< T const >& lhs, Rhs&& rhs ) const
  {
    lhs.v = ARGOT_FORWARD( Rhs )( rhs );
    return lhs.v;
  }
};

template< class T >
struct assign_holder_fn< T& >
{
  template< class Rhs
          , ARGOT_REQUIRES( Convertible< Rhs&, T& > )()
          >
  constexpr T& operator ()( holder< T& >& lhs, Rhs& rhs ) const noexcept
  {
    T& reference = rhs;
    lhs.v = std::addressof( reference );
    return *lhs.v;
  }
};

template< class T >
struct assign_holder_fn< T&& >
{
  template< class Rhs
          , ARGOT_REQUIRES
            ( RvalueReference< Rhs&& > )
            ( Convertible< Rhs&&, T&& > )
            ()
          >
  constexpr T& operator ()( holder< T&& >& lhs, Rhs&& rhs ) const noexcept
  {
    T&& reference = ARGOT_FORWARD( Rhs )( rhs );
    lhs.v = std::addressof( reference );
    return *lhs.v;
  }
};

template< class T >
constexpr assign_holder_fn< T > assign_holder{};

template< class T >
struct emplace_holder_fn
{
  template< class... P
          , ARGOT_REQUIRES( Constructible< T, P&&... > )()
          >
  constexpr T operator ()( P&&... args ) const
  {
    return T( ARGOT_FORWARD( P )( args )... );
  }
};

template<>
struct emplace_holder_fn< void >
{
  template< class P >
  constexpr void_ operator ()( P&& arg ) const noexcept
  {
    return void_();
  }
};

template<>
struct emplace_holder_fn< void const >
{
  template< class P >
  constexpr void_ operator ()( P&& arg ) const noexcept
  {
    return void_();
  }
};


template<>
struct emplace_holder_fn< void volatile >
{
  template< class P >
  constexpr void_ operator ()( P&& arg ) const noexcept
  {
    return void_();
  }
};

template<>
struct emplace_holder_fn< void volatile const >
{
  template< class P >
  constexpr void_ operator ()( P&& arg ) const noexcept
  {
    return void_();
  }
};

template< class T >
struct emplace_holder_fn< T const >
{
  // TODO(mattcalabrese) Constrain.
  // TODO(mattcalabrese) noexcept.
  template< class... P
          , ARGOT_REQUIRES( Constructible< T, P&&... > )()
          >
  constexpr holder< T const > operator ()( P&&... args ) const
  noexcept( std::is_nothrow_constructible_v< T, P&&... > )
  {
    return holder_type< T const >
    ( make_holder_type_tag()
    , ARGOT_FORWARD( P )( args )...
    );
  }
};

template< class T >
struct emplace_holder_fn< T& >
{
  constexpr holder< T& > operator ()( T& arg ) const noexcept
  {
    return holder_type< T& >( make_holder_type_tag(), arg );
  }
};

template< class T >
struct emplace_holder_fn< T&& >
{
  constexpr holder< T&& > operator ()( T&& arg ) const noexcept
  {
    return holder< T&& >( make_holder_type_tag(), ARGOT_MOVE( arg ) );
  }
};

template< class T >
constexpr emplace_holder_fn< T > emplace_holder{};

template< class T >
struct emplace_holder_with_result_fn
{
  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Fun&&, P&&... > )
    ( SameType
      < std::remove_cv_t
        < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... > >
      , std::remove_cv_t< T >
      >
    )
    ()
  >
  constexpr std::remove_cv_t< T > operator ()( Fun&& fun, P&&... args ) const
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun )
    , ARGOT_FORWARD( P )( args )...
    );
  }
};

template< class T >
struct emplace_holder_with_result_fn< T const >
{
  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Fun&&, P&&... > )
    ( SameType
      < std::remove_cv_t
        < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... > >
      , std::remove_cv_t< T >
      >
    )
    ()
  >
  constexpr holder< T const > operator ()( Fun&& fun, P&&... args ) const
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return holder< T const >
    ( make_holder_type_with_result_tag()
    , ARGOT_FORWARD( Fun )( fun )
    , ARGOT_FORWARD( P )( args )...
    );
  }
};

template< class T >
struct emplace_holder_with_result_fn< T& >
{
  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Fun&&, P&&... > )
    ( SameType
      < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... >, T& >
    )
    ()
  >
  constexpr holder< T& > operator ()( Fun&& fun, P&&... args ) const
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return holder< T& >
    ( make_holder_type_tag()
    , argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Fun )( fun )
      , ARGOT_FORWARD( P )( args )...
      )
    );
  }
};

template< class T >
struct emplace_holder_with_result_fn< T&& >
{
  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Fun&&, P&&... > )
    ( SameType
      < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... >, T&& >
    )
    ()
  >
  constexpr holder< T&& > operator ()( Fun&& fun, P&&... args ) const
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return holder< T&& >
    ( make_holder_type_tag()
    , argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Fun )( fun )
      , ARGOT_FORWARD( P )( args )...
      )
    );
  }
};

template<>
struct emplace_holder_with_result_fn< void >
{
  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( InvocableWith< Fun&&, P&&... > )
    ( SameType
      < std::remove_cv_t
        < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... > >
      , void
      >
    )
    ()
  >
  constexpr void_ operator ()( Fun&& fun, P&&... args ) const
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun )
    , ARGOT_FORWARD( P )( args )...
    );

    return void_();
  }
};

template<>
struct emplace_holder_with_result_fn< void const >
  : emplace_holder_with_result_fn< void > {};

template<>
struct emplace_holder_with_result_fn< void volatile >
  : emplace_holder_with_result_fn< void > {};

template<>
struct emplace_holder_with_result_fn< void volatile const >
  : emplace_holder_with_result_fn< void > {};

template< class T >
constexpr emplace_holder_with_result_fn< T > emplace_holder_with_result{};

template< class T >
struct access_impl
{
  template< class Self >
  static constexpr Self&& run( Self&& self ) noexcept
  {
    return ARGOT_FORWARD( Self )( self );
  }
};

template< class T >
struct state_impl
{
  template< class Self >
  static constexpr Self&& run( Self&& self ) noexcept
  {
    return ARGOT_FORWARD( Self )( self );
  }
};

template< class T >
struct access_impl< holder_type< T > >
{
  template< class Self >
  static constexpr give_qualifiers_to_t< Self&, T > run( Self& self ) noexcept
  {
    return self.v;
  }

  template< class Self >
  static constexpr give_qualifiers_to_t< Self&&, std::remove_const_t< T > >
  run( Self&& self ) noexcept
  {
    return ARGOT_FORWARD( Self )( self ).v;
  }
};

template< class T >
struct access_impl< holder_type< T& > >
{
  template< class Self >
  static constexpr T& run( Self&& self ) noexcept
  {
    return *self.v;
  }
};

template< class T >
struct access_impl< holder_type< T&& > >
{
  template< class Self >
  static constexpr give_qualifiers_to_t< Self&&, T&& >
  run( Self&& self ) noexcept
  {
    return ARGOT_FORWARD( give_qualifiers_to_t< Self&&, T&& > )( *self.v );
  }
};

template< class T >
struct state_impl< holder_type< T > >
{
  template< class Self >
  static constexpr give_qualifiers_to_t
  < Self&&, typename holder_type< T >::state_type >
  run( Self&& self ) noexcept
  {
    return ARGOT_FORWARD( Self )( self ).v;
  }
};

// Requires: T is a valid instantiation of holder_type
struct access_holder_t
{
  template< class T >
  constexpr decltype( auto ) operator()( T&& object ) const noexcept
  {
    return access_impl< remove_cvref_t< T > >
    ::run( ARGOT_FORWARD( T )( object ) );
  }
} inline constexpr access_holder{};

template< bool Condition >
constexpr typename argot_detail::conditional< Condition >::template apply
< access_holder_t
, identity_t
>
access_holder_if{};

// Requires: T is a valid instantiation of holder_type
template< class T >
constexpr decltype( auto ) holder_state( T&& object ) noexcept
{
  return state_impl< remove_cvref_t< T > >::run( ARGOT_FORWARD( T )( object ) );
}

template< class T >
constexpr bool operator ==
( const holder_type< T >& left, const holder_type< T >& right )
noexcept
( noexcept( ( holder_state )( left ) == ( holder_state )( right ) ) )
{
  return ( holder_state )( left ) == ( holder_state )( right );
}

template< class T >
constexpr bool operator !=
( const holder_type< T >& left, const holder_type< T >& right )
noexcept
( noexcept( ( holder_state )( left ) != ( holder_state )( right ) ) )
{
  return ( holder_state )( left ) != ( holder_state )( right );
}

template< class U >
struct holder_compare
{
  // TODO(mattcalabrese) Don't deduce T.
  // TODO(mattcalabrese) Always yield bool?
  template< class T >
  static constexpr
  auto equal( T const& lhs, T const& rhs ) noexcept( noexcept( lhs == rhs ) )
    -> decltype( lhs == rhs )
  {
    return lhs == rhs;
  }

  template< class T >
  static constexpr
  auto not_equal( T const& lhs, T const& rhs )
  noexcept( noexcept( lhs != rhs ) )
    -> decltype( lhs != rhs )
  {
    return lhs != rhs;
  }

  template< class T >
  static constexpr
  auto less( T const& lhs, T const& rhs ) noexcept( noexcept( lhs < rhs ) )
    -> decltype( lhs < rhs )
  {
    return lhs < rhs;
  }

  template< class T >
  static constexpr
  auto greater( T const& lhs, T const& rhs ) noexcept( noexcept( lhs > rhs ) )
    -> decltype( lhs > rhs )
  {
    return lhs > rhs;
  }

  template< class T >
  static constexpr auto less_equal( T const& lhs, T const& rhs )
  noexcept( noexcept( lhs <= rhs ) )
    -> decltype( lhs <= rhs )
  {
    return lhs <= rhs;
  }

  template< class T >
  static constexpr auto greater_equal( T const& lhs, T const& rhs )
  noexcept( noexcept( lhs >= rhs ) )
    -> decltype( lhs >= rhs )
  {
    return lhs >= rhs;
  }
};

template< class T >
constexpr auto operator <
( const holder_type< T >& lhs, const holder_type< T >& rhs )
noexcept
( noexcept
  ( holder_compare< T >::less( ( holder_state )( lhs )
                             , ( holder_state )( rhs )
                             )
  )
)
-> decltype( holder_compare< T >::less( ( holder_state )( lhs )
                                      , ( holder_state )( rhs )
                                      )
           )
{
  return holder_compare< T >::less( ( holder_state )( lhs )
                                  , ( holder_state )( rhs )
                                  );
}

template< class T >
constexpr auto operator <=
( const holder_type< T >& lhs, const holder_type< T >& rhs )
noexcept
( noexcept
  ( holder_compare< T >::less_equal( ( holder_state )( lhs )
                                   , ( holder_state )( rhs )
                                   )
  )
)
-> decltype( holder_compare< T >::less_equal( ( holder_state )( lhs )
                                            , ( holder_state )( rhs )
                                            )
           )
{
  return holder_compare< T >::less_equal( ( holder_state )( lhs )
                                        , ( holder_state )( rhs )
                                        );
}

template< class T >
constexpr auto operator >=
( const holder_type< T >& lhs, const holder_type< T >& rhs )
noexcept
( noexcept
  ( holder_compare< T >::greater_equal( ( holder_state )( lhs )
                                      , ( holder_state )( rhs )
                                      )
  )
)
-> decltype( holder_compare< T >::greater_equal( ( holder_state )( lhs )
                                               , ( holder_state )( rhs )
                                               )
           )
{
  return holder_compare< T >::greater_equal( ( holder_state )( lhs )
                                           , ( holder_state )( rhs )
                                           );
}

template< class T >
constexpr auto operator >
( const holder_type< T >& lhs, const holder_type< T >& rhs )
noexcept
( noexcept
  ( holder_compare< T >::greater( ( holder_state )( lhs )
                                , ( holder_state )( rhs )
                                )
  )
)
-> decltype( holder_compare< T >::greater( ( holder_state )( lhs )
                                         , ( holder_state )( rhs )
                                         )
           )
{
  return holder_compare< T >::greater( ( holder_state )( lhs )
                                     , ( holder_state )( rhs )
                                     );
}

// TODO(mattcalabrese) Make swap and hash

}  // namespace argot::call_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_HOLDER_HPP_
