/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_SINK_HPP_
#define ARGOT_DETAIL_SINK_HPP_

#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>
#include <utility>

// TODO(mattcalabrese) Remove volatile support

namespace argot {
namespace call_detail {

template< class Target, class T >
using result_of_forward_t
  = decltype( ARGOT_FORWARD( Target )( ARGOT_DECLVAL( T ) ) );

template< class T >
struct unconstrained_sink_impl
{
  static_assert( std::is_object_v< T > );
  static_assert( !std::is_const_v< T > );

  static constexpr T&& run( T&& source ) { return ARGOT_MOVE( source ); }
  static constexpr T const& run( T const& source ) { return source; }
};

template< class T >
using result_of_unconstrained_sink_t
  = decltype
    ( unconstrained_sink_impl< detail_argot::remove_cvref_t< T > >
      ::run( ARGOT_DECLVAL( T ) )
    );

template< class T >
using result_of_unconstrained_sink
  = lazy_expand< result_of_unconstrained_sink_t, T >;

template< class Enabler, class... T >
struct can_unconstrained_sink_impl : std::false_type {};

template< class... T >
struct can_unconstrained_sink_impl
< std::void_t< result_of_unconstrained_sink_t< T >... >, T... >
  : std::true_type {};

template< class... T >
bool constexpr can_unconstrained_sink_v
  = can_unconstrained_sink_impl< void, T... >::value;

template< class... T >
struct can_unconstrained_sink
  : std::integral_constant< bool, can_unconstrained_sink_v< T... > >{};

template< class P >
struct unconstrained_sink_t
{
  template< class T >
  constexpr result_of_unconstrained_sink_t< result_of_forward_t< P, T& > >
  operator ()( T&& source ) const
  {
    return unconstrained_sink_impl< detail_argot::remove_cvref_t< P > >::run
    ( ARGOT_FORWARD( P )( source ) );
  }
};

template< class P >
unconstrained_sink_t< P > constexpr unconstrained_sink{};

template< class T >
struct sink_impl
{
  static_assert( std::is_object_v< T > );
  static_assert( !std::is_const_v< T > );

  using value_type = detail_argot::remove_cvref_t< T >;

  template< class LazyT = T >
  static constexpr fast_enable_if_t
  <    std::is_constructible_v< value_type, LazyT&& >
    && std::is_destructible_v< value_type >
  , T&&
  >
  run( T&& source ) noexcept { return ARGOT_MOVE( source ); }

  template< class LazyT = T >
  static constexpr fast_enable_if_t
  <    std::is_constructible_v< value_type, LazyT const& >
    && std::is_destructible_v< value_type >
  , T const&
  >
  run( T const& source ) noexcept { return source; }
};

template< class T >
using result_of_sink_t
  = decltype( sink_impl< detail_argot::remove_cvref_t< T > >::run( ARGOT_DECLVAL( T ) ) );

template< class T >
using result_of_sink = lazy_expand< result_of_sink_t, T >;

template< class Enabler, class... T >
struct is_sinkable_impl : std::false_type {};

template< class... T >
struct is_sinkable_impl< std::void_t< result_of_sink_t< T >... >, T... >
  : std::true_type {};

template< class... T >
bool constexpr is_sinkable_v = is_sinkable_impl< void, T... >::value;

template< class... T >
struct is_sinkable : std::bool_constant< is_sinkable_v< T... > >{};

template< class... T >
bool constexpr is_nothrow_sinkable_v
  = (    std::is_nothrow_constructible_v
         < detail_argot::remove_cvref_t< T >, result_of_sink_t< T > >
      && ...
    );

template< class... T >
struct is_nothrow_sinkable
  : std::bool_constant< is_nothrow_sinkable_v< T... > > {};

struct sink_t
{
  template< class T >
  constexpr result_of_sink_t< T > operator ()( T&& source ) const noexcept
  {
    return sink_impl< detail_argot::remove_cvref_t< T > >
    ::run( ARGOT_FORWARD( T )( source ) );
  }
} inline constexpr sink{};

template< class P >
struct forward_and_sink_t
{
  template< class T >
  constexpr result_of_sink_t< result_of_forward_t< P, T& > >
  operator ()( T&& source ) const noexcept
  {
    return sink_impl< detail_argot::remove_cvref_t< P > >::run
    ( ARGOT_FORWARD( P )( source ) );
  }
};

// TODO(mattcalabrese) Eliminate the other sink and rename this to sink.
template< class P >
forward_and_sink_t< P > constexpr forward_and_sink{};

template< class T >
struct sinklike_cast_impl
{
  static_assert( std::is_object_v< T > );
  static_assert( !std::is_const_v< T > );

