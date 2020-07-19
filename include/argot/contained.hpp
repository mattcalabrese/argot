/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONTAINED_HPP_
#define ARGOT_CONTAINED_HPP_

//[description
/*`
argot::contained is a facility for generic code that allows the developer to
encapsulate and manipulate instances of types in a way such the associated
operations behave as though they were of a =Regular= type, even if those
operations when applied directly would otherwise differ in semantics.

It is a unary template-alias that is a referential identity operation if the
passed-in template argument, `T`, is an unqualified object type, otherwise:

* If `T` is a reference type, `contained< T >` is a type for which its value is
  considered to be the address of the target object. It is move-only if `T` is
  an rvalue reference type.
* If `T` is a c-style array type, `contained< T >` has the same =Regular=
  operations as the element type, as appropriately applied to all elements.
* If `T` is `void`, it behaves as `argot::void_`.
* If `T` is a const-qualified object type, `contained< T >` has the same
  properties as its const-unqualified form.
*/
//]

#include <argot/concepts/assignable.hpp>
#include <argot/concepts/constructible.hpp>
#include <argot/concepts/convertible.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/nothrow_assignable.hpp>
#include <argot/concepts/object.hpp>
#include <argot/concepts/rvalue_reference.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/referential_identity.hpp>
#include <argot/void_.hpp>

#include <functional>
#include <memory>
#include <type_traits>

// TODO(mattcalabrese) Support arrays.

