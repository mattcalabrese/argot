/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VOID_HPP_
#define ARGOT_VOID_HPP_

#ifdef __cpp_regular_void // If Regular Void p0146 is implemented...

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/forward.hpp>

#include <type_traits>

namespace argot {

using void_ = void;

inline void_ constexpr void_v{};

template< class T >
using void_to_regular_void_t = T;

template< class T >
using regular_void_to_void_t = T;

template< class T >
bool constexpr is_regular_void_v = std::is_void_v< T >;

template< class T >
using is_regular_void = std::is_void< T >;

template< class Fun, class... P >
constexpr decltype( auto ) void_to_regular_void_invoke( Fun&& fun, P&&... args )
noexcept
( noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > ) )
{
  return argot_detail::constexpr_invoke
  ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... );
}

template< class Fun, class... P >
constexpr decltype( auto ) regular_void_to_void_invoke( Fun&& fun, P&&... args )
noexcept
( noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > ) )
{
  return argot_detail::constexpr_invoke
  ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... );
}

}  // namespace argot

#else  // Otherwise, we live in a dystopian world without Regular Void p0146.

#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/forward.hpp>

#include <cstddef>
#include <functional>
#include <type_traits>

namespace argot {

struct void_
{
  void_() = default;

  template< class T >
  explicit constexpr void_( T&& ) noexcept {}

  [[nodiscard]] friend constexpr bool operator ==( void_, void_ ) noexcept
  {
    return true;
  }

  [[nodiscard]] friend constexpr bool operator !=( void_, void_ ) noexcept
  {
    return false;
  }

  [[nodiscard]] friend constexpr bool operator <( void_, void_ ) noexcept
  {
    return false;
  }

  [[nodiscard]] friend constexpr bool operator <=( void_, void_ ) noexcept
  {
    return true;
  }

  [[nodiscard]] friend constexpr bool operator >=( void_, void_ ) noexcept
  {
    return true;
  }

  [[nodiscard]] friend constexpr bool operator >( void_, void_ ) noexcept
  {
    return false;
  }

  friend constexpr void swap( void_, void_ ) noexcept {}
};

template< class T >
bool constexpr is_regular_void_v = false;

template<>
bool constexpr is_regular_void_v< void_ > = true;

template<>
bool constexpr is_regular_void_v< void_ const > = true;

template<>
bool constexpr is_regular_void_v< void_ volatile > = true;

template<>
bool constexpr is_regular_void_v< void_ volatile const > = true;

// TODO(mattcalabrese) Possibly use inheritance?
template< class T >
using is_regular_void = std::bool_constant< is_regular_void_v< T > >;

inline void_ constexpr void_v{};

template< class T >
using void_to_regular_void_t
  = typename argot_detail::conditional< std::is_void_v< T > >
    ::template half_meta_apply
    < call_detail::give_qualifiers_to_t, T
    , T, void_
    >;

template< class T >
using regular_void_to_void_t
  = typename argot_detail::conditional< is_regular_void_v< T > >
    ::template half_meta_apply
    < call_detail::give_qualifiers_to_t, T
    , T, void
    >;

template< class Fun, class... P >
constexpr decltype( auto ) void_to_regular_void_invoke( Fun&& fun, P&&... args )
noexcept
( noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > ) )
{
  if constexpr
  ( std::is_void_v
    < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... > >
  )
  {
    argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... );

    return void_();
  }
  else
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... );
}

template< class Fun, class... P >
constexpr decltype( auto ) regular_void_to_void_invoke( Fun&& fun, P&&... args )
noexcept
( noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > ) )
{
  if constexpr
  ( is_regular_void_v
    < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... > >
  )
    argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... );
  else
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... );
}

}  // namespace argot

namespace std {

template<>
struct hash< ::argot::void_ >
{
  // TODO(mattcalabrese) Only make this nodiscard if the standard specifies it.
  [[nodiscard]] constexpr size_t operator ()( ::argot::void_ ) noexcept
  {
    return 0;
  }
};

}  // namespace std

#endif  // End of branching for Regular Void

#endif  // ARGOT_VOID_HPP_