  using value_type = detail_argot::remove_cvref_t< T >;

  static constexpr T&& run( T&& source ) noexcept
  {
    return ARGOT_MOVE( source );
  }

  static constexpr T const& run( T const& source ) noexcept { return source; }
};

template< class T >
using result_of_sinklike_cast_t
  = decltype
    ( sinklike_cast_impl< detail_argot::remove_cvref_t< T > >::run( ARGOT_DECLVAL( T ) ) );

template< class T >
using result_of_sinklike_cast = lazy_expand< result_of_sinklike_cast_t, T >;

struct sinklike_cast_t
{
  template< class T >
  constexpr result_of_sinklike_cast_t< T >
  operator ()( T&& source ) const noexcept
  {
    return sinklike_cast_impl< detail_argot::remove_cvref_t< T > >
    ::run( ARGOT_FORWARD( T )( source ) );
  }
} inline constexpr sinklike_cast{};

template< class T >
struct decay_sink_impl
{
  using decayed_type = std::decay_t< T >;

  template< class LazyT = T >
  static constexpr fast_enable_if_t
  <    std::is_constructible_v< decayed_type, LazyT >
    && std::is_destructible_v< decayed_type >  // TODO(mattcalabrese) Test this requirement
  , LazyT&&
  >
  run( T&& source ) noexcept { return ARGOT_MOVE( source ); }

  template< class LazyT = T >
  static constexpr fast_enable_if_t
  <    std::is_constructible_v< decayed_type, LazyT const& >
    && std::is_destructible_v< decayed_type >  // TODO(mattcalabrese) Test this requirement
  , LazyT const&
  >
  run( T const& source ) noexcept { return source; }
};

template< class T >
using result_of_decay_sink_t
  = decltype( decay_sink_impl< detail_argot::remove_cvref_t< T > >::run( ARGOT_DECLVAL( T ) ) );

template< class T >
using result_of_decay_sink = lazy_expand< result_of_decay_sink_t, T >;

template< class Enabler, class... T >
struct is_decay_sinkable_impl : std::false_type {};

template< class... T >
struct is_decay_sinkable_impl
< std::void_t< result_of_decay_sink_t< T >... >, T... >
  : std::true_type {};

template< class... T >
bool constexpr is_decay_sinkable_v
  = is_decay_sinkable_impl< void, T... >::value;

template< class... T >
struct is_decay_sinkable : std::bool_constant< is_decay_sinkable_v< T... > >{};

template< class... T >
bool constexpr is_nothrow_decay_sinkable_v
  = (    std::is_nothrow_constructible_v
         < detail_argot::remove_cvref_t< T >, result_of_decay_sink_t< T > >
      && ...
    );

template< class... T >
struct is_nothrow_decay_sinkable
  : std::bool_constant< is_nothrow_decay_sinkable_v< T... > > {};

struct decay_sink_t
{
  template< class T >
  constexpr result_of_decay_sink_t< T > operator ()( T&& source ) const noexcept
  {
    return decay_sink_impl< detail_argot::remove_cvref_t< T > >
    ::run( ARGOT_FORWARD( T )( source ) );
  }
} inline constexpr decay_sink{};

template< class P >
struct forward_and_decay_sink_t
{
  template< class T >
  constexpr result_of_decay_sink_t< result_of_forward_t< P, T& > >
  operator ()( T&& source ) const noexcept
  {
    return decay_sink_impl< detail_argot::remove_cvref_t< P > >::run
    ( ARGOT_FORWARD( P )( source ) );
  }
};

// TODO(mattcalabrese) Eliminate the other decay sink and rename this to sink.
template< class P >
forward_and_decay_sink_t< P > constexpr forward_and_decay_sink{};

}  // namespace argot::call_detail
}  // namespace argot

#define ARGOT_SINK( ... )                                                      \
static_cast                                                                    \
< ::argot::call_detail::result_of_sink_t< decltype((__VA_ARGS__)) > >          \
( __VA_ARGS__ )

#define ARGOT_FORWARD_AND_SINK( ... )                                          \
static_cast< ::argot::call_detail::result_of_sink_t< __VA_ARGS__ > >           \
ARGOT_DETAIL_FORWARD_AND_SINK_IMPL

// TODO(Mattcalabrese) Macros for decay_sink, forward_and_decay_sink

#define ARGOT_DETAIL_FORWARD_AND_SINK_IMPL( ... ) ( __VA_ARGS__ )

#endif  // ARGOT_DETAIL_SINK_HPP_