namespace argot {

namespace detail_contained {

template< class T > struct state_impl;
template< class T > struct access_impl;

struct make_contained_tag {};

struct make_containment_wrapper_with_result_tag {};

} // namespace argot(::detail_contained)

namespace detail_contained_adl {

template< class Child > struct adl_base {};

} // namespace argot(::detail_contained_adl)

template< class T >
struct containment_wrapper;

template< class T >
constexpr bool is_containment_wrapper_v = false;

template< class T >
constexpr bool is_containment_wrapper_v< containment_wrapper< T > > = false;

// TODO(mattcalabrese) Inline this directly in "contained" and make a lazy form.
template< class T >
struct contained_impl
{
  // TODO(mattcalabrese) Optimize the disjunction.
  using type
    = typename argot_detail::conditional
      < std::is_const_v< T > || std::is_reference_v< T > >
      ::template meta_apply< containment_wrapper, void_to_regular_void_t, T >;
};

template< class T >
using contained = typename contained_impl< T >::type;

template< class T >
struct containment_wrapper;

template< class T > struct assign_contained_fn;
template< class T > struct make_contained_fn;
template< class T > struct emplace_contained_fn;
template< class T > struct emplace_contained_with_result_fn;

template< class T >
struct containment_wrapper< T const >
  : detail_contained_adl::adl_base< containment_wrapper< T const > >
{
  ARGOT_CONCEPT_ASSERT( Object< T > );

  friend detail_contained::access_impl< containment_wrapper >;
  friend detail_contained::state_impl< containment_wrapper >;
  friend make_contained_fn< T const >;
  friend assign_contained_fn< T const >;
  friend emplace_contained_fn< T const >;
  friend emplace_contained_with_result_fn< T const >;

  containment_wrapper() = default;
 private:
  using state_type = T const;

  template< class LazyT = T, class... P >
  constexpr containment_wrapper
  ( detail_contained::make_contained_tag, P&&... args )
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
  constexpr containment_wrapper
  ( detail_contained::make_containment_wrapper_with_result_tag
  , Fun&& fun, P&&... args
  )
    noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
    : v( argot_detail::constexpr_invoke
         ( ARGOT_FORWARD( Fun )( fun )
         , ARGOT_FORWARD( P )( args )...
         )
       ) {}
 private:
  // TODO(calabrese) swap

  ARGOT_NO_UNIQUE_ADDRESS T v;
};

template< class T >
struct containment_wrapper< T& >
  : detail_contained_adl::adl_base< containment_wrapper< T& > >
{
  friend detail_contained::access_impl< containment_wrapper >;
  friend detail_contained::state_impl< containment_wrapper >;
  friend make_contained_fn< T& >;
  friend assign_contained_fn< T& >;
  friend emplace_contained_fn< T& >;
  friend emplace_contained_with_result_fn< T& >;

  containment_wrapper() = default;
 private:
  using state_type = T*;

  constexpr explicit containment_wrapper
  ( detail_contained::make_contained_tag, T& v ) noexcept
    : v( std::addressof( v ) ) {}
 private:
  friend constexpr
  void swap( containment_wrapper& lhs, containment_wrapper& rhs ) noexcept {
      T* const temp = lhs.v;
      lhs.v = rhs.v;
      rhs.v = temp;
  }

  T* v;
};

template< class T >
struct containment_wrapper< T&& >
  : detail_contained_adl::adl_base< containment_wrapper< T&& > >
{
  friend detail_contained::access_impl< containment_wrapper >;
  friend detail_contained::state_impl< containment_wrapper >;
  friend make_contained_fn< T&& >;
  friend assign_contained_fn< T&& >;
  friend emplace_contained_fn< T&& >;
  friend emplace_contained_with_result_fn< T&& >;

  containment_wrapper() = default;
  containment_wrapper( containment_wrapper&& ) = default;
  containment_wrapper& operator =( containment_wrapper&& ) = default;
 private:
  using state_type = T*;

  constexpr explicit containment_wrapper
  ( detail_contained::make_contained_tag, T&& v ) noexcept
    : v( std::addressof( v ) ) {}
 private:
  friend constexpr
  void swap( containment_wrapper& lhs, containment_wrapper& rhs ) noexcept {
      T* const temp = lhs.v;
      lhs.v = rhs.v;
      rhs.v = temp;
  }

  T* v;
};

template< class T >
struct make_contained_fn
{
  // TODO(mattcalabrese) Constrain.
  template< class Self >
  constexpr contained< T > operator ()( Self&& self ) const
  {
    if constexpr( std::is_reference_v< T > )
      return containment_wrapper< T >
      ( detail_contained::make_contained_tag()
      , ARGOT_FORWARD( Self )( self )
      );
    else
      if constexpr( std::is_void_v< T > )
        return void_();
      else
        if constexpr( std::is_const_v< T > )
          // TODO(mattcalabrese) use forward_and_sink
          return containment_wrapper< T >
          ( detail_contained::make_contained_tag()
          , call_detail::sink( ARGOT_FORWARD( Self )( self ) )
          );
        else
          // TODO(mattcalabrese) use forward_and_sink
          return call_detail::sink( ARGOT_FORWARD( Self )( self ) );
  }
};

template< class T >
inline make_contained_fn< T > constexpr make_contained{};

template< class T >
struct assign_contained_fn
{
  template< class Rhs
          , ARGOT_REQUIRES( Assignable< T, Rhs&& > )()
          >
  constexpr T& operator ()( T& lhs, Rhs&& rhs ) const
  noexcept( ARGOT_IS_MODELED( NothrowAssignable< T, Rhs&& > ) )
  {
    lhs = ARGOT_FORWARD( Rhs )( rhs );
    return lhs;
  }
};

template<>
struct assign_contained_fn< void >
{
  constexpr
  contained< void >& operator ()( contained< void >& lhs, void_ /*rhs*/ ) const
  noexcept
  {
    return lhs;
  }
};

template<>
struct assign_contained_fn< void const >
{
  constexpr contained< void const >&
  operator ()( contained< void const >& lhs, void_ /*rhs*/ ) const noexcept
  {
    return lhs;
  }
};

template<>
struct assign_contained_fn< void volatile >
{
  constexpr contained< void volatile >&
  operator ()( contained< void volatile >& lhs, void_ /*rhs*/ ) const noexcept
  {
    return lhs;
  }
};

template<>
struct assign_contained_fn< void const volatile >
{
  constexpr contained< void const volatile >&
  operator ()( contained< void const volatile >& lhs, void_ /*rhs*/ ) const
  noexcept
  {
    return lhs;
  }
};

template< class T >
struct assign_contained_fn< T const >
{
  // TODO(mattcalabrese) noexcept
  template< class Rhs
          , ARGOT_REQUIRES( Assignable< T, Rhs&& > )()
          >
  constexpr T const& operator ()( contained< T const >& lhs, Rhs&& rhs ) const
  noexcept( ARGOT_IS_MODELED( NothrowAssignable< T, Rhs&& > ) )
  {
    lhs.v = ARGOT_FORWARD( Rhs )( rhs );
    return lhs.v;
  }
};

template< class T >
struct assign_contained_fn< T& >
{
  template< class Rhs
          , ARGOT_REQUIRES( Convertible< Rhs&, T& > )()
          >
  constexpr T& operator ()( contained< T& >& lhs, Rhs& rhs ) const noexcept
  {
    T& reference = rhs;
    lhs.v = std::addressof( reference );
    return *lhs.v;
  }
};

template< class T >
struct assign_contained_fn< T&& >
{
  // TODO(mattcalabrese) Fix constraints.
  template< class Rhs
          , ARGOT_REQUIRES
            ( RvalueReference< Rhs&& > )
            ( Convertible< Rhs&&, T&& > )
            ()
          >
  constexpr T& operator ()( contained< T&& >& lhs, Rhs&& rhs ) const noexcept
  {
    T&& reference = ARGOT_MOVE( rhs );
    lhs.v = std::addressof( reference );
    return *lhs.v;
  }
};

template< class T >
constexpr assign_contained_fn< T > assign_contained{};

template< class T >
struct emplace_contained_fn
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
struct emplace_contained_fn< void >
{
  template< class P >
  constexpr void_ operator ()( P&& arg ) const noexcept
  {
    return void_();
  }
};

template<>
struct emplace_contained_fn< void const >
  : emplace_contained_fn< void >{};

template<>
struct emplace_contained_fn< void volatile >
  : emplace_contained_fn< void >{};

template<>
struct emplace_contained_fn< void volatile const >
  : emplace_contained_fn< void >{};

template< class T >
struct emplace_contained_fn< T const >
{
  template< class... P
          , ARGOT_REQUIRES( Constructible< T, P&&... > )()
          >
  constexpr contained< T const > operator ()( P&&... args ) const
  noexcept( std::is_nothrow_constructible_v< T, P&&... > )
  {
    return containment_wrapper< T const >
    ( detail_contained::make_contained_tag()
    , ARGOT_FORWARD( P )( args )...
    );
  }
};

template< class T >
struct emplace_contained_fn< T& >
{
  constexpr contained< T& > operator ()( T& arg ) const noexcept
  {
    return containment_wrapper< T& >
    ( detail_contained::make_contained_tag(), arg );
  }
};

template< class T >
struct emplace_contained_fn< T&& >
{
  constexpr contained< T&& > operator ()( T&& arg ) const noexcept
  {
    return contained< T&& >
    ( detail_contained::make_contained_tag(), ARGOT_MOVE( arg ) );
  }
};

template< class T >
constexpr emplace_contained_fn< T > emplace_contained{};

template< class T >
struct emplace_contained_with_result_fn
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
struct emplace_contained_with_result_fn< T const >
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
  constexpr contained< T const > operator ()( Fun&& fun, P&&... args ) const
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return contained< T const >
    ( detail_contained::make_containment_wrapper_with_result_tag()
    , ARGOT_FORWARD( Fun )( fun )
    , ARGOT_FORWARD( P )( args )...
    );
  }
};

