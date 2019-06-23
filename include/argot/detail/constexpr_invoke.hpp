/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONSTEXPR_INVOKE_HPP_
#define ARGOT_DETAIL_CONSTEXPR_INVOKE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/forward.hpp>
#include <argot/lazy_expand.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <functional>
#include <type_traits>
#include <utility>

namespace argot::argot_detail {

template< class T, class... P >
struct invoke_impl_basic
{
  template< class Q >
  static constexpr basic_result_of_t< Q&&, P&&... > run( Q&& fun, P&&... args )
  noexcept( is_nothrow_basic_callable_v< Q&&, P&&... > )
  {
    return ARGOT_FORWARD( Q )( fun )( ARGOT_FORWARD( P )( args )... );
  }
};

template< class T, class Head, class... Tail >
struct invoke_impl_member_function;

template< class T, class Self, class... Args >
struct invoke_impl_member_function_direct
{
  template< class Q >
  static constexpr decltype
  ( ( ARGOT_DECLVAL( Self ).*ARGOT_DECLVAL( Q ) )( ARGOT_DECLVAL( Args )... ) )
  run( Q&& fun, Self&& self, Args&&... args )
  noexcept
  ( noexcept
    ( ( ARGOT_DECLVAL( Self ).*ARGOT_DECLVAL( Q ) )( ARGOT_DECLVAL( Args )... )
    )
  )
  {
    return ( self.*fun )( ARGOT_FORWARD( Args )( args )... );
  }
};

template< class T, class Self, class... Args >
struct invoke_impl_member_object_direct
{
  template< class Q >
  static constexpr decltype( ARGOT_DECLVAL( Self ).*ARGOT_DECLVAL( Q ) )
  run( Q&& member, Self&& self )
  noexcept( noexcept( ARGOT_DECLVAL( Self ).*ARGOT_DECLVAL( Q ) ) )
  {
    return self.*member;
  }
};

template< class T >
struct is_reference_wrapper : std::false_type {};

template< class T >
struct is_reference_wrapper< std::reference_wrapper< T > > : std::true_type {};

template< class T, class Self, class... Args >
struct invoke_impl_member_function_ref
{
  template< class Q >
  static constexpr decltype
  ( ( ARGOT_DECLVAL( Self ).get().*ARGOT_DECLVAL( Q ) )
    ( ARGOT_DECLVAL( Args )... )
  )
  run( Q&& fun, Self&& self, Args&&... args )
  noexcept
  ( noexcept
    ( ( ARGOT_DECLVAL( Self ).get().*ARGOT_DECLVAL( Q ) )
      ( ARGOT_DECLVAL( Args )... )
    )
  )
  {
    return ( self.get().*fun )( ARGOT_FORWARD( Args )( args )... );
  }
};

template< class T, class Self, class... Args >
struct invoke_impl_member_function_fallback
{
  template< class Q >
  static constexpr decltype
  ( ( ( *ARGOT_DECLVAL( Self ) ).*ARGOT_DECLVAL( Q ) )
    ( ARGOT_DECLVAL( Args )... )
  )
  run( Q&& fun, Self&& self, Args&&... args )
  noexcept
  ( noexcept
    ( ( ( *ARGOT_DECLVAL( Self ) ).*ARGOT_DECLVAL( Q ) )
        ( ARGOT_DECLVAL( Args )... )
    )
  )
  {
    return ( ( *ARGOT_FORWARD( Self )( self ) ).*fun )
    ( ARGOT_FORWARD( Args )( args )... );
  }
};

template< class T, class Self >
struct invoke_impl_member_object_ref
{
  template< class Q >
  static constexpr decltype( ARGOT_DECLVAL( Self ).get().*ARGOT_DECLVAL( Q ) )
  run( Q&& member, Self&& self )
  noexcept( noexcept( ARGOT_DECLVAL( Self ).get().*ARGOT_DECLVAL( Q ) ) )
  {
    return self.get().*member;
  }
};

template< class T, class Self >
struct invoke_impl_member_object_fallback
{
  template< class Q >
  static constexpr decltype( ( *ARGOT_DECLVAL( Self ) ).*ARGOT_DECLVAL( Q ) )
  run( Q&& member, Self&& self )
  noexcept( noexcept( ( *ARGOT_DECLVAL( Self ) ).*ARGOT_DECLVAL( Q ) ) )
  {
    return ( *ARGOT_FORWARD( Self )( self ) ).*member;
  }
};

template< class T, class Self, class... Args >
struct invoke_impl_member_function_indirect
  : conditional< is_reference_wrapper< std::decay_t< Self > >::value >
    ::template apply< invoke_impl_member_function_ref< T, Self, Args... >
                    , invoke_impl_member_function_fallback< T, Self, Args... >
                    > {};

template< class Type, class T, class Head, class... Tail >
struct invoke_impl_member_function< Type T::*, Head, Tail... >
  : conditional< std::is_base_of_v< T, std::decay_t< Head > > >::template apply
    < invoke_impl_member_function_direct< Type T::*, Head, Tail... >
    , invoke_impl_member_function_indirect< Type T::*, Head, Tail... >
    > {};

template< class T, class Self >
struct invoke_impl_member_object_indirect
  : conditional< is_reference_wrapper< std::decay_t< Self > >::value >
    ::template apply< invoke_impl_member_object_ref< T, Self >
                    , invoke_impl_member_object_fallback< T, Self >
                    > {};

template< class T, class Head, class... Tail >
struct invoke_impl_member_object {};

template< class Type, class T, class Head >
struct invoke_impl_member_object< Type T::*, Head >
  : conditional< std::is_base_of_v< T, std::decay_t< Head > > >::template apply
    < invoke_impl_member_object_direct< Type T::*, Head >
    , invoke_impl_member_object_indirect< Type T::*, Head >
    > {};

template< class T, class... P >
struct invoke_impl_member {};

template< class T, class Head, class... Tail >
struct invoke_impl_member< T, Head, Tail... >
  : conditional< std::is_member_object_pointer_v< detail_argot::remove_cvref_t< T > > >
    ::template apply< invoke_impl_member_object< T, Head, Tail... >
                    , invoke_impl_member_function< T, Head, Tail... >
                    > {};

template< class T, class... P >
struct invoke_impl
  : conditional< std::is_member_pointer_v< detail_argot::remove_cvref_t< T > > >
    ::template apply< invoke_impl_member< T, P... >
                    , invoke_impl_basic< T, P... >
                    > {};

template< class F, class... P >
using result_of_constexpr_invoke_t
  = decltype
    ( invoke_impl< F&&, P&&... >
      ::run( ARGOT_DECLVAL( F ), ARGOT_DECLVAL( P )... )
    );

// TODO(mattcalabrese) ref qualifiers?
template< class F, class... P >
using result_of_constexpr_invoke
  = argot::lazy_expand< result_of_constexpr_invoke_t, F, P... >;

template< class F, class... P >
bool constexpr is_nothrow_constexpr_invocable_v
  = noexcept
    ( invoke_impl< F&&, P&&... >
      ::run( ARGOT_DECLVAL( F ), ARGOT_DECLVAL( P )... )
    );

struct constexpr_invoke_t
{
  // TODO(mattcalabrese) Constrain
  template< class F, class... P >
  constexpr result_of_constexpr_invoke_t< F&&, P&&... >
  operator ()( F&& f, P&&... args ) const
  noexcept( is_nothrow_constexpr_invocable_v< F&&, P&&... > )
  {
    return invoke_impl< F&&, P&&... >::run
    ( ARGOT_FORWARD( F )( f ), ARGOT_FORWARD( P )( args )... );
  }
} inline constexpr constexpr_invoke{};

}  // namespace (argot::argot_detail)

#endif  // ARGOT_DETAIL_CONSTEXPR_INVOKE_HPP_
