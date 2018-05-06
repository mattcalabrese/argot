/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_ARGUMENT_PACK_HPP_
#define ARGOT_DETAIL_ARGUMENT_PACK_HPP_

#include <argot/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/holder.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/no_unique_address.hpp>

#include <memory>
#include <type_traits>
#include <utility>

// TODO(mattcalabrese) Optimize this up to some finite N (possibly 10)

namespace argot {
namespace call_detail {

template< class Head, class TailInvoker >
struct make_argument_pack_invoker_t
{
  std::remove_reference_t< Head >* head;
  ARGOT_NO_UNIQUE_ADDRESS TailInvoker tail_invoker;

  template< class... Heads >
  constexpr auto operator ()( Heads&&... heads ) const
  {
    return tail_invoker
    ( ARGOT_FORWARD( Heads )( heads )..., ARGOT_FORWARD( Head )( *head ) );
  }

  template< class BeforeHead >
  constexpr auto with_head( BeforeHead&& before_head ) const
  {
    return make_argument_pack_invoker_t
    < BeforeHead, make_argument_pack_invoker_t >
    { std::addressof( before_head ), *this };
  }
};

struct make_empty_argument_pack_invoker_t
{
  template< class... P >
  constexpr auto operator ()( P&&... args ) const
  {
    // TODO(mattcalabrese) SFINAE
    return [ &args... ]( auto&& fun ) -> decltype( auto )
      // -> std::invoke_result_t< decltype( fun ), P&&... >
    {
      return ARGOT_FORWARD( decltype( fun ) )( fun )
      ( ARGOT_FORWARD( P )( args )... );
    };
  }

  template< class Head >
  constexpr auto with_head( Head&& head ) const
  {
    return make_argument_pack_invoker_t
    < Head, make_empty_argument_pack_invoker_t >
    { std::addressof( head ), *this };
  }
};

template< class... P >
struct argument_pack_t;

// TODO(mattcalabrese) Make Regular
template<>
struct argument_pack_t<>
{
  template< class Self >
  static constexpr auto make_invoker( Self&& /*self*/ )
  {
    return make_empty_argument_pack_invoker_t();
  }
};

template< class T >
struct forward_as_const_impl
{
  static constexpr T&& run( T&& arg )
  {
    return ARGOT_FORWARD( T )( arg );
  }
};

template< class T >
struct forward_as_const_impl< T& >
{
  static constexpr const T& run( T& arg )
  {
    return arg;
  }
};

template< class T >
constexpr decltype( auto ) forward_as_const( T&& arg )
{
  return forward_as_const_impl< T >::run( ARGOT_FORWARD( T )( arg ) );
}

// TODO(mattcalabrese) Make Regular
template< class Head, class... Tail >
struct argument_pack_t< Head, Tail... >
{
  using head_type = holder< Head >;
  using tail_type = argument_pack_t< Tail... >;
  ARGOT_NO_UNIQUE_ADDRESS holder< Head > head;
  ARGOT_NO_UNIQUE_ADDRESS argument_pack_t< Tail... > tail;

  template< class Self >
  static constexpr auto make_invoker( Self&& self )
  {
    return tail_type::make_invoker( ARGOT_FORWARD( Self )( self ).tail )
    .with_head( ( access_holder )( ARGOT_FORWARD( Self )( self ).head ) );
  }
};

template< class Self >
using result_of_make_invoker_t
  = decltype( remove_cvref_t< Self >::make_invoker( ARGOT_DECLVAL( Self ) ) );

// TODO(mattcalabrese) Possibly just encapsulate (I don't think this can fail)
template< class Self >
using result_of_make_invoker = lazy_expand< result_of_make_invoker_t, Self >;

template< bool = false >
constexpr argument_pack_t<> make_argument_pack() noexcept
{
  return argument_pack_t<>();
}

template< class Head, class... Tail, class HeadP, class... TailP >
constexpr argument_pack_t< Head const, Tail const... >
make_argument_pack( HeadP&& head, TailP&&... tail )
{
  // TODO(mattcalabrese) sinklike cast to avoid "fake" copies
  return
  { ( make_holder< Head > )( ARGOT_FORWARD( HeadP )( head ) )
  , ( make_argument_pack< Tail... > )( ARGOT_FORWARD( TailP )( tail )... )
  };
}

struct argument_pack_as_references_t
{
  constexpr argument_pack_t<> operator ()() const
  {
    return argument_pack_t<>();
  }

  template< class Head, class... Tail >
  constexpr argument_pack_t< Head&&, Tail&&... >
  operator ()( Head&& head, Tail&&... tail ) const
  {
    return
    { make_holder< Head&& >( ARGOT_FORWARD( Head )( head ) )
    , argument_pack_as_references_t()( ARGOT_FORWARD( Tail )( tail )... )
    };
  }
} inline constexpr argument_pack_as_references{};

struct argument_pack_as_values_t
{
  constexpr argument_pack_t<> operator ()() const
  {
    return argument_pack_t<>();
  }

  // TODO(mattcalabrese) Check number of moves... make sure this doesn't
  //                     repeatedly move the tail. If so, rewrite to do
  //                     initialization via a function that returns tail.
  template< class Head, class... Tail >
  constexpr std::enable_if_t
  < is_sinkable_v< Head, Tail... >
  , argument_pack_t
    < std::remove_reference_t< Head > const
    , std::remove_reference_t< Tail > const...
    >
  >
  operator ()( Head&& head, Tail&&... tail ) const
  {
    return
    { make_holder< std::remove_reference_t< Head > const >
      ( ARGOT_FORWARD( Head )( head ) )
    , argument_pack_as_values_t()( ARGOT_FORWARD( Tail )( tail )... )
    };
  }
} inline constexpr argument_pack_as_values{};

}  // namespace argot::call_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_ARGUMENT_PACK_HPP_