template< class T >
struct emplace_contained_with_result_fn< T& >
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
  constexpr contained< T& > operator ()( Fun&& fun, P&&... args ) const
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return contained< T& >
    ( detail_contained::make_contained_tag()
    , argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Fun )( fun )
      , ARGOT_FORWARD( P )( args )...
      )
    );
  }
};

template< class T >
struct emplace_contained_with_result_fn< T&& >
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
  constexpr contained< T&& > operator ()( Fun&& fun, P&&... args ) const
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  {
    return contained< T&& >
    ( detail_contained::make_contained_tag()
    , argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Fun )( fun )
      , ARGOT_FORWARD( P )( args )...
      )
    );
  }
};

template<>
struct emplace_contained_with_result_fn< void >
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
struct emplace_contained_with_result_fn< void const >
  : emplace_contained_with_result_fn< void > {};

template<>
struct emplace_contained_with_result_fn< void volatile >
  : emplace_contained_with_result_fn< void > {};

template<>
struct emplace_contained_with_result_fn< void volatile const >
  : emplace_contained_with_result_fn< void > {};

// TODO(mattcalabrese) Resolve to non-template identity when able.
template< class T >
constexpr emplace_contained_with_result_fn< T > emplace_contained_with_result{};

namespace detail_contained {

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
struct access_impl< containment_wrapper< T > >
{
  template< class Self >
  static constexpr call_detail::give_qualifiers_to_t< Self&, T >
  run( Self& self ) noexcept
  {
    return self.v;
  }

