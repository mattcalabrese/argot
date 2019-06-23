/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_FORGETFUL_THENABLE_DETAIL_BOOST_SHARED_FUTURE_HPP_
#define ARGOT_CONCEPTS_FORGETFUL_THENABLE_DETAIL_BOOST_SHARED_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION
#error Included boost::shared_future concept map header without continuations enabled.
#else

#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/future/detail/immediate_boost_executor.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/void_.hpp>

#include <boost/thread/future.hpp>

#include <type_traits>

namespace argot {
namespace detail_future_boost_shared_future {

template< class T, class Fun >
static constexpr auto
intrinsic_then( boost::shared_future< T >&& self, Fun&& fun )
{
  // TODO(mattcalabrese) Get from fut_traits
  using value_type_t = void_to_regular_void_t< T >;

  // TODO(mattcalabrese) Perform the decay_sink as a cast to avoid moves
  return ARGOT_MOVE( self ).then
  ( boost::launch::sync
  , [ fun = ARGOT_MOVE( fun ) ]( boost::shared_future< T >&& self_arg ) mutable
    {
      if constexpr( std::is_void_v< T > )
      {
        ARGOT_MOVE( self_arg ).get();
        ARGOT_MOVE( fun )( value_type_t() );
      }
      else
        ARGOT_MOVE( fun )
        ( const_cast< T&& >( ARGOT_MOVE( self_arg ).get() ) );  // This probably shouldn't cast away const
    }
  );
}

} // namespace argot(::detail_future_boost_shared_future)

template< class T >
struct make_concept_map
< ForgetfulThenable< boost::shared_future< T >, executor::immediate_t > >
{
  template< class Fun >
  static constexpr void forgetful_then
  ( boost::shared_future< T >&& self, executor::immediate_t, Fun&& fun )
  {
    (void)detail_future_boost_shared_future::intrinsic_then
    ( ARGOT_MOVE( self ), ARGOT_MOVE( fun ) );
  }
};

} // namespace argot

#endif  // ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION

#endif  // ARGOT_CONCEPTS_FORGETFUL_THENABLE_DETAIL_BOOST_SHARED_FUTURE_HPP_
