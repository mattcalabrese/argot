/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_BOOST_SHARED_FUTURE_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_BOOST_SHARED_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION
#error Included boost::shared_future concept map header without continuations enabled.
#else

#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/future/immediate_boost_executor.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/persistent_forgetful_thenable.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/void_.hpp>

#include <boost/thread/future.hpp>

#include <type_traits>

namespace argot {
namespace detail_persistent_future_boost_shared_future {

template< class T, class Fun >
static constexpr auto
intrinsic_persistent_then( boost::shared_future< T > const& self, Fun&& fun )
{
  return self.then
  ( [ fun = ARGOT_MOVE( fun ) ]
    ( boost::shared_future< T > const& self_arg ) mutable -> decltype( auto )
    {
      if constexpr( std::is_void_v< T > )
      {
        void_to_regular_void_t< T > result{};

        self_arg.get();
        return ARGOT_MOVE( fun )( result );  // TODO(mattcalabrese) as const?
      }
      else
        ARGOT_MOVE( fun )( self_arg.get() );
    }
  );
}

} // namespace argot(::detail_persistent_future_boost_shared_future)

template< class T >
struct make_concept_map
< PersistentForgetfulThenable
  < boost::shared_future< T >, executor::immediate_t >
>
{
  template< class Fun >
  static constexpr void forgetful_then
  ( boost::shared_future< T > const& self, executor::immediate_t, Fun&& fun )
  {
    (void)detail_persistent_future_boost_shared_future
    ::intrinsic_persistent_then( self, ARGOT_MOVE( fun ) );
  }
};

} // namespace argot

#endif  // ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION

#endif  // ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_BOOST_SHARED_FUTURE_HPP_