  template< class Self >
  static constexpr
  call_detail::give_qualifiers_to_t< Self&&, std::remove_const_t< T > >
  run( Self&& self ) noexcept
  {
    return ARGOT_FORWARD( Self )( self ).v;
  }
};

template< class T >
struct access_impl< containment_wrapper< T& > >
{
  template< class Self >
  static constexpr T& run( Self&& self ) noexcept
  {
    return *self.v;
  }
};

template< class T >
struct access_impl< containment_wrapper< T&& > >
{
  template< class Self >
  static constexpr call_detail::give_qualifiers_to_t< Self&&, T&& >
  run( Self&& self ) noexcept
  {
    return ARGOT_FORWARD( call_detail::give_qualifiers_to_t< Self&&, T&& > )
    ( *self.v );
  }
};

template< class T >
struct state_impl< containment_wrapper< T > >
{
  template< class Self >
  static constexpr call_detail::give_qualifiers_to_t
  < Self&&, typename containment_wrapper< T >::state_type >
  run( Self&& self ) noexcept
  {
    return ARGOT_FORWARD( Self )( self ).v;
  }
};

template< class T >
constexpr decltype( auto ) contained_state( T&& object ) noexcept
{
  return state_impl< detail_argot::remove_cvref_t< T > >::run( ARGOT_FORWARD( T )( object ) );
}

} // namespace argot(::detail_contained)

// Requires: T is a valid instantiation of containment_wrapper
struct access_contained_fn
{
  template< class T >
  constexpr decltype( auto ) operator()( T&& object ) const noexcept
  {
    return detail_contained::access_impl< detail_argot::remove_cvref_t< T > >
    ::run( ARGOT_FORWARD( T )( object ) );
  }
} inline constexpr access_contained{};

template< bool Condition >
constexpr typename argot_detail::conditional< Condition >::template apply
< access_contained_fn
, referential_identity_fn
>
access_contained_if{};

template< class T >
constexpr typename argot_detail::conditional< !is_containment_wrapper_v< T > >
::template apply
< access_contained_fn
, referential_identity_fn
> access_contained_if_special{};

namespace detail_contained_adl {

#define ARGOT_DETAIL_CONTAINED_OPERATOR( op )                                  \
template< class T >                                                            \
constexpr auto operator op                                                     \
( const containment_wrapper< T >& lhs, const containment_wrapper< T >& rhs )   \
noexcept                                                                       \
( noexcept(    ( detail_contained::contained_state )( lhs )                    \
            op ( detail_contained::contained_state )( rhs )                    \
          )                                                                    \
) -> decltype(    ( detail_contained::contained_state )( lhs )                 \
               op ( detail_contained::contained_state )( rhs )                 \
             )                                                                 \
{                                                                              \
  return    ( detail_contained::contained_state )( lhs )                       \
         op ( detail_contained::contained_state )( rhs );                      \
}

ARGOT_DETAIL_CONTAINED_OPERATOR( == )
ARGOT_DETAIL_CONTAINED_OPERATOR( != )
ARGOT_DETAIL_CONTAINED_OPERATOR( < )
ARGOT_DETAIL_CONTAINED_OPERATOR( <= )
ARGOT_DETAIL_CONTAINED_OPERATOR( >= )
ARGOT_DETAIL_CONTAINED_OPERATOR( > )

#undef ARGOT_DETAIL_CONTAINED_OPERATOR

// TODO(mattcalabrese) Make swap and hash

} // namespace argot(::detail_contained_adl)

} // namespace argot

#endif  // ARGOT_CONTAINED_HPP_
